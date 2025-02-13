// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootDemo : ModuleRules
{
	public ShootDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"UMG", 
			"MoviePlayer", 
			"AIModule",
			"NavigationSystem",
			"GameplayTasks"
		});
        //PrivateDependencyModuleNames.AddRange(new string[] { "AIModule" });
    }
}
