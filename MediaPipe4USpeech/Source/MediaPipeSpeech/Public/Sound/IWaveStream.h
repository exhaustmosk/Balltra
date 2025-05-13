// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "Misc/DateTime.h"
#include "WaveChunk.h"

class IWaveStream
{
public:
	virtual ~IWaveStream() = default;
	virtual void Reset() = 0;
	virtual void Stop() = 0;
	virtual void Start() = 0;
	virtual bool IsCompleted() = 0;
	virtual long GetUTCTimeCompleted() = 0;
	virtual bool HasData() = 0;
	
	virtual int32 PollAudio(float* OutAudio, int32 NumSamples) = 0;
	virtual bool PushChunk(const TSharedRef<FWaveChunk>& InChunk) = 0;
};
