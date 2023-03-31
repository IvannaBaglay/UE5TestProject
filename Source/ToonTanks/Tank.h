// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APlayerController;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{

	GENERATED_BODY()
public:
	ATank();
	void HandleDestruction();
	APlayerController* GetTankPlayerController() const { return m_PlayerController; }
	bool bAlive = true;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Conponents", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Conponents", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_CameraComponent;

	void Move(float value);
	void Turn(float value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float m_Speed = 400.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float m_TurnRate = 45.f;

	APlayerController* m_PlayerController;
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
