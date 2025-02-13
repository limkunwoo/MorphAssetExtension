// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MEPreviewSceneDesc.generated.h"

/**
 * 
 */
UCLASS()
class MORPHASSETED_API UMEPreviewSceneDesc : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(DisplayThumbnail=true))
	USkeletalMesh* PreviewMesh;
};
