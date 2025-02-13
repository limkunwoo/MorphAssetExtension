// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "MEMorphAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class MORPHASSETED_API UMEMorphAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	UMEMorphAssetFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
