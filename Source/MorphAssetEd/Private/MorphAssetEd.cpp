#include "MorphAssetEd.h"
#include "MorphAssetTypeAction.h"
#include "MorphAssetExtension/MEMorphAsset.h"
#include "MorphAssetEd/MEMorphAssetEditor.h"

void FMorphAssetEdModule::StartupModule()
{
    MPATypeAction = MakeShared<FMorphAssetTypeAction>();
    FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(MPATypeAction.ToSharedRef());
}

void FMorphAssetEdModule::ShutdownModule()
{
    if (!FModuleManager::Get().IsModuleLoaded(TEXT("AssetTools")))
    {
        return;
    }
    FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(MPATypeAction.ToSharedRef());
}

TSharedRef<FMEMorphAssetEditor> FMorphAssetEdModule::CreateMorphAssetEditor(const EToolkitMode::Type Mode,
    const TSharedPtr<IToolkitHost>& InitToolkitHost, UMEMorphAsset* InAsset)
{
    TSharedRef<FMEMorphAssetEditor> MorphAssetEditor(new FMEMorphAssetEditor());
    MorphAssetEditor->InitMEMorphAssetEditor( Mode, InitToolkitHost, InAsset);
    return MorphAssetEditor;
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FMorphAssetEdModule, MorphAssetEd)