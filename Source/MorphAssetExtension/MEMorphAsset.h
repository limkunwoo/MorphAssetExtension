#pragma once

#include "CoreMinimal.h"
#include "MEMorphAsset.generated.h"
UCLASS()
class MORPHASSETEXTENSION_API UMEMorphAsset : public UObject
{
	GENERATED_BODY()
public:
	UMEMorphAsset();

	UPROPERTY(EditAnywhere)
	TMap<FName, float> MorphTargets;
};
