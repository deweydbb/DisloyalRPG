// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Disloyal_ARPGEditorTarget : TargetRules
{
	public Disloyal_ARPGEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("Disloyal_ARPG");
	}
}
