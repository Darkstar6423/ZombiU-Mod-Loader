#pragma once
#include "ZombiStructs.h"
#include "windows.h"
#include "hookparameter.h"

// refer to OnZombieDamage for ASM entry point


void playerDamageCallback();
bool createPlayerDamageHook();
