// Flynn's Rad Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "OnlineSubsystem.h"

#include "CIS_GameInstance.generated.h"

UCLASS()
class CIS_API UCIS_GameInstance : public UGameInstance
{
	GENERATED_BODY()
 
public:
    UFUNCTION(BlueprintCallable)
    virtual void Init();
    
    UFUNCTION(BlueprintCallable)
    void Host();
    
    UFUNCTION(BlueprintCallable)
    void Join();
    
private:
    IOnlineSessionPtr SessionInterface;
    TSharedPtr<class FOnlineSessionSearch> SessionSearch;
    
    void OnCreateSessionComplete(FName SessionName, bool Success);
    void OnDestroySessionComplete(FName SessionName, bool Success);
    void OnFindSessionsComplete(bool Success);
    
    void CreateSession();
};
