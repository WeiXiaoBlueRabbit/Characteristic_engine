#include "defines.h"
#include "static_references.h"

u16 GetAbilityBySpecies(u16 species, u8 slot);
static const u16 gPokeAbilities[][3];

/**
 * @用于获取精灵特性
 */
u16 GetAbilityBySpecies(u16 species, u8 slot)
{
    return gPokeAbilities[species][slot];
}

static const u16 gPokeAbilities[][3] = {
//  特性1   特性2   特性3
    {0,     0,     0},
};