// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Coin.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!Tank)
	{
		return;
	}
	
	if(TankInRange() && Tank)
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	ACoin* Coin = GetWorld()->SpawnActor<ACoin>(CoinClass, GetActorLocation(), GetActorRotation());
	Destroy();
}

void ATower::CheckFireCondition()
{
	if(!Tank)
	{
		return;
	}
	if(TankInRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool ATower::TankInRange()
{
	if(!Tank)
	{
		return false;
	}
	
	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	if(Distance <= FireRange)
	{
		return true;
	}
	return false;
}


