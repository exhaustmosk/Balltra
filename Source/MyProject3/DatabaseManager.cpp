#include "DatabaseManager.h"
#include "DatabaseHelper.h"  // Include the helper file
#include <string>

ADatabaseManager::ADatabaseManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADatabaseManager::BeginPlay()
{
	Super::BeginPlay();
}

void ADatabaseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADatabaseManager::ExecuteSQLQuery(const FString& Query, FString& Result)
{
	// Convert FString to std::string for the helper function
	std::string StdQuery = TCHAR_TO_UTF8(*Query);
	std::string StdResult;

	// Call the helper function
	bool Success = DatabaseHelper::RunSQLQuery(StdQuery, StdResult);

	// Convert the result back to FString
	Result = UTF8_TO_TCHAR(StdResult.c_str());

	return Success;
}
