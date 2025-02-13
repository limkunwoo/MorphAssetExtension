// Fill out your copyright notice in the Description page of Project Settings.


#include "MEMorphAssetEditor.h"
#include "MorphAssetPreviewScene.h"
#include "MEMorphAssetEditorMode.h"
#include "MorphAssetEdNames.h"
#include "MorphAssetExtension/MEMorphAsset.h"


FMEMorphAssetEditor::FMEMorphAssetEditor()
{
}

FMEMorphAssetEditor::~FMEMorphAssetEditor()
{
}
 
void FMEMorphAssetEditor::InitMEMorphAssetEditor(const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkotHost, UMEMorphAsset* InMorphAsset)
{
	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	MorphAsset = InMorphAsset;
	PreviewScene = MakeShared<FMorphAssetPreviewScene>(FPreviewScene::ConstructionValues().AllowAudioPlayback(true).ShouldSimulatePhysics(true), SharedThis(this));
	InitAssetEditor(Mode, InitToolkotHost, MorphAssetEdNames::MEMorphAssetEditorAppName, FTabManager::FLayout::NullLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InMorphAsset);
	AddApplicationMode(
			MorphAssetEdNames::MEMorphAssetEditorModeName,
			MakeShareable(new FMEMorphAssetEditorMode(SharedThis(this))));
	// Activate the initial mode (which will populate with a real layout)
	SetCurrentMode(MorphAssetEdNames::MEMorphAssetEditorModeName);
}

void FMEMorphAssetEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(MorphAsset);
}
