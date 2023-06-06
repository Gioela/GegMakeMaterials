// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/CoreMisc.h"
#include "Modules/ModuleManager.h"

class FMaterialMassiveCreatorModule : public IModuleInterface, public FSelfRegisteringExec
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);
};
