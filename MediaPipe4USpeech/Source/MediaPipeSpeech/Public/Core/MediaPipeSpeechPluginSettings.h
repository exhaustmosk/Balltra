// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MediaPipeSpeechPluginSettings.generated.h"

/**
 * 
 */
UCLASS(config = MediaPipeSpeech, DefaultConfig)
class MEDIAPIPESPEECH_API UMediaPipeSpeechPluginSettings : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(config, EditAnywhere, Category = "Debug", DisplayName="Debug Log")
	bool bDebugLogEnabled = false;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
