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
	
	//TODO: spawn enemies around player
	for(int i = 0; i < NumberEnemiesToSpawn; i++)
	{
		//find random spawn location within cube x distance away from player
		//this finds random spawn point in outer 4 corner areas of the cube
		FVector center = Player->GetActorLocation();
		center.Z = 0;
		//generate number between 0 and 1000
		int32 Offset = SpawnerMaxDistance - SpawnerMinDistance;
		int32 XCoord = FMath::RandRange(0, Offset);
		int32 YCoord = FMath::RandRange(0, Offset);

		//spawn on left or right of center
		if(FMath::RandRange(-1, 1) > 0)
		{
			XCoord = center.X + SpawnerMinDistance + XCoord;
		}
		else
		{
			XCoord = center.X - SpawnerMinDistance - XCoord;
		}

		//spawn on top or bottom
		if(FMath::RandRange(-1, 1) > 0)
		{
			YCoord = center.Y + SpawnerMinDistance + YCoord;
		}
		else
		{
			YCoord = center.Y - SpawnerMinDistance - YCoord;
		}

		//Clamp the X and Y coords to the boundaries of the map
		//min y = -7500 max y = 2400
		//min x = -7400  max x = 2400
		FVector EnemySpawnLocation = FVector(FMath::Clamp(XCoord, -7350, 2350), FMath::Clamp(YCoord, -7450, 2350), 81);
		DrawDebugSphere(GetWorld(), EnemySpawnLocation, 25.f, 12, FColor::Red, true);
		if(EnemiesToSpawn[0])
		{
			ATower* EnemySpawned = GetWorld()->SpawnActor<ATower>(
				EnemiesToSpawn[0],
				EnemySpawnLocation,
				FRotator::ZeroRotator);
		}
		
		//UE_LOG(LogTemp, Display, TEXT("Spawned Enemy #%i"), i);
	}
}