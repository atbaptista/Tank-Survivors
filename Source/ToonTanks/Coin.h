// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class TOONTANKS_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 50.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float FloatingAmplitude = 30.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float FloatingSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category = "Coin")
	float DespawnTime = 15.f;
	UPROPERTY(EditAnywhere, Category = "Coin")
	int32 Value = 1;
	

private:
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UMeshComponent* CoinMeshComponent;
	FVector InitialLocation;

	FTimerHandle DespawnTimerHandler;
	void Die();
	
	//collision
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult);
	
};