// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class FMEPreviewViewportClient;
/**
 * 
 */

class FMEMorphAssetEditor;
class FMorphAssetPreviewScene;

class MORPHASSETED_API SMEPreviewViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SMEPreviewViewport)
		{
		}
		SLATE_ARGUMENT(TWeakPtr<FMEMorphAssetEditor>, Editor)
		SLATE_ARGUMENT(TWeakPtr<FMorphAssetPreviewScene>, PreviewScene)
	SLATE_END_ARGS()
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
private:
	TWeakPtr<FMEMorphAssetEditor> Editor;
	TWeakPtr<FMorphAssetPreviewScene> PreviewScene;
	TSharedPtr<FMEPreviewViewportClient> ViewportClient;
};
