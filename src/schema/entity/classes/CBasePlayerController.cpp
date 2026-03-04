//
// Created by Michal Přikryl on 04.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "CBasePlayerController.h"

#include "core/addresses.h"

void CBasePlayerController::SetPawn(CBasePlayerPawn* pPawn){
	addresses::CBasePlayerController_SetPawn(this, pPawn, true, false, false, false);
}
