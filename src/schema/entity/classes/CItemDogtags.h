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

#include "CItem.h"

class CCSPlayerPawn;

class CItemDogtags : public CItem
{
public:
    DECLARE_SCHEMA_CLASS(CItemDogtags);

    SCHEMA_FIELD(CHandle<CCSPlayerPawn>, m_OwningPlayer);
    SCHEMA_FIELD(CHandle<CCSPlayerPawn>, m_KillingPlayer);
};
