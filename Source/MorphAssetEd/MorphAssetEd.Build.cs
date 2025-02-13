using UnrealBuildTool;

public class MorphAssetEd : ModuleRules
{
    public MorphAssetEd(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "UnrealEd",
                "Slate",
                "SlateCore",
                "AssetTools",
                "MorphAssetExtension",
                "AdvancedPreviewScene"
            }
        );
    }
}