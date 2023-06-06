// Fill out your copyright notice in the Description page of Project Settings.


#include "GegWorker.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Factories/MaterialFactoryNew.h"
#include "Materials/MaterialExpressionVectorParameter.h"
#include "Math/Color.h"
//#include "Math/RandomStream.h"
#include "Math/UnrealMathUtility.h"

UGegWorker::UGegWorker()
{
	Path = TEXT("");
	Name = FString(TEXT(""));
	ResetColor();
	TotMatCreated = 0;
	TotMatInstancesCreated = 0;

	//RandomGenerator = FRandomStream();
	//RandomGenerator.GenerateNewSeed();

	GMaterialFactory = NewObject<UMaterialFactoryNew>();
}

bool UGegWorker::CreateMaterialAsset()
{
	if (! GMaterialFactory)
	{
		return false;
	}

	FString MatName = FString::Printf(TEXT("M_%s"), *GetName());
	UPackage* Package = CreatePackage(*FString::Printf(TEXT("/Game/Test/%s"), *MatName));
	UObject* NewObj = GMaterialFactory->FactoryCreateNew(GMaterialFactory->SupportedClass, Package, *MatName, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, nullptr, GWarn);

	FAssetRegistryModule::AssetCreated(NewObj);

	UMaterial* Material = Cast<UMaterial>(NewObj);
	Material->Modify();

	UMaterialExpressionVectorParameter* MatVectParams = NewObject<UMaterialExpressionVectorParameter>(Material);
	//UMaterialExpressionVectorParameter* BaseColor = MakeColorMaterial(NewMaterial, FLinearColor::MakeRandomColor());
	MatVectParams->DefaultValue = GetColor();
	MatVectParams->ParameterName = TEXT("BaseColor");
	MatVectParams->MaterialExpressionEditorX = -300;

	Material->BaseColor.Expression = MatVectParams;
	Material->Expressions.Add(MatVectParams);

	Material->PostEditChange();
	Material->MarkPackageDirty();

	IncreaseTotMatCreated();
	UE_LOG(LogTemp, Display, TEXT("Asset Created: %s"), *MatName);

	return true;
}

void UGegWorker::SetPath(const FString* InPath)
{
	Path = *InPath;
}

FString UGegWorker::GetPath()
{
	return Path;
}

void UGegWorker::SetName(const FString* InName)
{
	Name = *InName;
}

void UGegWorker::ResetColor()
{
	Color = FLinearColor::Black;
}

FString UGegWorker::GetName()
{
	return Name;
}

void UGegWorker::SetColor(FString* InColor)
{
	Color = MakeLinearColor(InColor);
}

FLinearColor UGegWorker::GetColor()
{
	return Color;
}

void UGegWorker::IncreaseTotMatCreated(uint32 value)
{
	TotMatCreated += value;
}

uint32 UGegWorker::GetTotMatCreated()
{
	return TotMatCreated;
}

void UGegWorker::IncreaseTotMatInstanceCreated()
{
	TotMatInstancesCreated += 1;
}

uint32 UGegWorker::GetTotMaterialInstanceAssetCreated()
{
	return TotMatInstancesCreated;
}

float UGegWorker::GetRandomValue(const float InMin, const float InMax)
{
	//return RandomGenerator.FRandRange(InMin, InMax);
	return FMath::FRandRange(InMin, InMax);
}

//UMaterialFactoryNew& UGegWorker::Get()
//{
//	static TSharedRef<UMaterialFactoryNew> GMaterialFactory = MakeShared<UMaterialFactoryNew>();
//	return GMaterialFactory.Get();
//}

FLinearColor UGegWorker::MakeLinearColor(const FString* InVector)
{
	FLinearColor RandColor = FLinearColor::MakeRandomColor();

	//for (const FString& ColorValue : Params)
	//{
	//	if (ColorValue.Equals(TEXT("r"), ESearchCase::IgnoreCase))
	//	{
	//		RandColor.R = FCString::Atof(*ColorValue);
	//	}
	//	else if (ColorValue.Equals(TEXT("g"), ESearchCase::IgnoreCase))
	//	{
	//		RandColor.G = FCString::Atof(*ColorValue);
	//	}
	//	else if (ColorValue.Equals(TEXT("b"), ESearchCase::IgnoreCase))
	//	{
	//		RandColor.B = FCString::Atof(*ColorValue);
	//	}
	//	else if (ColorValue.Equals(TEXT("a"), ESearchCase::IgnoreCase))
	//	{
	//		RandColor.A = FCString::Atof(*ColorValue);
	//	}
	//}

	TArray<FString> Params;
	InVector->ParseIntoArray(Params, TEXT(" "));

	if (Params.Num() == 2)
	{
		RandColor.A = FCString::Atof(*Params[1]);
	}
	else if (Params.Num() == 3)
	{
		RandColor.B = FCString::Atof(*Params[1]);
		RandColor.A = FCString::Atof(*Params[2]);
	}
	else if (Params.Num() == 4)
	{
		if (!Params[0].Equals(TEXT("r"), ESearchCase::CaseSensitive))
		{
			RandColor.R = FCString::Atof(*Params[0]);
		}
		RandColor.G = FCString::Atof(*Params[1]);
		RandColor.B = FCString::Atof(*Params[2]);
		RandColor.A = FCString::Atof(*Params[3]);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[ERROR] Error in parsin RGBA field"));
	}

	return RandColor;
}

FVector4 UGegWorker::InitRandomVector()
{
	FVector4 Vector = FVector4();
	Vector.X = GetRandomValue();
	Vector.Y = GetRandomValue();
	Vector.Z = GetRandomValue();
	Vector.W = GetRandomValue();
	return Vector;
}
