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

void AToonTanksPlayerController::AddGold(int32 Value)
{
	Gold += Value;
	if(Gold % UpgradeEveryXGold == 0 && Gold != 0)
	{
		ActivateUpgradeMenu();

		//TODO: increment the UpgradeEveryXGold value
	}
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