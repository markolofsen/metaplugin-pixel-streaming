// Copyright 2022 Maxim Dudin. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class MetaEditor : ModuleRules
	{
		public MetaEditor(ReadOnlyTargetRules Target) : base(Target)
		{
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

			PrivateDependencyModuleNames.AddRange(
                new string[] { 
                    "Core", 
                    "CoreUObject",
                    "Engine",
                    "Json"
                }
            );
		}
	}
}
