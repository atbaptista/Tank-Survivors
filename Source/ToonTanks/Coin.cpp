// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CoinMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;
	CoinMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	GetWorldTimerManager().SetTimer(DespawnTimerHandler, this, &ACoin::Die, DespawnTime,false);

	TankPlayer = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BobSpin(DeltaTime);
	CheckDistance();

}

void ACoin::Die()
{
	Destroy();
}

void ACoin::BobSpin(float DeltaTime)
{
	//rotate
	FRotator Rotation = FRotator::ZeroRotator;
	Rotation.Yaw = TurnRate * DeltaTime;
	AddActorLocalRotation(Rotation, true);

	//bob
	FVector NewLocation = InitialLocation + FVector(0.0f, 0.0f, FloatingAmplitude * FMath::Sin(FloatingSpeed * GetGameTimeSinceCreation()));
	SetActorLocation(NewLocation);
}

void ACoin::CheckDistance()
{
	//check distance to player
	if(!TankPlayer)
	{
		return;
	}
	//add gold to player if close enough
	if(FVector::Dist(GetActorLocation(), TankPlayer->GetActorLocation()) <= TankPlayerController->GetGoldPickUpDistance())
	{
		TankPlayerController->AddGold(Value);
		//play sound
		if(CoinSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CoinSound, GetActorLocation(), GetActorRotation());
		}
		Destroy();
	}
}



