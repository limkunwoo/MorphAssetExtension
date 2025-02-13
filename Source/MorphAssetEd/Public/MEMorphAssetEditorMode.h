﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

/**
 * 
 */
class FMEMorphAssetEditor;

class MORPHASSETED_API FMEMorphAssetEditorMode : public FApplicationMode
{
public:
	FMEMorphAssetEditorMode(const TSharedRef<FMEMorphAssetEditor>& InMorphAssetEditor);
	virtual ~FMEMorphAssetEditorMode() override = default;

protected:
	FWorkflowAllowedTabSet TabFactories;
	TWeakPtr<FMEMorphAssetEditor> EditorPtr;
};
