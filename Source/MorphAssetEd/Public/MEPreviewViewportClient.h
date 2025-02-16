// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class SMEPreviewViewport;
class FMorphAssetPreviewScene;
class FMEMorphAssetEditor;
/**
 * 
 */
class MORPHASSETED_API FMEPreviewViewportClient : public FEditorViewportClient, public TSharedFromThis<FMEPreviewViewportClient>
{
public:
	FMEPreviewViewportClient(const TSharedRef<FMEMorphAssetEditor>& InEditor, const TSharedRef<FMorphAssetPreviewScene>& InPreviewScene, const TSharedRef<SMEPreviewViewport>& InViewport);
	~FMEPreviewViewportClient();

private:
	TWeakPtr<FMEMorphAssetEditor> Editor;
	TWeakPtr<FMorphAssetPreviewScene> PreviewScene;
	TWeakPtr<SMEPreviewViewport> Viewport;
};
