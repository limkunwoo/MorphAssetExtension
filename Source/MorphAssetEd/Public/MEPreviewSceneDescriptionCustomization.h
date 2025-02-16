// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class FMorphAssetPreviewScene;
/**
 * 
 */
class FMEMorphAssetEditor;

class MORPHASSETED_API FMEPreviewSceneDescriptionCustomization : public IDetailCustomization
{
public:
	FMEPreviewSceneDescriptionCustomization(const TSharedRef<FMEMorphAssetEditor>& InEditor, const TSharedRef<FMorphAssetPreviewScene>& InPreviewScene);
	virtual ~FMEPreviewSceneDescriptionCustomization() override;
	bool HandleShouldFilterAsset(const FAssetData& AssetData);
	void HandleMeshChanged(const FAssetData& AssetData) const;
	virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;
private:
	TWeakPtr<FMEMorphAssetEditor> Editor;
	TWeakPtr<FMorphAssetPreviewScene> PreviewScene;
};
