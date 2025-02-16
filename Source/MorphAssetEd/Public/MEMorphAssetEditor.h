// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MorphAssetPreviewScene.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

/**
 * 
 */
class UMEMorphAsset;
class FMorphAssetPreviewScene;

class MORPHASSETED_API FMEMorphAssetEditor : public FWorkflowCentricApplication, public FGCObject
{
public:
	FMEMorphAssetEditor();
	virtual ~FMEMorphAssetEditor() override;

	void InitMEMorphAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkotHost, UMEMorphAsset* InMorphAsset);
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override { return TEXT("MEMorphAssetEditor"); };

	virtual FName GetToolkitFName() const override { return TEXT("MEMorphAssetEditor"); }
	virtual FText GetBaseToolkitName() const override { return INVTEXT("ME Morph Asset Editor"); }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("ME Morph Asset "); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FColor::Blue; }
	TSharedPtr<FMorphAssetPreviewScene> GetMorphAssetPreviewScene() { return PreviewScene; };

	UMEMorphAsset* GetMorphAsset() { return MorphAsset; }
private:
	TObjectPtr<UMEMorphAsset> MorphAsset;
	TSharedPtr<FMorphAssetPreviewScene> PreviewScene;
};
