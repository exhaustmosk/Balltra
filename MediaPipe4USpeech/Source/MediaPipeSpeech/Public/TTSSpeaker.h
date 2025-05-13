// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "TTSSpeaker.generated.h"

USTRUCT(BlueprintType)
struct FTTSSpeaker
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TTS")
	int Id = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TTS")
	FString Name{};
};
