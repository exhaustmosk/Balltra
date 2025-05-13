// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "SpeechModelLoadingPolicy.h"
#include "SpeechModelState.h"
#include "TTSSolutionComponent.h"
#include "LocalTTSSolutionComponent.generated.h"

class ISpeechAPI;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTTSModelsLoadCompleted, bool, Succeed);

UCLASS(ClassGroup=(MediaPipeSpeech), meta=(BlueprintSpawnableComponent))
class MEDIAPIPESPEECH_API ULocalTTSSolutionComponent : public UTTSSolutionComponent
{
	GENERATED_BODY()
	DECLARE_DELEGATE(FOnStopped)
public:
	// Sets default values for this component's properties
	ULocalTTSSolutionComponent();

	/*Text front profile for acoustic model*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TTS")
	FString ConfigFile = "tts.conf";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TTS")
	ESpeechModelLoadingPolicy LoadModelOnStart = ESpeechModelLoadingPolicy::Async;

	UPROPERTY(Category="ASR|Events", BlueprintAssignable)
	FOnTTSModelsLoadCompleted OnModelsLoadCompleted;

	UFUNCTION(BlueprintCallable, Category="TTS")
	bool LoadModels();

	UFUNCTION(BlueprintCallable, Category="TTS")
	bool UnLoadModels();

	UFUNCTION(BlueprintCallable, Category="TTS")
	void LoadModelsAsync();

	UFUNCTION(BlueprintCallable, Category="TTS")
	bool IsModelsLoaded();

	virtual bool TextToSpeech(const FString& Sentence, FWaveClip& OutWav) override;

	virtual bool ListSpeakers(TMap<FString, int>& OutSpeakers) override;

	virtual EAudioDataFormat GetAudioFormat() override;

	UFUNCTION(BlueprintCallable, Category="TTS")
	virtual int32 GetSampleRate() override;

	virtual int GetSpeakerId() override;

	virtual bool IsEnvironmentReady() override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual ETTSLanguage ParseLanguage(const FString& LanguageName) const;
	virtual ETTSLanguage GetLanguage() const override;
private:
	
	bool LoadModelsInternal(bool bForceLoad);
	bool UnLoadModelsInternal(bool bLock);
	bool LoadSpeakers(const FString& ConfigFileFullPath);
	TMap<FString, int> Speakers;
	mutable FCriticalSection SendMutex;
	ISpeechAPI* SpeechAPI;
	FCriticalSection LoadMutex;
	ESpeechModelState ModeState = ESpeechModelState::WaitToLoad;
	int32 SampleRate = 24000;
	ETTSLanguage Language = ETTSLanguage::Known;
};
