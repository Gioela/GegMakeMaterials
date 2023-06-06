#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "Json.h"
#include "GegJsonIterator.generated.h"

UCLASS()
class MATERIALMASSIVECREATOR_API UGegJsonIterator : public UObject
{
	GENERATED_BODY()


public:
	UGegJsonIterator();

	void ProcessInputFile(const FString& InFile);
	void MapExplorer(const TMap<FString, TSharedPtr<FJsonValue>>& InMap);
	void JsonFieldValidator(const TSharedPtr<FJsonValue>& InValue, FString* Key);

	class UGegWorker* GetWorker();

protected:
	class UGegWorker* JsWorker;
};
