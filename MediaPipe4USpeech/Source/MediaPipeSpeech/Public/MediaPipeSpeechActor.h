// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "TTSSolution.h"
#include "GameFramework/Actor.h"
#include "LocalTTSSolutionComponent.h"
#include "SpeechSynthComponent.h"
#include "UObject/WeakInterfacePtr.h"
#include "LocalASRSolutionComponent.h"
#include "TTSSpeaker.h"
#include "LipSync/LipSyncComponent.h"
#include "MediaPipeSpeechActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTTSInferenceCompleted, const FGuid&, SentenceId,  ESpeechState, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTTSWaveChunkReceived, const FWaveChunk&, WavChunk);

UCLASS(ClassGroup=MediaPipeSpeech, Blueprintable, BlueprintType)
class MEDIAPIPESPEECH_API AMediaPipeSpeechActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMediaPipeSpeechActor();
	
	UFUNCTION(BlueprintCallable, Category="TTS")
	FGuid GetCurrentSentenceId() const;

	UFUNCTION(BlueprintCallable, Category="TTS")
	bool SpeakText(const FString& Text, bool StopPrevious = true);
	
	UFUNCTION(BlueprintCallable, Category="TTS")
	bool SetTTSSolution(const TScriptInterface<ITTSSolution>& Solution);
	
	UFUNCTION(BlueprintCallable, Category="TTS")
	void StopSpeak();

	UFUNCTION(BlueprintCallable, Category="ASR")
	bool StartASR();
	
	UFUNCTION(BlueprintCallable, Category="ASR", meta=(ToolTip="Start aduio capturing with default micrphone."))
	virtual bool StartASRWithAudio(UAudioComponent* AudioComponent);
	
	UFUNCTION(BlueprintCallable, Category="ASR")
	bool SetASRSolution(const TScriptInterface<IASRSolution>& Solution);

	UFUNCTION(BlueprintCallable, Category="ASR")
	void StopASR();

	UFUNCTION(BlueprintCallable, Category="ASR")
	bool IsASRCapturing();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ASR")
	TObjectPtr<ULocalASRSolutionComponent> LocalASRSolution;

	UFUNCTION(BlueprintCallable, Category="TTS")
	bool ListTTSSpeakers(TArray<FTTSSpeaker>& Speakers);

	UFUNCTION(BlueprintCallable, Category="TTS")
	int GetTTSSpeakerId();

	UFUNCTION(BlueprintCallable, Category="TTS")
	int SetTTSSpeakerId(int SpeakerId);

	UFUNCTION(BlueprintCallable, Category="TTS")
	bool IsTTSReady() const;

	UFUNCTION(BlueprintCallable, Category="ASR")
	bool IsASRReady() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TTS")
	TObjectPtr<ULocalTTSSolutionComponent> LocalTTSSolution;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USpeechSynthComponent> Synth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<ULipSyncComponent> LipSync;
	
	UPROPERTY(Category="TTS|Events", BlueprintAssignable)
	FOnTTSInferenceCompleted OnTTSCompleted;
	
	UPROPERTY(Category="TTS|Events", BlueprintAssignable)
	FOnTTSWaveChunkReceived OnTTSWaveReceived;
	
	UFUNCTION(Category="TTS", BlueprintCallable)
	bool IsTTSSpeaking() const;

	bool SetTTSSolutionUObject(ITTSSolution* Solution);
	bool SetTTSSolutionNative(TSharedRef<ITTSSolution>& Solution);

	bool SetASRSolutionUObject(IASRSolution* Solution);
	void SetASRSolutionNative(TSharedRef<IASRSolution>& Solution);


	//Blueprint Events
	UPROPERTY(Category="ASR|Events", BlueprintAssignable)
	FOnTextRecognized OnTextRecognized;

	FNativeTextRecognizedEvent& OnNativeTextRecognized();
	
	bool IsLocalASRUsed() const;

	bool IsLocalTTSUsed() const;
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginDestroy() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	ITTSSolution* GetCurrentTTSSolution() const;
	IASRSolution* GetCurrentASRSolution() const;
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
private:
	void SafeStop();
	void HandleLipSyncFrame(const TSharedPtr<FOVRLipSyncFrame>& Frame);
	void OnSolutionCompleted(const FGuid& SentenceId, ESpeechState State);
	void OnTTSWaveChunkReceived( const TSharedRef<FWaveChunk>& WaveChunk) const;
	bool DoSpeak(const FString& Text, ITTSSolution* Solution);
	void OnASRTextRecognized(IASRSolution* Solution, const FString& Text, bool bFinished);
	void OnASRStopped(IASRSolution* Solution);
	bool DoStartASR(IASRSolution* Solution, UAudioComponent* Audio, UASRCaptureComponent* AudioCapture);
	FGuid CurrentSentenceId;
	TSharedPtr<FTTSCommand> PeekBusyCommand();
	TSharedPtr<FTTSCommand> ExecuteNextCommand();
	TQueue<TSharedPtr<FTTSCommand>> ExecutionQueue;
	TQueue<TSharedPtr<FTTSCommand>> PendingQueue;
	TMap<FGuid, TSharedPtr<FTTSCommand>> Tasks;
	FRWLock CommandsMutex;
	
	//solutions
	bool bIsNativeTTSSolution = true;
	TWeakInterfacePtr<ITTSSolution> TTSObjectSolution;
	TSharedPtr<ITTSSolution> TTSNativeSolution;

	bool bIsNativeASRSolution = true;
	TWeakInterfacePtr<IASRSolution> ASRObjectSolution;
	TSharedPtr<IASRSolution> ASRNativeSolution;
	bool bStopPrevious = true;
	FNativeTextRecognizedEvent NativeTextRecognizedEvent;
};

