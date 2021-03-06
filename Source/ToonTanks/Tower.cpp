// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
	
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

void ATower::CheckFireCondition()
{
	if (!Tank)
	{
		return;
	}

	// Check if the Tank is in range
	if (InFireRange() && Tank->IsAlive())
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (!Tank)
	{
		return false;
	}

	// Find distance to the tank
	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	return Distance <= FireRange;
	
}