// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "ASRSolutionComponent.h"
#include "WaveChunk.h"
#include "UObject/Interface.h"
#include "TTSSolution.generated.h"

class ITTSSolution;
class FTTSCommand;

UENUM(BlueprintType)
enum class ESpeechState : uint8
{
	Finished,
	Failed,
	Canceled
};

USTRUCT(BlueprintType)
struct MEDIAPIPESPEECH_API FWaveClip
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TTS")
	TArray<float> Data;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TTS")
	float DurationMills = 0.0f;
};

DECLARE_EVENT_TwoParams(ITTSSolution, FTTSInferenceCompletedEvent, const FGuid&,  ESpeechState)
DECLARE_EVENT_OneParam(ITTSSolution, FTTSWaveChunkReceivedEvent, const TSharedRef<FWaveChunk>&)

// This class does not need to be modified.
UINTERFACE()
class UTTSSolution : public UInterface
{
	GENERATED_BODY()
};
/**
 * 
 */
class MEDIAPIPESPEECH_API ITTSSolution
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsEnvironmentReady() = 0;
	virtual int GetSpeakerId() = 0;
	virtual void SetSpeakerId(int Id) = 0;
	virtual int32 GetSampleRate() =0;
	virtual EAudioDataFormat GetAudioFormat() =0;
	virtual ETTSLanguage GetLanguage() const = 0;
	virtual bool ListSpeakers(TMap<FString, int>& OutSpeakers) = 0;
	virtual  bool TextToSpeech(const FString& Sentence, FWaveClip& OutWav) = 0;
	
	virtual void RaiseWaveChunkReceivedEvent(TSharedRef<FWaveChunk> InWavChunk) = 0;
	virtual void RaiseInferenceCompletedEvent(const FGuid& SentenceId, ESpeechState State) = 0;

	virtual FTTSInferenceCompletedEvent& GetInferenceCompletedEvent() = 0;
	virtual FTTSWaveChunkReceivedEvent& GetWaveChunkReceivedEvent() = 0;
};
