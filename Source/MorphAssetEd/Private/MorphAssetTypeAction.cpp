// Fill out your copyright notice in the Description page of Project Settings.


#include "MorphAssetTypeAction.h"

UClass* FMorphAssetTypeAction::GetSupportedClass() const
{
	return UMEMorphAsset::StaticClass();
}
