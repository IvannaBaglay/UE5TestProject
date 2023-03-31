// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	m_Health = m_MaxHealth;
	// ...
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	m_ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::DamageTaken(AActor* damageActor, float damage, const UDamageType* damageType, AController* instigator, AActor* damageCauser)
{
	if (damage <= 0.f)
	{
		return;
	}
	m_Health -= damage;

	if (m_Health <= 0.f)
	{
		if (damageActor != nullptr)
		{
			m_ToonTanksGameMode->ActorDied(damageActor);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("HEalth %f"), m_Health);
}



// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

