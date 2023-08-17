// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ATank;
class ATower;

UCLASS()
class TOONTANKS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnDelayTime = 6.f;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 NumberEnemiesToSpawn = 1;

	//Wall References
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walls")
	AActor* WestWall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walls")
	AActor* EastWall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walls")
	AActor* NorthWall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walls")
	AActor* SouthWall;
	

private:
	APawn* Player;
	int32 WaveNumber = 0;

	//Spawning
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<TSubclassOf<ATower>> EnemiesToSpawn;
	FTimerHandle EnemySpawnTimerHandle;
	void SpawnEnemies();
	FVector GenerateSpawnPoint();
	
};
