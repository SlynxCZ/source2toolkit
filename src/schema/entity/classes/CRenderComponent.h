#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CEntityComponent.h"

class CRenderComponent : public CEntityComponent
{
public:
    DECLARE_SCHEMA_CLASS(CRenderComponent);

    SCHEMA_FIELD(CEntityInstance*, __m_pChainEntity);
    SCHEMA_FIELD(bool, m_bIsRenderingWithViewModels);
    SCHEMA_FIELD(uint32_t, m_nSplitscreenFlags);
    SCHEMA_FIELD(bool, m_bEnableRendering);
    SCHEMA_FIELD(bool, m_bInterpolationReadyToDraw);
};
