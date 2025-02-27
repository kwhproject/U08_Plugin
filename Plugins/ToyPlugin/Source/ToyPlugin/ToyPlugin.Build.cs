// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ToyPlugin : ModuleRules
{
	public ToyPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"EditorStyle",
				"Projects",
				"GameplayDebugger",
				"DesktopPlatform",
				"MainFrame",
				"UnrealEd",
				"AdvancedPreviewScene",
				"InputCore",
				"PropertyEditor",
				"AssetTools",
				"Toy"
			});
		
	}
}
