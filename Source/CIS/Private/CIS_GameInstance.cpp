// Flynn's Rad Copyright.

#include "CIS_GameInstance.h"

#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

const static FName SESSION_NAME = TEXT("My Session Name");

void UCIS_GameInstance::Init()
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (Subsystem != nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("Found subsystem %s"), *Subsystem->GetSubsystemName().ToString());
        SessionInterface = Subsystem->GetSessionInterface();
        if(SessionInterface.IsValid())
        {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCIS_GameInstance::OnCreateSessionComplete);
            SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UCIS_GameInstance::OnDestroySessionComplete);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UCIS_GameInstance::OnFindSessionsComplete);
            
            SessionSearch = MakeShareable(new FOnlineSessionSearch());
            if(SessionSearch.IsValid())
            {
                SessionSearch->bIsLanQuery = true;
                UE_LOG(LogTemp, Warning, TEXT("Starting Find Session."));
                SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
            }
            UE_LOG(LogTemp, Warning, TEXT("Executing Init!"));
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));
    }
}

void UCIS_GameInstance::Host()
{
    if(SessionInterface.IsValid())
    {
        auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
        if(ExistingSession != nullptr)
        {
            SessionInterface->DestroySession(SESSION_NAME);
        }
        else
        {
            CreateSession();
        }
    }
}

void UCIS_GameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
    if(Success)
    {
        CreateSession();
    }
}

void UCIS_GameInstance::CreateSession()
{
    if(SessionInterface.IsValid())
    {
        FOnlineSessionSettings SessionSettings;
        SessionSettings.bIsLANMatch = true;
        SessionSettings.NumPublicConnections = 2;
        SessionSettings.bShouldAdvertise = true;
        SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
    }
}

void UCIS_GameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
    
}

void UCIS_GameInstance::OnFindSessionsComplete(bool Success)
{
    if(Success && SessionSearch.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Finished Find Session."));
        for(const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
        {
            UE_LOG(LogTemp, Warning, TEXT("Found session name: %s"), *SearchResult.GetSessionIdStr());
        }
    }
}

void UCIS_GameInstance::Join()
{
    
}
