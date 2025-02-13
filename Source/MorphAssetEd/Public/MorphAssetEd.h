#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMorphAssetTypeAction;
class IToolkitHost;
class UMEMorphAsset;
class FMEMorphAssetEditor;

class FMorphAssetEdModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    TSharedRef<FMEMorphAssetEditor> CreateMorphAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMEMorphAsset* InAsset);

    TSharedPtr<FMorphAssetTypeAction> MPATypeAction;
};
