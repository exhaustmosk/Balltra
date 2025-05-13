// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpeechUtils.h"

#define GET_CONFIG_PARAM_OR_RTN_FALSE(VAR_NAME, ConfigMap, Key) \
if(!ConfigMap.Find(TEXT(Key))) \
{ \
	PLUGIN_LOG(Error, TEXT("Missing config parameter '%s'."), TEXT(Key)); \
	return false; \
} \
auto VAR_NAME = ConfigMap[TEXT(Key)];

// #define GET_CONFIG_FILE_PATH_OR_RTN_FALSE(VAR_NAME, ConfigMap, WorkDir, Key) \
// if(!ConfigMap.Find(TEXT(Key))) \
// { \
// 	PLUGIN_LOG(Error, TEXT("Missing config parameter '%s'."), TEXT(Key)); \
// 	return false; \
// } \
// auto VAR_NAME = FSpeechUtils::GetPathInWorkDir(WorkDir, ConfigMap[TEXT(Key)]);


/**
 * 
 */
class MEDIAPIPESPEECH_API FSpeechConfigReader
{
public:
	/**
	 * Read parameters from string, format ex:
	 * --a=b
	 * --d=c
	 * will get result: a:b, d:c
	 */
	static bool ReadConfigFile(const FString& FilePath, TMap<FString, FString>& NameAndValues);

	static bool ReadConfigParameterFromFile(const FString& FilePath, const FString& ParameterName, FString& Value);

	/**
	 * Read dictionary from string, format ex:
	 * A  D
	 * B  C
	 * will get result: A:D, B:C
	 */
	static bool ReadDictionaryFile(const FString& FilePath, TMap<FString, FString>& KeysAndValues);

private:
	static bool SplitStringView(const FStringView& View, FString& OutLeft, FString& OutRight);
};
