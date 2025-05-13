// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASRSolution.h"
#include "ASRCaptureComponent.h"
#include "AudioCaptureDeviceInterface.h"
#include "EVadAggressive.h"
#include "speech_api.h"
#include "TTSLanguage.h"
#include "Components/ActorComponent.h"
#include "ASRSolutionComponent.generated.h"

class IAudioUtils;

typedef struct TinyWav TinyWav;

UENUM(BlueprintType)
enum class EAudioDataFormat : uint8
{
	Int16,
	Float32
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTextRecognized, const FString&, Text, bool, bIsFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnASRCaptureStopped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioFileRecorded, const FString&, FilePath);

UCLASS(Abstract, ClassGroup=(MediaPipe))
class MEDIAPIPESPEECH_API UASRSolutionComponent : public UActorComponent, public IASRSolution, public IMicrophoneStreamCallback
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UASRSolutionComponent();

	virtual bool StartAudio(UAudioComponent* AudioComponent) override;

	virtual bool StartAudioCapture(UASRCaptureComponent* CaptureComponent) override;

	virtual bool StartMicrophone() override;

	virtual bool IsEnvironmentReady() override { return true; }

	UFUNCTION(BlueprintCallable, Category = "ASR Capture",
			  Meta = (Tooltip = "Stop recognize audio."))
	virtual void Stop() override;

	UFUNCTION(BlueprintCallable, Category = "ASR Capture")
	virtual bool IsCapturing() override;

	UFUNCTION(BlueprintCallable, Category = "ASR Capture")
	virtual bool HasSpeech();
	
	UFUNCTION(BlueprintCallable, Category="ASR Capture")
	int32 GetCaptureSampleRate() const;

	UFUNCTION(BlueprintCallable, Category = "ASR Capture")
	int GetCaptureNumOfChannels();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR")
	FString ConfigFile = "asr.conf";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR", meta=(EditCondition = "bVadEnabled"))
	EVadAggressive VadLevel = EVadAggressive::Aggressive;
	/**
	 * Voice sample rate; It must be consistent with the sampling rate of ASR model.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR|Sampling")
	int SampleRate = 16000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR|Sampling")
	int SampleChannels = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR")
	bool bVadEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR|Save")
	bool bSaveAudioFile = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR|Save")
	FString SaveAudioFilePath = "asr.wav";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR|Denoise")
	bool bDeNoise = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR|Denoise", meta=(ClampMin=-100, ClampMax=0, EditCondition="bDeNoise"))
	int NoiseInDB = -25;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR|EndPoint", meta=(ClampMin=1, ClampMax=60))
	float MaxVoiceSeconds = 60.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ASR|EndPoint", meta=(EditCondition = "bVadEnabled", ClampMin=0.1, ClampMax=3.0f))
	float MaxSilenceSeconds = 0.8f;

	//Blueprint Events
	UPROPERTY(Category="ASR|Events", BlueprintAssignable)
	FOnTextRecognized OnTextRecognized;

	UPROPERTY(Category="ASR|Events", BlueprintAssignable)
	FOnAudioFileRecorded OnAudioFileRecorded;

	//Blueprint Events
	UPROPERTY(Category="ASR|Events", BlueprintAssignable)
	FOnASRCaptureStopped OnCaptureStopped;
	
	virtual FNativeTextRecognizedEvent& GetNativeTextRecognizedEvent() override;
	virtual FNativeASRStoppedEvent& GetNativeASRStoppedEvent() override;

protected:
	void FlushAudioFile();
	virtual void OnStopped() {}
	virtual void BeforeStart();
	virtual void OnStarted();
	virtual bool DetectSpeech(EAudioDataFormat Format, const uint8* AudioBuffer, const int32 SamplesPerChannel, const int32 NumChannels, int32 InSampleRate);
	virtual void HandleAudioCapture(EAudioDataFormat Format, const uint8* AudioBuffer, const int32 SamplesPerChannel, const int32 NumChannels, const int32 InSampleRate, bool bIsFinish) PURE_VIRTUAL(,)
	void RaiseTextRecognizedEvent(const FString& Text, bool bFinished);
	void RaiseCaptureStoppedEvent();
	void RaiseAudioFileRecordedEvent(FString InAudioFile);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	enum class EAudioInputType
	{
		None,
		AudioComponent,
		AudioCaptureComponent,
		Microphone
	};
	
	EAudioDataFormat SampleFormat = EAudioDataFormat::Int16;

	EAudioInputType CurrentAudioType =  EAudioInputType::None;
	int ReSampleAudio(const uint8* AudioData, int SamplesPerChannels, uint8** OutBuffer, int SourceSampleRate, int SourceNumChannels, EAudioDataFormat SampleType);
	bool NeedResample(int32 SrcNumChannels, int32 SrcSampleRate) const;
private:
	
	bool SoundGetMaxSilence(const uint8* AudioBuffer, const int32 SamplesPerChannels, bool& bHasSpeech);
	void FilterAudio(EAudioDataFormat Format, const uint8* AudioBuffer, const int32 NumSamples, const int32 NumChannels, const int32 InSampleRate);
	void FlushAudioBuffer(bool bIsFinish);
	void WriteSilenceSamples(float DurationSeconds = 0.1f);
	void ProcessAudio(const uint8* AudioBuffer, int32 SamplesPerChannel, bool bIsFinish);
	void OnAudioPlaybackPercent(const UAudioComponent* AudioComponent, const USoundWave* SoundWave, float Percent);
	void OnCaptureAudio(const float* AudioData, int32 NumSamples, int32 NumChannels, int32 InSampleRate);
	bool GetDefaultAudioInputDevice();
	void WriteWavFile(const uint8* AudioData, int32 SamplesPerChannel, int32 NumChannels, EAudioDataFormat SampleType) const;

	virtual void OnMicrophoneAudioCapture(AudioFormat format, const uint8_t* audio_data, int num_samples,
	                                      int sample_rate, int num_channels, bool overflow) override;

	bool IsMicrophoneCapturing();
	void SaveSession();
private:
	struct FCaptureSession
	{
		int32 SampleRate;
		int32 SampleChannels;
		EAudioDataFormat Format;
		bool bDeNoise;
		int32 SamplesPerChannel;
		bool bProcessorReady;
	};
	
	UPROPERTY(Transient)
	TObjectPtr<UASRCaptureComponent> CurrentAudioCapture;
	UPROPERTY(Transient)
	TObjectPtr<UAudioComponent> CurrentAudioInput;
	
	FCriticalSection CaptureCriticalSection;
	Audio::FCaptureDeviceInfo DefaultDevice;

	int32 LatestWaveIndex = 0;
	float LatestSeconds = 0;
	TArray<float> WaveBuffer;
	bool bShowErrorInCapturing = false;

	FNativeTextRecognizedEvent NativeTextRecognizedEvent;
	FNativeASRStoppedEvent NativeASRStoppedEvent;
	IAudioUtils* AudioUtils = nullptr;
	float SilenceElapsedSeconds = 0;
	bool bStopping = false;
	TArray<uint8> AudioFrame;
	int AudioFrameBytesPerChannel = 0;
	bool bIsRecordingFile;
	FString AudioFile;
	TinyWav* TinyWavPtr;
	FCaptureSession Session;
	bool bSpeechDetected = false;
	bool bNeedFillSilenceData = false;
};


