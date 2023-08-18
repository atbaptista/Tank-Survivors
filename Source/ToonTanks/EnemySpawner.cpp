// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "Kismet/GameplayStatics.h"
#include "Tower.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerPawn(this, 0);
	GetWorldTimerManager().SetTimer(EnemySpawnTimerHandle, this, &AEnemySpawner::SpawnEnemies, SpawnDelayTime, true);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemies()
{
	WaveNumber++;
	if(!Player)
	{
		return;
	}
	
	//spawn enemies randomly in map

	for(int i = 0; i < NumberEnemiesToSpawn; i++)
	{
		if(EnemiesToSpawn[0])
		{
			ATower* EnemySpawned = GetWorld()->SpawnActor<ATower>(
			EnemiesToSpawn[0],
			FVector(0,0,1000),
			FRotator::ZeroRotator);

			//spawned enemy inside of a wall or another object
			if(!EnemySpawned)
			{
				//DrawDebugSphere(GetWorld(), EnemySpawnLocation, 25.f, 12, FColor::Red, true);
				i--;
				if(i < 25)
				{
					break;
				}
			}
			else
			{
				FVector EnemySpawnLocation = GenerateSpawnPoint(EnemySpawned);
				EnemySpawned->SetActorLocation(EnemySpawnLocation);
			}

		}
	}
}

//generates random X and Y values, sets Z Value to be above the floor
FVector AEnemySpawner::GenerateSpawnPoint(AActor* Enemy)
{
	if(!WestWall || !EastWall || !NorthWall || !SouthWall)
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: MAP BOUNDS NOT SET IN EDITOR"));
		return FVector::ZeroVector;
	}
	
	int32 XCoord = 0;
	int32 YCoord = 0;
		
	XCoord = FMath::RandRange(WestWall->GetActorLocation().X, EastWall->GetActorLocation().X);
	XCoord = FMath::Clamp(XCoord, WestWall->GetActorLocation().X + 200, EastWall->GetActorLocation().X - 200);
		
	YCoord = FMath::RandRange(SouthWall->GetActorLocation().Y, NorthWall->GetActorLocation().Y);
	YCoord = FMath::Clamp(YCoord, SouthWall->GetActorLocation().Y + 200, NorthWall->GetActorLocation().Y - 200);

	return FVector(XCoord, YCoord, Enemy->GetSimpleCollisionHalfHeight());
}
