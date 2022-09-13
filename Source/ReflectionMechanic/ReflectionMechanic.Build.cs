// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ReflectionMechanic : ModuleRules
{
	public ReflectionMechanic(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
