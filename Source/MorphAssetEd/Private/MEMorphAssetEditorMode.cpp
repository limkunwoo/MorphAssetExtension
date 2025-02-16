// Fill out your copyright notice in the Description page of Project Settings.


#include "MEMorphAssetEditorMode.h"

#include "MEMorphAssetEditor.h"
#include "MEMorphAssetTabSummoner.h"
#include "MorphAssetEdNames.h"

FMEMorphAssetEditorMode::FMEMorphAssetEditorMode(const TSharedRef<FMEMorphAssetEditor>& InMorphAssetEditor) : FApplicationMode(MorphAssetEdNames::MEMorphAssetEditorModeName), EditorPtr(InMorphAssetEditor)
{
	PreviewScenePtr = InMorphAssetEditor->GetMorphAssetPreviewScene();
	TabLayout = FTabManager::NewLayout("Standalone_MorphAssetEditMode_Layout")
	->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				// Main application area
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					// Left side
					FTabManager::NewStack()
						->SetHideTabWell(true)
						->AddTab(MorphAssetTabNames::ViewportTab, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetHideTabWell(false)
					->SetSizeCoefficient(0.2f)
					->AddTab(MorphAssetTabNames::Details, ETabState::OpenedTab)
					->AddTab(MorphAssetTabNames::MEPreviewTab, ETabState::OpenedTab)
					->SetForegroundTab(MorphAssetTabNames::Details)
				)
			) 
		);

	TabFactories.RegisterFactory(MakeShared<FMEViewportTabSummoner>(InMorphAssetEditor.ToSharedPtr(), PreviewScenePtr.Pin()));
	TabFactories.RegisterFactory(MakeShared<FMEPreviewSceneTabSummoner>(InMorphAssetEditor.ToSharedPtr(), PreviewScenePtr.Pin()));
	TabFactories.RegisterFactory(MakeShared<FMEMorphAssetDetailTabSummoner>(InMorphAssetEditor.ToSharedPtr(), PreviewScenePtr.Pin()));
}

void FMEMorphAssetEditorMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	EditorPtr.Pin()->PushTabFactories(TabFactories);
}

