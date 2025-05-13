// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "SpeechModelLoadingPolicy.generated.h"

UENUM(BlueprintType)
enum class ESpeechModelLoadingPolicy : uint8
{
	Disabled,
	Async,
	Sync
};
