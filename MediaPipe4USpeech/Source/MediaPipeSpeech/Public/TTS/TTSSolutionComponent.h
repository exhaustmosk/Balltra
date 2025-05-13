// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TTSSampleRate.h"
#include "TTSSolution.h"
#include "Components/ActorComponent.h"
#include "TTSSolutionComponent.generated.h"



UCLASS(Abstract, ClassGroup=(MediaPipe))
class MEDIAPIPESPEECH_API UTTSSolutionComponent : public UActorComponent, public ITTSSolution
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTTSAudioFileSaved, const FString&, SavedFile);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TTS")
	int SpeakerId = 174;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TTS|Save")
	bool bSaveAudioFile = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TTS|Save")
	FString SaveAudioFilePath = "tts.wav";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TTS")
	ETTSSampleRate SampleRate = ETTSSampleRate::TTS_SR_24000;

	virtual bool ListSpeakers(TMap<FString, int>& OutSpeakers) override { return false; }

	virtual bool IsEnvironmentReady() override { return true; }
	// TTSSolution Interface
	virtual int32 GetSampleRate() override;
	virtual int GetSpeakerId() override;
	virtual void SetSpeakerId(int Id) override;
	virtual void RaiseWaveChunkReceivedEvent(TSharedRef<FWaveChunk> InWavChunk) override;
	virtual void RaiseInferenceCompletedEvent(const FGuid& SentenceId, ESpeechState State) override;

	UPROPERTY(Category="Runtime|Events", BlueprintAssignable)
	FTTSAudioFileSaved OnTTSAudioFileSaved; 

	virtual FTTSInferenceCompletedEvent& GetInferenceCompletedEvent() override;
	virtual FTTSWaveChunkReceivedEvent& GetWaveChunkReceivedEvent() override;

	virtual bool TextToSpeech(const FString& Sentence, FWaveClip& OutWav) override PURE_VIRTUAL(UTTSSolutionComponent::TextToSpeech, return false;)

	virtual ETTSLanguage GetLanguage() const override  PURE_VIRTUAL(, return ETTSLanguage::ZH;) 

	virtual EAudioDataFormat GetAudioFormat() override PURE_VIRTUAL(UTTSSolutionComponent::TextToSpeech, return EAudioDataFormat::Float32;)
protected:
	virtual void BeginPlay() override;
private:
	FTTSInferenceCompletedEvent InferenceCompletedEvent;
	FTTSWaveChunkReceivedEvent WaveChunkReceivedEvent;
};
