// Fill out your copyright notice in the Description page of Project Settings.


#include "MEMorphAssetFactory.h"

#include "MorphAssetExtension/MEMorphAsset.h"

UMEMorphAssetFactory::UMEMorphAssetFactory()
{
	SupportedClass = UMEMorphAsset::StaticClass();
	bCreateNew = true;
}

UObject* UMEMorphAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
                                                UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UMEMorphAsset>(InParent, Class, Name, Flags, Context);
}
