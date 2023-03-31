// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h" 


void ATower::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    if (InFireRange())
    {
        RotateTurret(m_Tank->GetActorLocation());
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    m_Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(m_FireRateTimerHande, this, &ATower::CheckFireCondition, m_FireRate, true);

}

void ATower::CheckFireCondition()
{
    if (InFireRange() && m_Tank->bAlive)
    {
        Fire();
    }
}


bool ATower::InFireRange() const
{
    if (m_Tank != nullptr)
    {
        float distance = FVector::Dist(GetActorLocation(), m_Tank->GetActorLocation());
        return distance <= m_FireRange;
    }
    return false;
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}
