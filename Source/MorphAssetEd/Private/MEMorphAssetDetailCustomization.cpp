// Fill out your copyright notice in the Description page of Project Settings.


#include "MEMorphAssetDetailCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "MEMorphAssetEditor.h"
#include "PropertyCustomizationHelpers.h"
#include "SlateOptMacros.h"
#include "MorphAssetExtension/MEMorphAsset.h"
#include "Widgets/Input/SSlider.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SMEMorphAssetDetailCustomization::SMEMorphAssetDetailCustomization(const TSharedRef<FMEMorphAssetEditor>& InEditor, const TSharedRef<FMorphAssetPreviewScene>& InPreviewScene, UMEMorphAsset* InMorphAsset)
	: Editor(InEditor)
	, PreviewScene(InPreviewScene)
	, MorphAsset(InMorphAsset)
{
	
}

bool SMEMorphAssetDetailCustomization::HandleShouldFilterAsset(const FAssetData& AssetData)
{
	return false;
}

void SMEMorphAssetDetailCustomization::HandleValueChanged(float X, FName TargetName)
{
	Editor.Pin()->GetMorphAsset()->MorphTargets[TargetName] = X;
	PreviewScene.Pin()->GetPreviewMeshComponent()->SetMorphTarget(TargetName, X);
}

void SMEMorphAssetDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TSharedRef<IPropertyHandle> SkeletalMeshProperty = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UMEMorphAsset, TargetMesh));
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
			.OnShouldFilterAsset(this, &SMEMorphAssetDetailCustomization::HandleShouldFilterAsset)
			.OnObjectChanged(this, &SMEMorphAssetDetailCustomization::HandleMeshChanged)
			.ThumbnailPool(DetailBuilder.GetThumbnailPool())
		];

	TSharedRef<IPropertyHandle> MorphTargetMapProperty = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UMEMorphAsset, MorphTargets));
	MorphTargetMapProperty->MarkHiddenByCustomization();
	UMEMorphAsset* ObjectToEdit = Cast<UMEMorphAsset>(DetailBuilder.GetSelectedObjects()[0].Get());
	
	if (ObjectToEdit->TargetMesh)
	{
		for (UMorphTarget* MorphTarget : ObjectToEdit->TargetMesh->GetMorphTargets())
		{
			ObjectToEdit->MorphTargets.FindOrAdd(FName(MorphTarget->GetName()));	
		}	
	}
	
	TSharedRef<SVerticalBox> MorphTargetVerticalBox = SNew(SVerticalBox);
	for (auto& [Name, Value] : ObjectToEdit->MorphTargets)
	{
		MorphTargetVerticalBox->AddSlot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					MorphTargetMapProperty->CreatePropertyNameWidget(FText::FromName(Name))
				]
				+SHorizontalBox::Slot()
				[
					SNew(SSlider)
					.MinValue(0.0f)
					.MaxValue(1.0f)
					.Value(Value)
					.OnValueChanged(FOnFloatValueChanged::CreateSP(StaticCastSharedRef<SMEMorphAssetDetailCustomization>(AsShared()), &SMEMorphAssetDetailCustomization::HandleValueChanged, Name))
				]
		];
	}
	 //MorphTargetMapProperty->AsMap()->GetElement(0)->
	//DetailBuilder.EditCategory(TEXT("MorphTargets")).AddCustomRow(FText::FromString(TEXT("row"))).ValueCon
	DetailBuilder.EditCategory(TEXT("MorphTargets"))
		.AddProperty(MorphTargetMapProperty)
		.CustomWidget()
		.WholeRowContent()
		[
			MorphTargetVerticalBox
		];
}

void SMEMorphAssetDetailCustomization::HandleMeshChanged(const FAssetData& AssetData) const
{
	USkeletalMesh* NewPreviewMesh = Cast<USkeletalMesh>(AssetData.GetAsset());
	PreviewScene.Pin()->SetPreviewMesh(NewPreviewMesh);
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
