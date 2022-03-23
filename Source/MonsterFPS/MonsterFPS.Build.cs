// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MonsterFPS : ModuleRules
{
	public MonsterFPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
