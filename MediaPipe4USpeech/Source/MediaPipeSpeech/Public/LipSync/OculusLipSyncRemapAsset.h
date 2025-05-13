// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "LipSyncVisemes.h"
#include "OculusLipSyncRemapAsset.generated.h"

UCLASS(BlueprintType, NotBlueprintable, hideCategories=Object)
class MEDIAPIPESPEECH_API UOculusLipSyncRemapAsset : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName SIL = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName PP = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName FF = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName TH = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName DD = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName KK = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName CH = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName SS = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName NN = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName RR = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName AA = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName E = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName I = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName O = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves")
	FName U = NAME_None;

	FName GetVisemeCurveName(ELipSyncViseme Viseme);
};
