#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
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

#include "CPathParticleRope.h"

class CPathParticleRopeAlias_path_particle_rope_clientside : public CPathParticleRope, public CBaseEntity::Factory<CPathParticleRopeAlias_path_particle_rope_clientside>
{
public:
    DECLARE_SCHEMA_CLASS(CPathParticleRopeAlias_path_particle_rope_clientside);

};
