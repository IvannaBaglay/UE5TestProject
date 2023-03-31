// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Particles/ParticleSystemComponent.h" 
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraShakeBase.h" 

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = m_ProjectileMesh;

	m_TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticle"));
	m_TrailParticle->SetupAttachment(RootComponent);

	m_ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	m_ProjectileMovementComponent->InitialSpeed = 1200.f;
	m_ProjectileMovementComponent->MaxSpeed = 1200.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	m_ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (m_LaunchSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, m_LaunchSound, GetActorLocation(), GetActorRotation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	auto myOwner = GetOwner();
	if (myOwner == nullptr)
	{
		Destroy();
		return;
	}

	if (m_HitSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, m_HitSound, GetActorLocation(), GetActorRotation());
	}

	if (HitCameraShakeClass != nullptr)
	{
		// UE 4.25 - ClientPlayCameraShake; UE 4.26+ ClientStartCameraShake
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}


	auto myOwnerInstigator = myOwner->GetInstigatorController();

	auto damageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor != this && otherActor != myOwner)
	{
		UGameplayStatics::ApplyDamage(otherActor, m_Damage, myOwnerInstigator, this, damageTypeClass);
		if (m_HitParticles != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, m_HitParticles, GetActorLocation(), GetActorRotation());
		}
	}
	Destroy();

}
