// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class FMEMorphAssetEditor;
class FMorphAssetPreviewScene;
/**
 * 
 */
class MORPHASSETED_API FMEPreviewSceneTabSummoner : public FWorkflowTabFactory
{
public:
	FMEPreviewSceneTabSummoner(const TSharedPtr<FMEMorphAssetEditor>& InHostingApp, TSharedPtr<FMorphAssetPreviewScene> InScene);
	virtual ~FMEPreviewSceneTabSummoner() override;

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

	/** Customize the details of the scene setup object */
	TSharedRef<class IDetailCustomization> CustomizePreviewSceneDescription() const;
	/** Customize a preview mesh collection entry */
	TSharedRef<class IPropertyTypeCustomization> CustomizePreviewMeshCollectionEntry();
	
	TWeakPtr<FMorphAssetPreviewScene> PreviewScene;
	TWeakPtr<FMEMorphAssetEditor> Editor;
};

class MORPHASSETED_API FMEViewportTabSummoner : public FWorkflowTabFactory
{
public:
	FMEViewportTabSummoner(const TSharedPtr<FMEMorphAssetEditor>& InHostingApp, TSharedPtr<FMorphAssetPreviewScene> InScene);
	virtual ~FMEViewportTabSummoner() override = default;

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;
	TWeakPtr<FMorphAssetPreviewScene> PreviewScene;
	TWeakPtr<FMEMorphAssetEditor> Editor;
};

class MORPHASSETED_API FMEMorphAssetDetailTabSummoner : public FWorkflowTabFactory
{
public:
	FMEMorphAssetDetailTabSummoner(const TSharedPtr<FMEMorphAssetEditor>& InHostingApp, TSharedPtr<FMorphAssetPreviewScene> InScene);
	virtual ~FMEMorphAssetDetailTabSummoner() override;

	TSharedRef<IDetailCustomization> CustomizePreviewSceneDescription() const;
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

private:	
	TWeakPtr<FMEMorphAssetEditor> Editor;
	TWeakPtr<FMorphAssetPreviewScene> PreviewScene;
};
