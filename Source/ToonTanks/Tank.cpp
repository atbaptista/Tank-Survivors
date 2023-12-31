// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HealthComponent.h"


ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Cam->SetupAttachment(SpringArmComp);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!TankPlayerController)
	{
		return;
	}

	FHitResult out;
	TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, out);
	//DrawDebugSphere(GetWorld(), out.ImpactPoint, 25.f, 10, FColor::Red);
	RotateTurret(out.ImpactPoint);
}

void ATank::Move(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("Move Axis: %f"), Value)
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * GetWorld()->GetDeltaSeconds();
	//UE_LOG(LogTemp, Display, TEXT("Move Axis: %s"), *DeltaLocation.ToString())
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator Rotation = FRotator::ZeroRotator;
	Rotation.Yaw = TurnRate * Value * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(Rotation, true);
}

void ATank::SwitchCanFire()
{
	bCanFire = true;
	//UE_LOG(LogTemp, Display, TEXT("Can fire again!"))
}

void ATank::Fire()
{
	if(!bCanFire)
	{
		return;
	}
	
	Super::Fire();
	bCanFire = false;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATank::SwitchCanFire, FireRate);
}

void ATank::HealTank(float Val)
{
	Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()))->Heal(Val);
}

void ATank::UpgradeMaxHealth(float Val)
{
	Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()))->IncreaseMaxHealth(Val);
}

void ATank::UpgradeSpeed(float Val)
{
	Speed += Val;
}

void ATank::UpgradeFireRate(float Val)
{
	FireRate -= Val;
}

float ATank::GetMaxHealth()
{
	return Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()))->GetMaxHealth();
}

float ATank::GetHealth()
{
	return Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()))->GetHealth();
}
