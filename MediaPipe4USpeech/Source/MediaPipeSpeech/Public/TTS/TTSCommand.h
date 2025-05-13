// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "ASRSolutionComponent.h"
#include "SpeechSentence.h"
#include "TTSLanguage.h"
#include "TTSSolution.h"
#include "Core/tinywav.h"
#include "UObject/WeakInterfacePtr.h"


class FTTSCommand : public IQueuedWork
{
public:
	FTTSCommand(ITTSSolution* InSolution, const TSharedRef<FSpeechSentence>& InSentence);
	virtual ~FTTSCommand() override;

	virtual void DoThreadedWork() override;

	bool bSaveFile = false;
	FString SaveFilePath;
	ETTSLanguage Language = ETTSLanguage::ZH;
	virtual void Cancel();
	bool IsCompleted() const;
	FGuid GetSentenceId() const;
private:
	virtual void Abandon() override;
	bool Inference();
	void Execute();
	ITTSSolution* GetTTSSolution() const;
	void FlushAudioFile();
	bool bCanceled = false;
	int SpkID = -1;
	TWeakInterfacePtr<ITTSSolution> Solution;
	TSharedPtr<FSpeechSentence> Sentence;
	bool bCompleted = false;
	TUniquePtr<TinyWav> Wav;
};
