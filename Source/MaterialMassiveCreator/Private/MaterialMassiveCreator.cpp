// Copyright Epic Games, Inc. All Rights Reserved.

#include "MaterialMassiveCreator.h"
#include "GegJsonIterator.h"
#include "Misc/FileHelper.h"


#define LOCTEXT_NAMESPACE "FMaterialMassiveCreatorModule"

void FMaterialMassiveCreatorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMaterialMassiveCreatorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

bool FMaterialMassiveCreatorModule::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	if (FParse::Command(&Cmd, TEXT("create")))
	{
		if (FParse::Command(&Cmd, TEXT("materials")))
		{
			FString Lines;
			FString FilePath = FParse::Token(Cmd, false);
			if (FilePath.IsEmpty())
			{
				UE_LOG(LogTemp, Error, TEXT("Input path is empty"));
				return true;
			}

			FFileHelper::LoadFileToString(Lines, *FilePath);
			if (Lines.IsEmpty())
			{
				UE_LOG(LogTemp, Error, TEXT("File read is empty"));
				return true;
			}

			UGegJsonIterator* GegIterator = NewObject<UGegJsonIterator>();
			GegIterator->ProcessInputFile(Lines);

			UE_LOG(LogTemp, Display, TEXT("Materials Asset was created correctly"));
			return true;
		}
	}
	return false;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMaterialMassiveCreatorModule, MaterialMassiveCreator)