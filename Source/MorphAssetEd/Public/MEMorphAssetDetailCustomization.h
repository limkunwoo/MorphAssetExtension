// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "Widgets/SCompoundWidget.h"

class UMEMorphAsset;
class FMorphAssetPreviewScene;
class FMEMorphAssetEditor;
/**
 * 
 */
class MORPHASSETED_API SMEMorphAssetDetailCustomization : public IDetailCustomization
{
public:
	SLATE_BEGIN_ARGS(SMEMorphAssetDetailCustomization)
		{
		}

	SLATE_END_ARGS()
	SMEMorphAssetDetailCustomization(const TSharedRef<FMEMorphAssetEditor>& InEditor, const TSharedRef<FMorphAssetPreviewScene>& InPreviewScene, UMEMorphAsset* InMorphAsset);
	bool HandleShouldFilterAsset(const FAssetData& AssetData);
	void HandleValueChanged(float X, FName TargetName);
	virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;

	virtual void HandleMeshChanged(const FAssetData& AssetData) const;

private:
	TWeakPtr<FMEMorphAssetEditor> Editor;
	TWeakPtr<FMorphAssetPreviewScene> PreviewScene;
	UMEMorphAsset* MorphAsset;
};
