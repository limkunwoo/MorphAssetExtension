﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MEPreviewViewportClient.h"

#include "MEMorphAssetEditor.h"
#include "MorphAssetPreviewScene.h"
#include "MEPreviewViewport.h"

FMEPreviewViewportClient::FMEPreviewViewportClient(const TSharedRef<FMEMorphAssetEditor>& InEditor, const TSharedRef<FMorphAssetPreviewScene>& InPreviewScene, const TSharedRef<SMEPreviewViewport>& InViewport) :
	FEditorViewportClient(&InEditor->GetEditorModeManager(), &InPreviewScene.Get(), StaticCastSharedRef<SEditorViewport>(InViewport)),
	Editor(InEditor), PreviewScene(InPreviewScene), Viewport(InViewport)
{
	FEditorViewportClient::SetViewMode(VMI_Lit);
	PreviewScene.Pin()->OnInvalidateScene.AddRaw(this, &FMEPreviewViewportClient::InvalidateView);
}

FMEPreviewViewportClient::~FMEPreviewViewportClient()
{
}

void FMEPreviewViewportClient::Tick(float DeltaTime)
{
	FEditorViewportClient::Tick(DeltaTime);
}

void FMEPreviewViewportClient::InvalidateView()
{
	Invalidate();
}
