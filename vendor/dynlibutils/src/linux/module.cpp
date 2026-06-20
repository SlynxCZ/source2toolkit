// DynLibUtils
// Copyright (C) 2023 komashchenko (Phoenix)
// Licensed under the MIT license. See LICENSE file in the project root for details.

#include <dynlibutils/module.hpp>
#include <dynlibutils/memaddr.hpp>

#include <cstring>
#include <link.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

using namespace DynLibUtils;

CModule::~CModule()
{
	if (IsValid())
		dlclose(GetPtr());
}

//-----------------------------------------------------------------------------
// Purpose: Initializes the module from module name
// Input  : svModuleName
//          bExtension
// Output : bool
//-----------------------------------------------------------------------------
bool CModule::InitFromName(const std::string_view svModuleName, bool bExtension)
{
	if (IsValid())
		return false;

	if (svModuleName.empty())
		return false;

	std::string sModuleName(svModuleName);
	if (!bExtension)
		sModuleName.append(".so");

	struct dl_data
	{
		ElfW(Addr) addr;
		const char* moduleName;
		const char* modulePath;
	} dldata{ 0, sModuleName.c_str(), {} };

	dl_iterate_phdr([](dl_phdr_info* info, std::size_t /* size */, void* data)
	{
		dl_data* dldata = reinterpret_cast<dl_data*>(data);

		if (std::strstr(info->dlpi_name, dldata->moduleName) != nullptr)
		{
			dldata->addr = info->dlpi_addr;
			dldata->modulePath = info->dlpi_name;
		}

		return 0;
	}, &dldata);

	if (!dldata.addr)
		return false;

	if (!LoadFromPath(dldata.modulePath, RTLD_LAZY | RTLD_NOLOAD))
		return false;

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Initializes the module from module memory
// Input  : pModuleMemory
// Output : bool
//-----------------------------------------------------------------------------
bool CModule::InitFromMemory(const CMemory pModuleMemory, bool bForce)
{
	if (IsValid() && !bForce)
		return false;

	if (!pModuleMemory.IsValid())
		return false;

	Dl_info info;
	if (!dladdr(pModuleMemory, &info) || !info.dli_fbase || !info.dli_fname)
		return false;

	if (!LoadFromPath(info.dli_fname, RTLD_LAZY | RTLD_NOLOAD))
		return false;

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Initializes a module descriptors
//-----------------------------------------------------------------------------
bool CModule::LoadFromPath(const std::string_view svModelePath, int flags)
{
	void* handle = dlopen(svModelePath.data(), flags);
	if (!handle)
	{
		SaveLastError();
		return false;
	}

	link_map* lmap;
	if (dlinfo(handle, RTLD_DI_LINKMAP, &lmap) != 0)
	{
		dlclose(handle);
		return false;
	}

	int fd = open(lmap->l_name, O_RDONLY);
	if (fd == -1)
	{
		dlclose(handle);
		return false;
	}

	struct stat st;
	if (fstat(fd, &st) == 0)
	{
		void* map = mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		if (map != MAP_FAILED)
		{
			ElfW(Ehdr)* ehdr = static_cast<ElfW(Ehdr)*>(map);
			ElfW(Shdr)* shdrs = reinterpret_cast<ElfW(Shdr)*>(reinterpret_cast<std::uintptr_t>(ehdr) + ehdr->e_shoff);
			const char* strTab = reinterpret_cast<const char*>(reinterpret_cast<std::uintptr_t>(ehdr) + shdrs[ehdr->e_shstrndx].sh_offset);

			for (auto i = 0; i < ehdr->e_shnum; ++i) // Loop through the sections.
			{
				ElfW(Shdr)* shdr = reinterpret_cast<ElfW(Shdr)*>(reinterpret_cast<std::uintptr_t>(shdrs) + i * ehdr->e_shentsize);
				if (*(strTab + shdr->sh_name) == '\0')
					continue;

				auto& section = m_vecSections.emplace_back(static_cast<std::uintptr_t>(lmap->l_addr + shdr->sh_addr), shdr->sh_size, strTab + shdr->sh_name);

				// Copy disk bytes for executable sections so FindPattern can scan
				// original bytes even when functions have been hooked in live memory.
				const bool bExecutable = (shdr->sh_flags & SHF_EXECINSTR) != 0;
				if (bExecutable && shdr->sh_offset != 0 && shdr->sh_size != 0)
				{
					const auto* diskBytes = reinterpret_cast<const std::uint8_t*>(reinterpret_cast<std::uintptr_t>(ehdr) + shdr->sh_offset);
					section.m_diskBytes.assign(diskBytes, diskBytes + shdr->sh_size);
				}
			}

			munmap(map, st.st_size);
		}
	}

	close(fd);

	SetPtr(handle);
	m_sPath.assign(svModelePath);

	m_pExecutableSection = GetSectionByName(".text");
	assert(m_pExecutableSection != nullptr);

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Gets an address of a virtual method table by rtti type descriptor name
// Input  : svTableName
//          bDecorated
// Output : CMemory
//-----------------------------------------------------------------------------
CMemory CModule::GetVirtualTableByName(const std::string_view svTableName, bool bDecorated) const
{
	if (svTableName.empty())
		return DYNLIB_INVALID_MEMORY;

	const Section_t *pReadOnlyData = GetSectionByName(".rodata"), *pReadOnlyRelocations = GetSectionByName(".data.rel.ro");

	assert(pReadOnlyData != nullptr);
	assert(pReadOnlyRelocations != nullptr);

	if (!pReadOnlyData || !pReadOnlyRelocations)
		return DYNLIB_INVALID_MEMORY;

	std::string sDecoratedTableName(bDecorated ? svTableName : std::to_string(svTableName.length()) + std::string(svTableName));
	std::string sMask(sDecoratedTableName.length() + 1, 'x');

	CMemory typeInfoName = FindPattern(sDecoratedTableName.data(), sMask, nullptr, pReadOnlyData);
	if (!typeInfoName)
		return DYNLIB_INVALID_MEMORY;

	CMemory referenceTypeName = FindPattern(&typeInfoName, "xxxxxxxx", nullptr, pReadOnlyRelocations); // Get reference to type name.
	if (!referenceTypeName)
		return DYNLIB_INVALID_MEMORY;

	CMemory typeInfo = referenceTypeName.Offset(-0x8); // Offset -0x8 to typeinfo.

	for (const auto& sectionName : { std::string_view(".data.rel.ro"), std::string_view(".data.rel.ro.local") })
	{
		const Section_t *pSection = GetSectionByName(sectionName);
		if (!pSection)
			continue;

		CMemory reference;
		while ((reference = FindPattern(&typeInfo, "xxxxxxxx", reference, pSection))) // Get reference typeinfo in vtable
		{
			if (reference.Offset(-0x8).Get<int64_t>() == 0) // Offset to this.
			{
				return reference.Offset(0x8);
			}

			reference.OffsetSelf(0x8);
		}
	}

	return DYNLIB_INVALID_MEMORY;
}

//-----------------------------------------------------------------------------
// Purpose: Gets an address of a virtual method table by rtti type descriptor name
// Input  : svFunctionName
// Output : CMemory
//-----------------------------------------------------------------------------
CMemory CModule::GetFunctionByName(const std::string_view svFunctionName) const noexcept
{
	return CMemory((IsValid() && !svFunctionName.empty()) ? dlsym(GetPtr(), svFunctionName.data()) : nullptr);
}

//-----------------------------------------------------------------------------
// Purpose: Returns the module base
//-----------------------------------------------------------------------------
CMemory CModule::GetBase() const noexcept
{
	return RCast<link_map*>()->l_addr;
}

void CModule::SaveLastError()
{
	m_sLastError = dlerror();
}