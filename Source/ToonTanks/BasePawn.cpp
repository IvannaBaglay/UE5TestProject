// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"

#include "Components/StaticMeshComponent.h" 
#include "Components/CapsuleComponent.h" 
#include "Components/SceneComponent.h" 
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraShakeBase.h" 


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = m_CapsuleComp;

	m_BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	m_BaseMesh->SetupAttachment(m_CapsuleComp);
	m_TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	m_TurretMesh->SetupAttachment(m_BaseMesh);

	m_ProjecttileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Component"));
	m_ProjecttileSpawnPoint->SetupAttachment(m_TurretMesh);
}

void ABasePawn::RotateTurret(FVector lookAtTarget)
{
	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	FVector toTarget = lookAtTarget - m_TurretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.f, toTarget.Rotation().Yaw, 0.f);

	m_TurretMesh->SetWorldRotation(FMath::RInterpTo(m_TurretMesh->GetComponentRotation(), lookAtRotation, deltaTime, 5.f));

}

void ABasePawn::Fire()
{
	FVector spawnPoint = m_ProjecttileSpawnPoint->GetComponentLocation();
	FRotator spawnRotation = m_ProjecttileSpawnPoint->GetComponentRotation();

	auto projectile = GetWorld()->SpawnActor<AProjectile>(m_ProjectileClass, spawnPoint, spawnRotation);
	projectile->SetOwner(this);

}

void ABasePawn::HandleDestruction()
{
	// TODO: Visual/sound effects
	if (m_DeathBoom)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, m_DeathBoom, GetActorLocation(), GetActorRotation());
	}
	if (m_DeathSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, m_DeathSound, GetActorLocation(), GetActorRotation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}


}
