#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPlayer_UseServices.h"

class CBaseEntity;

class CCSPlayer_UseServices : public CPlayer_UseServices
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayer_UseServices);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hLastKnownUseEntity);
    SCHEMA_FIELD(float, m_flLastUseTimeStamp);
    SCHEMA_FIELD(float, m_flTimeLastUsedWindow);
};
