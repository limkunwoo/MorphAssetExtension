// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"

class UMEPreviewSceneDesc;
/**
 * 
 */
class MORPHASSETED_API FMorphAssetPreviewScene : FAdvancedPreviewScene
{
public:
	FMorphAssetPreviewScene(const ConstructionValues& CVS, const TSharedPtr<class FMEMorphAssetEditor>& InEditor);
	virtual ~FMorphAssetPreviewScene() override;
private:
	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override; 
	TObjectPtr<AActor> PreviewActor;
	TWeakPtr<class FMEMorphAssetEditor> Editor;
	TObjectPtr<UMEPreviewSceneDesc> PreviewSceneDescription;
};
