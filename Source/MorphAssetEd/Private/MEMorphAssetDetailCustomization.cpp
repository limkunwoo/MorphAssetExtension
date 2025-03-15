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
	PreviewScene.Pin()->InvalidateVeiw();
}

void SMEMorphAssetDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	MyDetailLayout = &DetailBuilder;
	ValidateMorphTargetList(Editor.Pin()->GetMorphAsset());
	PreviewScene.Pin()->SetPreviewMesh(Editor.Pin()->GetMorphAsset()->TargetMesh);
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

	AddTestPartsAssetCategory(DetailBuilder);
}
void SMEMorphAssetDetailCustomization::AddTestPartsAssetCategory(IDetailLayoutBuilder& DetailBuilder)
{
	TSharedRef<IPropertyHandle> PartsMeshProperty = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UMEMorphAsset, Parts));
	
	DetailBuilder.EditCategory(TEXT("PartsAsset Category"))
		.AddCustomRow(FText::FromString("TestPartsAsset"))
		.RowTag(TEXT("PartsAssetWearTypes"))
		.NameContent()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[ 
			SNew(STextBlock).Text(FText::FromString("AddAssetElement"))
		]
		.ValueContent()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
				.Text(FText::FromString(TEXT("메시 파츠 추가")))
				//.ToolTipText(LOCTEXT("AddLODLevelCategories_MaterialArrayOpAdd_Tooltip", "Add Material Slot at the end of the Material slot array. Those Material slots can be used to override a LODs section, (not the base LOD)"))
				.ContentPadding(4.0f)
				.ForegroundColor(FSlateColor::UseForeground())
				//.OnClicked(this, &FPersonaMeshDetails::AddMaterialSlot)
				.IsEnabled(true)
				.IsFocusable(false)
				[
					SNew(SImage)
					.Image(FAppStyle::GetBrush("Icons.PlusCircle"))
					.ColorAndOpacity(FSlateColor::UseForeground())
				]
			]
		];
	PartsMeshProperty->MarkHiddenByCustomization();
	uint32 NumChild;
	PartsMeshProperty->GetNumChildren(NumChild);
	for (uint32 i = 0; i < NumChild; i++)
	{
		TSharedPtr<IPropertyHandle> MeshGroupMapValueHandle = PartsMeshProperty->GetChildHandle(i);
		TSharedPtr<IPropertyHandle> AssetElementMapHandle = MeshGroupMapValueHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FPartsMeshGroup, AssetElement));
		TSharedPtr<IPropertyHandle> WearTypeKeyHandle = PartsMeshProperty->GetChildHandle(i)->GetKeyHandle();

		UEnum* WearTypeEnum = StaticEnum<EPartsWearType>();
		void* WearTypeKey;
		WearTypeKeyHandle->GetValueData(WearTypeKey);
		FString CategoryName = *WearTypeEnum->GetDisplayNameTextByValue(*(uint8*)WearTypeKey).ToString();
		DetailBuilder.EditCategory(*CategoryName)
			.AddCustomRow(FText::FromString("WearTypeElement"))
			.WholeRowContent()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Center)
			[
				CreateAssetElementCustomWidget(DetailBuilder, AssetElementMapHandle.ToSharedRef())
			];
	}
	
}

TSharedRef<SWidget> SMEMorphAssetDetailCustomization::CreateAssetElementCustomWidget(const IDetailLayoutBuilder& DetailBuilder, const TSharedRef<IPropertyHandle>& AssetElementMapHandle)
{
	TSharedRef<SVerticalBox> AssetElementBox = SNew(SVerticalBox);
	uint32 NumChild;
	AssetElementMapHandle->GetNumChildren(NumChild);
	for (uint32 i = 0; i < NumChild; i++)
	{
		auto MeshElementHandle =  AssetElementMapHandle->GetChildHandle(i);

		auto ObjectPathHandle = MeshElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FPartsAssetElement, Asset));
		auto MESocketRefHandle = MeshElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FPartsAssetElement, Socket));

		auto AttachEquipSlotHandle = MESocketRefHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMESocketRef, AttachTo));
		auto SocketNameHandle = MESocketRefHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMESocketRef, SocketName));
		auto SocketOffsetTransformHandle = MESocketRefHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMESocketRef, Offset));

		AssetElementBox->AddSlot()
		[
			SNew(SBorder)
			.Content()
			[
				SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							[
								SNew(STextBlock).Text(FText::FromString(TEXT("단일 에셋 타입")))
							]
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							+SHorizontalBox::Slot()
							[
								MeshElementHandle->GetKeyHandle()->CreatePropertyValueWidget()	
							]
							
						]
						+ SVerticalBox::Slot()
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							[
								SNew(STextBlock).Text(FText::FromString(TEXT("에셋")))
							]
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							+SHorizontalBox::Slot()
							[
								SNew(SObjectPropertyEntryBox)
								.AllowedClass(UObject::StaticClass())
								.PropertyHandle(ObjectPathHandle)
								.ThumbnailPool(DetailBuilder.GetThumbnailPool())	
							]	
						]
						.AutoHeight()	
					]
					.AutoWidth()
					.Padding(4, 0)
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.Padding(4, 0)
					.FillWidth(1)
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							[
								AttachEquipSlotHandle->CreatePropertyNameWidget()
							]
							+SHorizontalBox::Slot()
							[
								AttachEquipSlotHandle->CreatePropertyValueWidget()
							]
							.HAlign(HAlign_Fill)
							.FillWidth(1)
						]
						+SVerticalBox::Slot()
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							[
								SocketNameHandle->CreatePropertyNameWidget()
							]
							+SHorizontalBox::Slot()
							[
								SocketNameHandle->CreatePropertyValueWidget()
							]
							.HAlign(HAlign_Fill)
							.FillWidth(1)
						]
						+SVerticalBox::Slot()
				        [
				            SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(0)->CreatePropertyNameWidget()
							]
							+SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(0)->GetChildHandle(0)->CreatePropertyValueWidget()
							]
				            .HAlign(HAlign_Fill)
				            .FillWidth(1)
				            +SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(0)->GetChildHandle(1)->CreatePropertyValueWidget()
							]
				            .HAlign(HAlign_Fill)
							.FillWidth(1)
				            +SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(0)->GetChildHandle(2)->CreatePropertyValueWidget()
							]
				            .HAlign(HAlign_Fill)
				            .FillWidth(1)
				        ]
						+SVerticalBox::Slot()
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(1)->CreatePropertyNameWidget()
							]
							+SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(1)->GetChildHandle(0)->CreatePropertyValueWidget()
							]
							.HAlign(HAlign_Fill)
							.FillWidth(1)
							+SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(1)->GetChildHandle(1)->CreatePropertyValueWidget()
							]
							.HAlign(HAlign_Fill)
							.FillWidth(1)
							+SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(1)->GetChildHandle(2)->CreatePropertyValueWidget()
							]
							.HAlign(HAlign_Fill)
							.FillWidth(1)
						]
						+SVerticalBox::Slot()
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(2)->CreatePropertyNameWidget()
							]
							+SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(2)->GetChildHandle(0)->CreatePropertyValueWidget()
							]
							.HAlign(HAlign_Fill)
							.FillWidth(1)
							+SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(2)->GetChildHandle(1)->CreatePropertyValueWidget()
							]
							.HAlign(HAlign_Fill)
							.FillWidth(1)
							+SHorizontalBox::Slot()
							[
								SocketOffsetTransformHandle->GetChildHandle(2)->GetChildHandle(2)->CreatePropertyValueWidget()
							]
							.HAlign(HAlign_Fill)
							.FillWidth(1)
						]
					]
				]
			];
	}
	
	return AssetElementBox;
}

void SMEMorphAssetDetailCustomization::HandleMeshChanged(const FAssetData& AssetData) const
{
	USkeletalMesh* NewPreviewMesh = Cast<USkeletalMesh>(AssetData.GetAsset());
	MorphAsset->TargetMesh = NewPreviewMesh;
	ValidateMorphTargetList(MorphAsset);
	PreviewScene.Pin()->SetPreviewMesh(NewPreviewMesh);
	MyDetailLayout->ForceRefreshDetails();
}

void SMEMorphAssetDetailCustomization::ValidateMorphTargetList(UMEMorphAsset* ObjectToEdit) const
{
	if (ObjectToEdit->TargetMesh == nullptr)
	{
		ObjectToEdit->MorphTargets.Empty();
		return;
	}
	TSet<FName> DesiredMorphTargets;	
	for(UMorphTarget* MorphTarget : ObjectToEdit->TargetMesh->GetMorphTargets())
	{
		DesiredMorphTargets.Add(FName(MorphTarget->GetName()));
		ObjectToEdit->MorphTargets.FindOrAdd(FName(MorphTarget->GetName()));
	}

	TSet<FName> CurrentMorphTargets;
	ObjectToEdit->MorphTargets.GetKeys(CurrentMorphTargets);

	TSet ToRemove = CurrentMorphTargets.Difference(DesiredMorphTargets);
	for (FName RemoveTargetName : ToRemove)
	{
		ObjectToEdit->MorphTargets.Remove(RemoveTargetName);
	}
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
