// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "speech_api.h"
#include "Modules/ModuleManager.h"
#include "ThirdPartyLibLoader.h"

class MEDIAPIPESPEECH_API IMediaPipeSpeechModule : public IModuleInterface
{
public:
	static IMediaPipeSpeechModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IMediaPipeSpeechModule>("MediaPipeSpeech");
	}
	
	virtual  FThirdPartyLibLoader& GetAPILibrary() = 0;
	virtual  FThirdPartyLibLoader& GetOVRLipSyncLibrary() = 0;
	virtual const FString& GetDataFolder() = 0;
	virtual const FString& GetTTSWorkDir() = 0;
	virtual const FString& GetASRWorkDir() = 0;
	virtual const FString& GetOVRLipSyncDataDir() = 0;

	virtual ILogger* GetAPILogger() = 0;
};
