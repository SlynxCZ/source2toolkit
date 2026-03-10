//
// Created by Michal Přikryl on 04.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "CBaseModelEntity.h"

#include "CBodyComponent.h"
#include "CSkeletonInstance.h"

#include "core/addresses.h"

CUtlSymbolLarge CBaseModelEntity::GetModelName()
{
    if(m_CBodyComponent == nullptr) return CUtlSymbolLarge();
    if(m_CBodyComponent->m_pSceneNode == nullptr) return CUtlSymbolLarge();
    if(((CSkeletonInstance*)m_CBodyComponent->m_pSceneNode.Get()) == nullptr) return CUtlSymbolLarge();
    return ((CSkeletonInstance*)m_CBodyComponent->m_pSceneNode.Get())->m_modelState().m_ModelName.Get();
}

Vector CBaseModelEntity::GetEyePosition()
{
    Vector x = Vector(m_vecViewOffset().m_vecX, m_vecViewOffset().m_vecY, m_vecViewOffset().m_vecZ);
    Vector m_vecOrigin = GetAbsOrigin();
    return {
        m_vecOrigin.x + x.x,
        m_vecOrigin.y + x.y,
        m_vecOrigin.z + x.z
    };
}

void CBaseModelEntity::SetModel(const char* pszModel){
    addresses::CBaseModelEntity_SetModel(this, pszModel);
}
