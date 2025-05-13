// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include <cstdint>


class ILogger
{
public:
    virtual ~ILogger() = default;
    virtual bool IsDebugEnabled() = 0;
    virtual void SetDebugEnabled(bool enabled) = 0;
    virtual void LogInfo(const char* msg) const = 0;
    virtual void LogWarning(const char* msg) const = 0;
    virtual void LogError(const char* msg) const = 0;
    virtual void LogDebug(const char* msg) const = 0;
};

enum class WaveFormat : int
{
    WAVE_FORMAT_16BIT_PCM = 0,
    WAVE_FORMAT_32BIT_FLOAT = 1
};

struct SpeechOptions
{
    WaveFormat AudioFormat = WaveFormat::WAVE_FORMAT_32BIT_FLOAT;
    int ThreadNumbers = 1;
    int SampleRate = 24000;
    const char* AcousticModelFile = nullptr;
    int AcousticModelFileLen = 0;
    
    const char* VoCoderModelFile = nullptr;
    int VoCoderModelFileLen = 0;
    
    const char* FrontCnfFile = nullptr;
    int FrontCnfFileLen = 0;

    const char* G2pEncoderModelFile = nullptr;
    int G2pEncoderModelFileLen = 0;

    const char* G2pDecoderModelFile = nullptr;
    int G2pDecoderModelFileLen = 0;
};

enum class VadAggressive
{
    Normal = 0,
    LowBitrate = 1,
    Aggressive = 2,
    VeryAggressive = 3,
};

struct ReSampleResult
{
    bool Succeed = false;
    int SamplesPerChannel = 0;
    int DataSizeInBytes = 0;
};

enum class AudioFormat
{
    Float,
    FloatPlanar,
    Int16,
    Int16Planar
};

struct AudioProcOptions
{
    bool DenoiseEnabled = true;
    int NoiseDB = -25;
    bool EchoSuppressEnabled = false;
    bool AGCEnabled = false;
    float DeReverb = false;
    int EchoLengthInMills = 120;
};


class IMicrophoneStreamCallback
{
public:
    virtual ~IMicrophoneStreamCallback() = default;
    virtual void OnMicrophoneAudioCapture(
        AudioFormat format,
        const uint8_t* audio_data,
        int num_samples,
        int sample_rate,
        int num_channels,
        bool overflow) = 0;
};


class IRecognizerOutput
{
public:
    virtual ~IRecognizerOutput() = default;
    virtual const char* GetText() = 0;
   virtual  int GetTextLength() = 0;
    virtual void Release() = 0;
};
