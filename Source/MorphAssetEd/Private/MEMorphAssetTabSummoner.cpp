// Fill out your copyright notice in the Description page of Project Settings.


#include "MEMorphAssetTabSummoner.h"
#include "MorphAssetEdNames.h"
#include "MEMorphAssetEditor.h"
#include "AdvancedPreviewSceneModule.h"
#include "MEMorphAssetDetailCustomization.h"
#include "MEPreviewSceneDesc.h"
#include "MEPreviewSceneDescriptionCustomization.h"
#include "MEPreviewViewport.h"
#include "MorphAssetExtension/MEMorphAsset.h"

#define LOCTEXT_NAMESPACE "PersonaModes"

FMEPreviewSceneTabSummoner::FMEPreviewSceneTabSummoner(const TSharedPtr<FMEMorphAssetEditor>& InHostingApp, TSharedPtr<FMorphAssetPreviewScene> InScene) :
FWorkflowTabFactory(MorphAssetTabNames::MEPreviewTab, StaticCastSharedPtr<FAssetEditorToolkit>(InHostingApp)),
PreviewScene(InScene), Editor(InHostingApp)
{
	TabLabel = LOCTEXT("PreviewSceneSettingsTab", "Preview Scene Settings");
    TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details");	
    bIsSingleton = true;
    
    ViewMenuDescription = LOCTEXT("AdvancedPreviewScene", "Preview Scene Settings");
    ViewMenuTooltip = LOCTEXT("AdvancedPreviewScene_ToolTip", "Shows the advanced preview scene settings");
}

FMEPreviewSceneTabSummoner::~FMEPreviewSceneTabSummoner()
{
}

TSharedRef<SWidget> FMEPreviewSceneTabSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedRef<FMorphAssetPreviewScene> PreviewSceneRef = PreviewScene.Pin().ToSharedRef();

	TArray<FAdvancedPreviewSceneModule::FDetailCustomizationInfo> DetailsCustomizations;

	DetailsCustomizations.Add({ UMEPreviewSceneDesc::StaticClass(), FOnGetDetailCustomizationInstance::CreateSP(this, &FMEPreviewSceneTabSummoner::CustomizePreviewSceneDescription) });

	FAdvancedPreviewSceneModule& AdvancedPreviewSceneModule = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");
	return AdvancedPreviewSceneModule.CreateAdvancedPreviewSceneSettingsWidget(PreviewSceneRef, PreviewSceneRef->GetPreviewSceneDescription(), DetailsCustomizations);
}


FText FMEPreviewSceneTabSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return LOCTEXT("AdvancedPreviewSettingsToolTip", "The Advanced Preview Settings tab will let you alter the preview scene's settings.");
}

TSharedRef<class IDetailCustomization> FMEPreviewSceneTabSummoner::CustomizePreviewSceneDescription() const
{
	TSharedRef<FMorphAssetPreviewScene> PreviewSceneRef = PreviewScene.Pin().ToSharedRef();
	return MakeShared<FMEPreviewSceneDescriptionCustomization>(Editor.Pin().ToSharedRef(), PreviewSceneRef);
}


FMEViewportTabSummoner::FMEViewportTabSummoner(const TSharedPtr<FMEMorphAssetEditor>& InHostingApp,	TSharedPtr<FMorphAssetPreviewScene> InScene) :
FWorkflowTabFactory(MorphAssetTabNames::ViewportTab, StaticCastSharedPtr<FAssetEditorToolkit>(InHostingApp)),
PreviewScene(InScene), Editor(InHostingApp)
{
	TabLabel = FText::Format(LOCTEXT("ViewportTabTitle", "Viewport {0}"), FText::AsNumber(1));
	TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Viewports");

	bIsSingleton = true;

	ViewMenuDescription = FText::Format(LOCTEXT("ViewportViewFormat", "Viewport {0}"), FText::AsNumber(1));
	ViewMenuTooltip = LOCTEXT("ViewportView_ToolTip", "Shows the viewport");
}


TSharedRef<SWidget> FMEViewportTabSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedRef<SMEPreviewViewport> Viewport = SNew(SMEPreviewViewport)
												.Editor(Editor)
												.PreviewScene(PreviewScene.Pin());
	
	return Viewport;
}

FText FMEViewportTabSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FWorkflowTabFactory::GetTabToolTipText(Info);
}

FMEMorphAssetDetailTabSummoner::FMEMorphAssetDetailTabSummoner(const TSharedPtr<FMEMorphAssetEditor>& InHostingApp, TSharedPtr<FMorphAssetPreviewScene> InScene) :
	FWorkflowTabFactory(MorphAssetTabNames::Details, StaticCastSharedPtr<FAssetEditorToolkit>(InHostingApp))
	, Editor(InHostingApp)
	, PreviewScene(InScene)
{
	TabLabel = LOCTEXT("DetailsView_TabTitle", "Details");
	TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details");

	bIsSingleton = true;

	ViewMenuDescription = LOCTEXT("DetailsView_MenuTitle", "Details");
	ViewMenuTooltip = LOCTEXT("DetailsView_ToolTip", "Shows the details view");
}

FMEMorphAssetDetailTabSummoner::~FMEMorphAssetDetailTabSummoner()
{
}

TSharedRef<IDetailCustomization> FMEMorphAssetDetailTabSummoner::CustomizePreviewSceneDescription() const
{
	return MakeShareable(new SMEMorphAssetDetailCustomization(Editor.Pin().ToSharedRef(), PreviewScene.Pin().ToSharedRef(), Editor.Pin()->GetMorphAsset()));
}

TSharedRef<SWidget> FMEMorphAssetDetailTabSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	TSharedRef<IDetailsView> Details = PropertyModule.CreateDetailView(FDetailsViewArgs(false, true, true, FDetailsViewArgs::ObjectsUseNameArea));

	Details->RegisterInstancedCustomPropertyLayout(UMEMorphAsset::StaticClass(), FOnGetDetailCustomizationInstance::CreateSP(this, &FMEMorphAssetDetailTabSummoner::CustomizePreviewSceneDescription));
	Details->SetObject(Editor.Pin()->GetMorphAsset());
	
	return Details;
}

FText FMEMorphAssetDetailTabSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FWorkflowTabFactory::GetTabToolTipText(Info);
}

#undef LOCTEXT_NAMESPACE
