#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "vector.h"
#include "utlsymbol.h"
#include "utlsymbollarge.h"
#include "utlstring.h"
#include "utlstringtoken.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPlayer_ItemServices.h"

class CBasePlayerWeapon;

class CCSPlayer_ItemServices : public CPlayer_ItemServices, public CBaseEntity::Factory<CCSPlayer_ItemServices>
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayer_ItemServices);

    SCHEMA_FIELD(bool, m_bHasDefuser);
    SCHEMA_FIELD(bool, m_bHasHelmet);

public:
    void DropActivePlayerWeapon(CBasePlayerWeapon* pActiveWeapon);
    void RemoveWeapons();
    CBasePlayerWeapon* GiveNamedItem(const char* pszItem);
};
