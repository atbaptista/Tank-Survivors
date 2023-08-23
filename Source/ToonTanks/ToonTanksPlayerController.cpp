// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

#include "HealthComponent.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if(bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}

float AToonTanksPlayerController::GetHealth()
{
	UHealthComponent* PlayerHealthComp = Cast<UHealthComponent>(GetPawn()->GetComponentByClass(UHealthComponent::StaticClass()));
	if(PlayerHealthComp)
	{
		return PlayerHealthComp->GetHealth();
	}
	return 0;
}
