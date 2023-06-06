#include "GegJsonIterator.h"
#include "GegWorker.h"

UGegJsonIterator::UGegJsonIterator()
{
	JsWorker = NewObject<UGegWorker>();
}

void UGegJsonIterator::ProcessInputFile(const FString& InFile)
{
	UE_LOG(LogTemp, Display, TEXT("ProcessInputFile -> Start"));

	TSharedRef<TJsonReader<TCHAR>> JsReader = TJsonReaderFactory<TCHAR>::Create(InFile);

	TSharedPtr<FJsonObject> OutArray;

	if (FJsonSerializer::Deserialize(JsReader, OutArray, FJsonSerializer::EFlags::None))
	{
		UE_LOG(LogTemp, Display, TEXT("Json deserialized"));
		MapExplorer(OutArray->Values);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error in Json Deserialization Process"));
	}

	UE_LOG(LogTemp, Error, TEXT("ProcessInputFile -> Total MaterialAsset Created are: %d"), JsWorker->GetTotMatCreated());
	UE_LOG(LogTemp, Display, TEXT("ProcessInputFile -> End"));
}

void UGegJsonIterator::MapExplorer(const TMap<FString, TSharedPtr<FJsonValue>>& InMap)
{
	for (TPair<FString, TSharedPtr<FJsonValue>> Element : InMap)
	{
		if (Element.Key.Equals(TEXT(""), ESearchCase::IgnoreCase) || !Element.Value.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("* * * * * * * * USCITA DAL MAP EXPLORER * * * * * * * * * * * * * * * * * * * * "));
			return;
		}

		switch (Element.Value->Type)
		{
		case EJson::Array:
			UE_LOG(LogTemp, Error, TEXT("[ARRAY] CHIAVE: %s\tValore e' array => ciclo iterativo sui singoli elementi"), *Element.Key);
			for (const TSharedPtr<FJsonValue> Item : Element.Value.ToSharedRef()->AsArray())
			{
				MapExplorer(Item->AsObject()->Values);
			}
			break;
		case EJson::Object:
			UE_LOG(LogTemp, Error, TEXT("[OBJ] CHIAVE: %s\tValore e' object => creazione nuova mappa"), *Element.Key);
			MapExplorer(Element.Value->AsObject()->Values);
			break;
		default:
			UE_LOG(LogTemp, Display, TEXT("[MAP] CHIAVE: %s"), *Element.Key);
			JsonFieldValidator(Element.Value, &Element.Key);
			break;
		}
	}

}

void UGegJsonIterator::JsonFieldValidator(const TSharedPtr<FJsonValue>& InValue, FString* Key)
{
	FString FieldValue;
	InValue->TryGetString(FieldValue);
	UE_LOG(LogTemp, Display, TEXT("Key: %s\tValue: %s"), **Key, *FieldValue);

	if (Key->Equals(TEXT("path"), ESearchCase::CaseSensitive))
	{
		JsWorker->SetPath(&FieldValue);
	}
	else if (Key->Equals(TEXT("end"), ESearchCase::CaseSensitive) && FieldValue.Equals(TEXT("create"), ESearchCase::CaseSensitive))
	{
		JsWorker->CreateMaterialAsset();
		
		FString Empty = FString::Printf(TEXT(""));
		JsWorker->SetName(&Empty);
		JsWorker->ResetColor();
	}
	else if (Key->Equals(TEXT("name"), ESearchCase::CaseSensitive))
	{
		JsWorker->SetName(&FieldValue);
	}
	else if (Key->Equals(TEXT("rgba"), ESearchCase::CaseSensitive))
	{
		JsWorker->SetColor(&FieldValue);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Key: *** with its Value: %s are not mapped..."), *FieldValue);
	}
}

UGegWorker* UGegJsonIterator::GetWorker()
{
	return JsWorker;
}
