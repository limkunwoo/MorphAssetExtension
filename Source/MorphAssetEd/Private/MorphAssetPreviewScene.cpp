// Fill out your copyright notice in the Description page of Project Settings.


#include "MorphAssetPreviewScene.h"

#include "MEPreviewSceneDesc.h"
#include "Animation/DebugSkelMeshComponent.h"


FMorphAssetPreviewScene::FMorphAssetPreviewScene(const ConstructionValues& CVS, const TSharedPtr< FMEMorphAssetEditor>& InEditor) : FAdvancedPreviewScene(CVS), Editor(InEditor)
{
	PreviewSceneDescription = NewObject<UMEPreviewSceneDesc>(GetTransientPackage());
	PreviewSceneDescription->SetFlags(RF_Transactional);
}

FMorphAssetPreviewScene::~FMorphAssetPreviewScene()
{
}

void FMorphAssetPreviewScene::Tick(float InDeltaTime)
{
	GetWorld()->Tick(ELevelTick::LEVELTICK_All, InDeltaTime);
	FAdvancedPreviewScene::Tick(InDeltaTime);
}

void FMorphAssetPreviewScene::AddComponent(class UActorComponent* Component, const FTransform& LocalToWorld,
                                           bool bAttachToRoot)
{
	if (bAttachToRoot)
    {
        if (USceneComponent* SceneComponent = Cast<USceneComponent>(Component))
        {
        	SceneComponent->AttachToComponent(PreviewActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
        }
    }
    PreviewActor->AddOwnedComponent(Component);
	FAdvancedPreviewScene::AddComponent(Component, LocalToWorld, bAttachToRoot);
}

void FMorphAssetPreviewScene::SetPreviewMeshComponent(USkeletalMeshComponent* InSkeletalMeshComponent)
{
	PreviewSkeletalMeshComponent = InSkeletalMeshComponent; 

	if(PreviewSkeletalMeshComponent)
	{
		PreviewSkeletalMeshComponent->SelectionOverrideDelegate = UPrimitiveComponent::FSelectionOverride::CreateRaw(this, &FMorphAssetPreviewScene::PreviewComponentSelectionOverride);
		PreviewSkeletalMeshComponent->PushSelectionToProxy();	
	}
}

USkeletalMesh* FMorphAssetPreviewScene::GetPreviewMesh()
{
	return PreviewSceneDescription->PreviewMesh;
}

void FMorphAssetPreviewScene::SetPreviewMesh(USkeletalMesh* InPreviewMesh)
{
	PreviewSceneDescription->PreviewMesh = InPreviewMesh;
	UDebugSkelMeshComponent* DebugSkeletalMeshComp = Cast<UDebugSkelMeshComponent>(PreviewSkeletalMeshComponent);
	
	DebugSkeletalMeshComp->SetSkeletalMesh(InPreviewMesh);
	DebugSkeletalMeshComp->bTickInEditor = true;
	DebugSkeletalMeshComp->SetUpdateAnimationInEditor(true);
	DebugSkeletalMeshComp->InitAnim(true);

	DebugSkeletalMeshComp->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

bool FMorphAssetPreviewScene::PreviewComponentSelectionOverride(const UPrimitiveComponent* InComponent) const
{
	if (InComponent == PreviewSkeletalMeshComponent)
	{
		const USkeletalMeshComponent* Component = CastChecked<USkeletalMeshComponent>(InComponent);
		return (Component->GetSelectedEditorSection() != INDEX_NONE || Component->GetSelectedEditorMaterial() != INDEX_NONE);
	}
	return false;
}
void FMorphAssetPreviewScene::InvalidateVeiw()
{
	OnInvalidateScene.Broadcast();
}

void FMorphAssetPreviewScene::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(PreviewSceneDescription);
	Collector.AddReferencedObject(PreviewSkeletalMeshComponent);
	Collector.AddReferencedObject(PreviewActor);
	FAdvancedPreviewScene::AddReferencedObjects(Collector);
}
