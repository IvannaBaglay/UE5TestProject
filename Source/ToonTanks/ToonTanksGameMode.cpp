// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"


void AToonTanksGameMode::ActorDied(AActor* deadActor)
{
    if (deadActor == m_Tank)
    {
        m_Tank->HandleDestruction();
        if (m_ToonTanksPlayerController)
        {
            m_ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if (ATower* destroyedTower = Cast<ATower>(deadActor))
    {
        destroyedTower->HandleDestruction();
        m_TargetTowers--;
        if (m_TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    m_TargetTowers = GetTargetTowers();
    m_Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    m_ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (m_ToonTanksPlayerController!= nullptr)
    {
        m_ToonTanksPlayerController->SetPlayerEnabledState(false);
        FTimerHandle playerEnableTimerHandle;

        FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(m_ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

        GetWorldTimerManager().SetTimer(playerEnableTimerHandle, timerDelegate, m_StartDelay, false);

    }

}

int AToonTanksGameMode::GetTargetTowers()
{
    TArray<AActor*> towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);

    return towers.Num();

}