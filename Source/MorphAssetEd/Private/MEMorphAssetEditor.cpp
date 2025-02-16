// Fill out your copyright notice in the Description page of Project Settings.


#include "MEMorphAssetEditor.h"
#include "MorphAssetPreviewScene.h"
#include "MEMorphAssetEditorMode.h"
#include "MorphAssetEdNames.h"
#include "Animation/DebugSkelMeshComponent.h"
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
	AActor* PreviewActor = PreviewScene->GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FTransform::Identity);
	PreviewScene->SetActor(PreviewActor);
	
	UDebugSkelMeshComponent* PreviewSkeletalComponent = NewObject<UDebugSkelMeshComponent>(PreviewActor);
	PreviewSkeletalComponent->SetUpdateAnimationInEditor(true);
	PreviewSkeletalComponent->bTickInEditor = true;
	
	PreviewScene->AddComponent(PreviewSkeletalComponent, FTransform::Identity);
	PreviewScene->SetPreviewMeshComponent(PreviewSkeletalComponent);
	PreviewActor->SetRootComponent(PreviewSkeletalComponent);
	
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
