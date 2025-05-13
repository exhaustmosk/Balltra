// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "ASRSolutionComponent.h"
#include "SpeechModelLoadingPolicy.h"
#include "SpeechModelState.h"
#include "LocalASRSolutionComponent.generated.h"

class IRecognizerAPI;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnASRModelsLoadCompleted, bool, Succeed);

UCLASS(ClassGroup=(MediaPipeSpeech), meta=(BlueprintSpawnableComponent))
class MEDIAPIPESPEECH_API ULocalASRSolutionComponent : public UASRSolutionComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	ULocalASRSolutionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR")
	ESpeechModelLoadingPolicy LoadModelOnStart = ESpeechModelLoadingPolicy::Async;

	UFUNCTION(BlueprintCallable, Category = "ASR")
	bool IsModelsLoaded();

	UFUNCTION(BlueprintCallable, Category="ASR")
	void LoadModelsAsync();

	UFUNCTION(BlueprintCallable, Category="ASR")
	bool LoadModels();

	UFUNCTION(BlueprintCallable, Category="ASR")
	bool UnLoadModels();

	UPROPERTY(Category="ASR|Events", BlueprintAssignable)
	FOnASRModelsLoadCompleted OnModelsLoadCompleted;

	virtual bool IsEnvironmentReady() override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void HandleAudioCapture(EAudioDataFormat Format, const uint8* AudioBuffer, const int32 SamplesPerChannel, const int32 NumChannels, const int32 InSampleRate, bool bIsFinish) override;
	virtual void OnStopped() override;
	//virtual bool HasSpeech(EAudioDataFormat Format, const uint8* AudioBuffer, const int32 SamplesPerChannel, const int32 NumChannels, int32 InSampleRate) override;
private:
	void RaiseModelsLoadCompleted(bool bSucceed) const;
	FCriticalSection LoadingMutex;
	IRecognizerAPI* RecognizerAPI = nullptr;
	bool bErrorShown = false;
	ESpeechModelState ModelState = ESpeechModelState::WaitToLoad;
	bool UnLoadModelsInternal(bool bLock);
	bool LoadModelsInternal(bool bForceLoad);
};

