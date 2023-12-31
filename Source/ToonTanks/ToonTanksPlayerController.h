// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetPlayerEnabledState(bool bPlayerEnabled);


private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
	int32 Gold = 0;
	UPROPERTY(EditAnywhere, Category = "Player")
	float GoldPickUpDistance = 50.f;
	UPROPERTY(EditAnywhere, Category = "Player")
	int32 UpgradeEveryXGold = 10;

public:
	//getters and setters for Gold and pickup radius
	UFUNCTION(BlueprintCallable)
	int32 GetGold() const {return Gold;}
	UFUNCTION(BlueprintCallable)
	void AddGold(int32 Value);
	UFUNCTION(BlueprintCallable)
	float GetGoldPickUpDistance() const {return GoldPickUpDistance;}
	UFUNCTION(BlueprintCallable)
	void AddGoldPickUpDistance(float Add){this->GoldPickUpDistance += Add;}
	UFUNCTION(BlueprintCallable)
	float GetHealth();

	//Upgrades
	UFUNCTION(BlueprintImplementableEvent)
	void ActivateUpgradeMenu();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 EnemiesDefeated = 0;
};
