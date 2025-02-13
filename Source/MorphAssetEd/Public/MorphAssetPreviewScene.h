// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"

/**
 * 
 */
class MORPHASSETED_API FMorphAssetPreviewScene : FAdvancedPreviewScene
{
public:
	FMorphAssetPreviewScene(const ConstructionValues& CVS);
	virtual ~FMorphAssetPreviewScene() override;
private:
	TObjectPtr<AActor> PreviewActor;
};
