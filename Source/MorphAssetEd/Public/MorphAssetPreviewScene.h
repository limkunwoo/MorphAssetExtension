// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"

class UMEPreviewSceneDesc;

DECLARE_MULTICAST_DELEGATE(FOnInvalidateScene)
/**
 * 
 */
class MORPHASSETED_API FMorphAssetPreviewScene : public FAdvancedPreviewScene
{
public:
	FMorphAssetPreviewScene(const ConstructionValues& CVS, const TSharedPtr<class FMEMorphAssetEditor>& InEditor);
	virtual ~FMorphAssetPreviewScene() override;

	virtual void Tick(float InDeltaTime) override;
	void SetActor(AActor* InActor) { PreviewActor = InActor; }
	virtual void AddComponent(class UActorComponent* Component, const FTransform& LocalToWorld, bool bAttachToRoot = false) override;
	virtual void SetPreviewMeshComponent(USkeletalMeshComponent* InSkeletalMeshComponent);
	virtual USkeletalMeshComponent* GetPreviewMeshComponent() {return PreviewSkeletalMeshComponent; }
	virtual USkeletalMesh* GetPreviewMesh();
	virtual void SetPreviewMesh(USkeletalMesh* InPreviewMesh);
	UMEPreviewSceneDesc* GetPreviewSceneDescription() { return PreviewSceneDescription; }
	bool PreviewComponentSelectionOverride(const UPrimitiveComponent* InComponent) const;

	void InvalidateVeiw();
	FOnInvalidateScene OnInvalidateScene;
private:
	
	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override; 
	TObjectPtr<AActor> PreviewActor;
	TObjectPtr<USkeletalMeshComponent> PreviewSkeletalMeshComponent;
	TWeakPtr<class FMEMorphAssetEditor> Editor;
	TObjectPtr<UMEPreviewSceneDesc> PreviewSceneDescription;
};

