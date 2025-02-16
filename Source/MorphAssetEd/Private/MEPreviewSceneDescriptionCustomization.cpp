// Fill out your copyright notice in the Description page of Project Settings.


#include "MEPreviewSceneDescriptionCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "MEPreviewSceneDesc.h"
#include "MorphAssetPreviewScene.h"
#include "PropertyCustomizationHelpers.h"

#define LOCTEXT_NAMESPACE "AnimationEditorPreviewScene"

FMEPreviewSceneDescriptionCustomization::FMEPreviewSceneDescriptionCustomization(
	const TSharedRef<FMEMorphAssetEditor>& InEditor, const TSharedRef<FMorphAssetPreviewScene>& InPreviewScene)
	: Editor(InEditor), PreviewScene(InPreviewScene)
{
}

FMEPreviewSceneDescriptionCustomization::~FMEPreviewSceneDescriptionCustomization()
{
}

bool FMEPreviewSceneDescriptionCustomization::HandleShouldFilterAsset(const FAssetData& AssetData)
{
	return false;
}

void FMEPreviewSceneDescriptionCustomization::HandleMeshChanged(const FAssetData& AssetData) const
{
	USkeletalMesh* NewPreviewMesh = Cast<USkeletalMesh>(AssetData.GetAsset());
	PreviewScene.Pin()->SetPreviewMesh(NewPreviewMesh);
}

void FMEPreviewSceneDescriptionCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TSharedRef<IPropertyHandle> SkeletalMeshProperty = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UMEPreviewSceneDesc, PreviewMesh));
	SkeletalMeshProperty->MarkHiddenByCustomization();
	
	FText PreviewMeshName = SkeletalMeshProperty->GetPropertyDisplayName();

	DetailBuilder.EditCategory("Mesh")
		.AddProperty(SkeletalMeshProperty)
		.CustomWidget()
		.OverrideResetToDefault(FResetToDefaultOverride::Create(
			TAttribute<bool>::CreateLambda([PreviewSceneWeakPtr = PreviewScene]()
			{
				if (PreviewSceneWeakPtr.IsValid())
				{
					return PreviewSceneWeakPtr.Pin()->GetPreviewMesh() != nullptr;
				}
				return false;
			}),
			FSimpleDelegate::CreateLambda([PreviewSceneWeakPtr = PreviewScene]()
			{
				if (PreviewSceneWeakPtr.IsValid())
				{
					PreviewSceneWeakPtr.Pin()->SetPreviewMesh(nullptr);
				}
			}))
		)
		.NameContent()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SkeletalMeshProperty->CreatePropertyNameWidget(PreviewMeshName)
			]
		]
		.ValueContent()
		.MaxDesiredWidth(250.0f)
		.MinDesiredWidth(250.0f)
		[
			SNew(SObjectPropertyEntryBox)
			.AllowedClass(USkeletalMesh::StaticClass())
			.PropertyHandle(SkeletalMeshProperty)
			.OnShouldFilterAsset(this, &FMEPreviewSceneDescriptionCustomization::HandleShouldFilterAsset)
			.OnObjectChanged(this, &FMEPreviewSceneDescriptionCustomization::HandleMeshChanged)
			.ThumbnailPool(DetailBuilder.GetThumbnailPool())
		];
}
#undef LOCTEXT_NAMESPACE