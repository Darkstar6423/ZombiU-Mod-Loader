#pragma once
#include "ZombiStructs.h"
#include "windows.h"
#include "hookparameter.h"
#include "console.h"
// refer to OnZombieDamage for ASM entry point

void cheatGodmodeCommand(string args[]);
void playerDamageCallback();
bool createPlayerDamageHook();
