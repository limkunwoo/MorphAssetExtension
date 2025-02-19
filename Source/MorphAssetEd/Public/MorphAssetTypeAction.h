﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "MEMorphAssetEditor.h"
#include "MorphAssetExtension/MEMorphAsset.h"
/**
 * 
 */
class MORPHASSETED_API FMorphAssetTypeAction : public FAssetTypeActions_Base
{
public:
	virtual UClass* GetSupportedClass() const override;
	virtual FText GetName() const override { return FText::FromString("Morph Asset"); }
	virtual FColor GetTypeColor() const override { return FColor::Blue; }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; };

	virtual void OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) override
	{
		TSharedRef<FMEMorphAssetEditor> Editor = MakeShareable(new FMEMorphAssetEditor());
		Editor->InitMEMorphAssetEditor(EToolkitMode::Standalone,nullptr, Cast<UMEMorphAsset>(InObjects[0]));
	}
};
