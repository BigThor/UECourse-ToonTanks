// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATower();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

private:
	void CheckFireCondition();
	bool InFireRange();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 600.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;

	class ATank* Tank;
};
