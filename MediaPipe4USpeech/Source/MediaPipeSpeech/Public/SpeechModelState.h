// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "SpeechModelState.generated.h"

UENUM(BlueprintType)
enum class ESpeechModelState : uint8
{
	WaitToLoad,
	Loading,
	Loaded,
	LoadFailed,
};
