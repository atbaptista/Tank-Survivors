// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	SetFocus(PlayerPawn);
	
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* Tank = Cast<ATank>(PlayerPawn);
	
	
	if(Tank && Tank->bAlive)
	{
		MoveToActor(Tank, 100);
	}
	else
	{
		StopMovement();
	}
}
