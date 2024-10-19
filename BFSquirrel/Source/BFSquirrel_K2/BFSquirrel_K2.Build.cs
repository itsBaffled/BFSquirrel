using UnrealBuildTool;

public class BFSquirrel_K2 : ModuleRules
{
    public BFSquirrel_K2(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseUnity = false;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "BlueprintGraph",
                "KismetCompiler",
                "UnrealEd",
                "GraphEditor",
                "BFSquirrel"

            }
        );
    }
}