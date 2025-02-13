// Fill out your copyright notice in the Description page of Project Settings.


#include "MEMorphAssetEditorMode.h"
#include "../MEMorphAssetEditor.h"
#include "MorphAssetEdNames.h"

FMEMorphAssetEditorMode::FMEMorphAssetEditorMode(const TSharedRef<FMEMorphAssetEditor>& InMorphAssetEditor) : FApplicationMode(MorphAssetEdNames::MEMorphAssetEditorModeName), EditorPtr(InMorphAssetEditor)
{
}

