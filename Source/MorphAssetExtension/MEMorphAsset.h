#pragma once

#include "CoreMinimal.h"
#include "MEMorphAsset.generated.h"
UCLASS()
class MORPHASSETEXTENSION_API UMEMorphAsset : public UObject
{
	GENERATED_BODY()
public:
	UMEMorphAsset();
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = Mesh)
	USkeletalMesh* TargetMesh = nullptr;
#endif
	UPROPERTY(EditAnywhere)
	TMap<FName, float> MorphTargets;
};
