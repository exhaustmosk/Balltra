#pragma once

#include "CoreMinimal.h"

class IAssetTypeActions;

class FMediaPipeSpeechEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TSharedPtr<IAssetTypeActions> OculusLipSyncRemapAsseAction;
};
