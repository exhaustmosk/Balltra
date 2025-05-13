using UnrealBuildTool;



public class MediaPipeSpeech : ModuleRules
{
	public MediaPipeSpeech(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.NoPCHs;
		bUsePrecompiled = true;
		PrecompileForTargets = PrecompileTargetsType.None;
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"Engine",
				"AudioMixer", 
				"AudioCapture",
				"AudioCaptureCore",
				"OVRLipSyncLibrary", 
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Projects",
				"SpeechAPI",
				"AnimGraphRuntime",
				"OVRLipSyncLibrary", 
				"MediaPipe",
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
		
		PublicIncludePaths.AddRange(
			new string[]
			{
				"$(ModuleDir)/Public/Core",
				"$(ModuleDir)/Public/TTS",
				"$(ModuleDir)/Public/ASR",
				"$(ModuleDir)/Public/Sound",
			});  
		
		if (!bUsePrecompiled)
		{
			PrivateIncludePathModuleNames.AddRange(new string[] { "MediaPipe" });
		}
		
		if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))
		{
#if UE_5_3_OR_LATER
			PrivateDependencyModuleNames.Add("AudioCaptureWasapi");
#endif
			PrivateDependencyModuleNames.Add("AudioCaptureRtAudio");
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PrivateDependencyModuleNames.Add("AudioCaptureRtAudio");
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PrivateDependencyModuleNames.Add("AudioCaptureAudioUnit");
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.Add("AudioCaptureAndroid");
		}
	}
}
