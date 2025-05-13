// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ASRCaptureComponent.h"
#include "Components/AudioComponent.h"
#include "ASRSolution.generated.h"

class IASRSolution;

DECLARE_EVENT_ThreeParams(IASRSolution, FNativeTextRecognizedEvent, IASRSolution*, const FString&, bool);
DECLARE_EVENT_OneParam(IASRSolution, FNativeASRStoppedEvent, IASRSolution*);

// This class does not need to be modified.
UINTERFACE()
class UASRSolution : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDIAPIPESPEECH_API IASRSolution
{
	GENERATED_BODY()

public:
	virtual bool IsEnvironmentReady() = 0;
	virtual bool IsCapturing() = 0;
	virtual bool StartAudio(UAudioComponent* AudioComponent) = 0;
	virtual bool StartAudioCapture(UASRCaptureComponent* CaptureComponent) = 0;
	virtual bool StartMicrophone() = 0;
	virtual void Stop() = 0;

	virtual FNativeTextRecognizedEvent& GetNativeTextRecognizedEvent() = 0;
	virtual  FNativeASRStoppedEvent& GetNativeASRStoppedEvent() = 0;
};
