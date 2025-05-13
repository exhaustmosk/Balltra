// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioCaptureCore.h"
#include "HAL/ThreadSafeBool.h"
#include "Components/SynthComponent.h"
#include "ASRCaptureComponent.generated.h"


/**
 * float* : audio buffer
 * int32: num of samples
 * int32: channels
 * int32: sample rate
 */
UCLASS(ClassGroup=(MediaPipeSpeech), meta=(BlueprintSpawnableComponent))
class MEDIAPIPESPEECH_API UASRCaptureComponent : public USynthComponent
{
	GENERATED_BODY()
	
	DECLARE_EVENT_FourParams(UASRCaptureComponent, FAudioBufferGeneratedEvent, const float*, int32, int32, int32)
public:

	FAudioBufferGeneratedEvent& GetAudioBufferGeneratedEvent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Latency", meta = (ClampMin = "0", ClampMax = "1024"))
	int32 JitterLatencyFrames = 0;
protected:
	virtual void OnBeginGenerate() override;
	virtual void OnEndGenerate() override;
	//~ End USynthComponent interface

	//~ Begin UObject interface
	virtual void BeginDestroy() override;
	virtual bool IsReadyForFinishDestroy() override;
	virtual void FinishDestroy() override;
	//~ End UObject interface
	
	virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;
	virtual bool Init(int32& SampleRate) override;

private:
	Audio::FAudioCaptureSynth& GetCaptureSynth();
	int32 GenerateAudio(float* OutAudio, int32 NumSamples);
	int32 CurrentSampleRate = 0;
	FAudioBufferGeneratedEvent AudioBufferGeneratedEvent;
	TUniquePtr<Audio::FAudioCaptureSynth> CaptureSynth;
	TArray<float> CaptureAudioData;
	int32 CapturedAudioDataSamples = 0;
	//Copy from audio capture
	bool bSuccessfullyInitialized = false;
	bool bIsCapturing = false;
	bool bIsStreamOpen = false;
	int32 CaptureChannels = 0;
	int32 FramesSinceStarting = 0;
	int32 ReadSampleIndex = 0;
	FThreadSafeBool bIsDestroying;
	FThreadSafeBool bIsNotReadyForForFinishDestroy;
};
