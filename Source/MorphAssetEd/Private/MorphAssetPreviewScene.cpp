// Fill out your copyright notice in the Description page of Project Settings.


#include "MorphAssetPreviewScene.h"

#include "MEPreviewSceneDesc.h"


FMorphAssetPreviewScene::FMorphAssetPreviewScene(const ConstructionValues& CVS, const TSharedPtr< FMEMorphAssetEditor>& InEditor) : FAdvancedPreviewScene(CVS), Editor(InEditor)
{
	PreviewSceneDescription = NewObject<UMEPreviewSceneDesc>(GetTransientPackage());
	PreviewSceneDescription->SetFlags(RF_Transactional);
}

FMorphAssetPreviewScene::~FMorphAssetPreviewScene()
{
}

void FMorphAssetPreviewScene::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(PreviewSceneDescription);
	Collector.AddReferencedObject(PreviewActor);
	FAdvancedPreviewScene::AddReferencedObjects(Collector);
}
