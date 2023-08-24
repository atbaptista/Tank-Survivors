// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HandleDestruction();
	APlayerController* GetTankPlayerController() const {return TankPlayerController;}

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* Cam;

	void Move(float Value);
	void Turn(float Value);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 500.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 90.f;

	APlayerController* TankPlayerController;

	//fire rate code
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 0.6f;
	bool bCanFire = true;
	void SwitchCanFire();
	void Fire();
	FTimerHandle FireTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//upgrades
	UFUNCTION(BlueprintCallable)
	void HealTank(float Val);
	UFUNCTION(BlueprintCallable)
	void UpgradeMaxHealth(float Val);
	UFUNCTION(BlueprintCallable)
	void UpgradeSpeed(float Val);
	UFUNCTION(BlueprintCallable)
	void UpgradeFireRate(float Val);

	//Stats
	UFUNCTION(BlueprintCallable)
	float GetFireRate(){return FireRate;}
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable)
	float GetHealth();
};
