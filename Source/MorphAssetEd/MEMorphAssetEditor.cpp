// Fill out your copyright notice in the Description page of Project Settings.


#include "MEMorphAssetEditor.h"
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
	InitAssetEditor(Mode, InitToolkotHost, MorphAssetEdNames::MEMorphAssetEditorAppName, FTabManager::FLayout::NullLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InMorphAsset);
}

void FMEMorphAssetEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(MorphAsset);
}
