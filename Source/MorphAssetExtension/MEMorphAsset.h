#pragma once

#include "CoreMinimal.h"
#include "MEMorphAsset.generated.h"

UENUM()
enum class ECharacterEquipType : uint8
{
	None,
	Face,
	Hair,
	Hand,
	Foot
};

UENUM()
enum class EPartsWearType : uint8
{
	None,
	Face1,
	Face2,
	Face3,
	Face4,
};

UENUM()
enum class EMultiAssetElementType : uint8
{
	FaceSubPartsEar,
	FaceSubPartsMouth,
	FaceSubPartsEyes,
	FaceSubPartsHead
};

USTRUCT()
struct FMESocketRef
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	ECharacterEquipType AttachTo;
	UPROPERTY(EditAnywhere)
	FName SocketName;
	UPROPERTY(EditAnywhere)
	FTransform Offset;
};
USTRUCT()
struct FPartsAssetElement
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (AllowedClasses="StaticMesh, SkeletalMesh"))
	FSoftObjectPath Asset;
	UPROPERTY(EditAnywhere)
	FMESocketRef Socket;
};

USTRUCT()
struct FPartsMeshGroup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<EMultiAssetElementType , FPartsAssetElement> AssetElement;
};
UCLASS()
class MORPHASSETEXTENSION_API UMEPartsAssetV2 : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<EPartsWearType, FPartsMeshGroup> WearTypeMap;
};

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

	UPROPERTY(EditAnywhere)
	FTransform TestTransform;
	UPROPERTY(EditAnywhere)
	FVector TestLocation;
	UPROPERTY(EditAnywhere, meta = (AllowedClasses="StaticMesh, SkeletalMesh"))
	FSoftObjectPath AssetTest;
	UPROPERTY(EditAnywhere, EditFixedSize, meta=(ReadOnlyKeys))
	TMap<EPartsWearType, FPartsMeshGroup> Parts;
};
