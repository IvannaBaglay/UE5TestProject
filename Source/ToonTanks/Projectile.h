// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


class UStaticMeshComponent;
class UProjectileMovementComponent;
class UPrimitiveComponent;
class UCameraShake;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* m_ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float m_Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat");
	class UParticleSystem* m_HitParticles;

	UPROPERTY(VisibleAnywhere, Category = "Combat");
	class UParticleSystemComponent* m_TrailParticle;

	UPROPERTY(EditAnywhere, Category = "Combat");
	class USoundBase* m_LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat");
	USoundBase* m_HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

};
