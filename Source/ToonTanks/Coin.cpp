// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CoinMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));

	//FloatingAmplitude = 50.0f; // Adjust as needed
	//FloatingSpeed = 1.0f; // Adjust as needed
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	GetWorldTimerManager().SetTimer(DespawnTimerHandler, this, &ACoin::Die, DespawnTime,false);

	CoinMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlap);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//rotate
	FRotator Rotation = FRotator::ZeroRotator;
	Rotation.Roll = TurnRate * DeltaTime;
	AddActorLocalRotation(Rotation, true);

	//bob
	FVector NewLocation = InitialLocation + FVector(0.0f, 0.0f, FloatingAmplitude * FMath::Sin(FloatingSpeed * GetGameTimeSinceCreation()));
	SetActorLocation(NewLocation);
}

void ACoin::Die()
{
	Destroy();
}

void ACoin::OnOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult)
{
	
	if(ATank* Player = Cast<ATank>(OtherActor))
	{
		UE_LOG(LogTemp, Error, TEXT("OVERLAPPED %s"), *OtherActor->GetActorNameOrLabel());
		AToonTanksPlayerController* PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		PlayerController->AddGold(Value);
		Destroy();
	}
	
}



