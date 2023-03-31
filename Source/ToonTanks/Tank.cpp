// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h" 
#include "GameFramework/SpringArmComponent.h" 
#include "Components/InputComponent.h" 

#include "GameFramework/PlayerController.h" 
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    m_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    m_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));

    m_SpringArmComponent->SetupAttachment(RootComponent);
    m_CameraComponent->SetupAttachment(m_SpringArmComponent);

}

void ATank::Move(float value)
{
    FVector deltaLocation = FVector::ZeroVector;
    float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

    deltaLocation.X = value * deltaTime * m_Speed;

    AddActorLocalOffset(deltaLocation, true);
}

void ATank::Turn(float value)
{
    FRotator deltaRotation = FRotator::ZeroRotator;
    float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

    // Yaw = Value * DeltaTime * TurnRate
    deltaRotation.Yaw = value * deltaTime * m_TurnRate;

    AddActorLocalRotation(deltaRotation, true);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();
    m_PlayerController = Cast<APlayerController>(GetController());
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed ,this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (m_PlayerController)
    {
        FHitResult hitResult;
        m_PlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false, 
            hitResult);

        RotateTurret(hitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);

    SetActorTickEnabled(false);
    bAlive = false;

}
