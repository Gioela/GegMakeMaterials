// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "GegWorker.generated.h"

/**
 * 
 */
UCLASS()
class MATERIALMASSIVECREATOR_API UGegWorker : public UObject
{
	GENERATED_BODY()

private:
	FString Path;
	FString Name;
	//FString Rgba;
	//uint32 R;
	//uint32 G;
	//uint32 B;
	//uint32 A;
	uint32 TotMatCreated;
	uint32 TotMatInstancesCreated;
	FLinearColor Color;

	class UMaterialFactoryNew* GMaterialFactory;

public:
	UGegWorker();

	bool CreateMaterialAsset();

	void SetPath(const FString* InPath);
	void SetName(const FString* InName);
	void ResetColor();
	void SetColor(FString* InColor);

	void IncreaseTotMatCreated(uint32 value = 1);
	void IncreaseTotMatInstanceCreated();

	FString GetPath();
	FString GetName();
	FLinearColor GetColor();
	uint32 GetTotMatCreated();
	uint32 GetTotMaterialInstanceAssetCreated();

	float GetRandomValue(const float InMin = 0.f, const float InMax = 1.f);

	/**
	 * Singleton access
	 */
	// static UMaterialFactoryNew& Get();


protected:
	//struct FRandomStream RandomGenerator;
	FLinearColor MakeLinearColor(const FString* InVector);

	FVector4 InitRandomVector();

};
