// Fill out your copyright notice in the Description page of Project Settings.


#include "MEPreviewViewport.h"

#include "MEMorphAssetEditor.h"
#include "MEPreviewViewportClient.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<FEditorViewportClient> SMEPreviewViewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable(new FMEPreviewViewportClient(Editor.Pin().ToSharedRef(), PreviewScene.Pin().ToSharedRef(), SharedThis(this)));
	return ViewportClient.ToSharedRef();
}

void SMEPreviewViewport::Construct(const FArguments& InArgs)
{
	Editor = InArgs._Editor;
	PreviewScene = InArgs._Editor.Pin()->GetMorphAssetPreviewScene();
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
