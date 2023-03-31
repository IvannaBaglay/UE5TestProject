// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
class ATank;

UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float deltaTime) override;

	void HandleDestruction();
protected:
	virtual void BeginPlay() override;

private:
	ATank* m_Tank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float m_FireRange = 0.f;

	FTimerHandle m_FireRateTimerHande;
	float m_FireRate = 2.f;
	void CheckFireCondition();

	bool InFireRange() const;
};
