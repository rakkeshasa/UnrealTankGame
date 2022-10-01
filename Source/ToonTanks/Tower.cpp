// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Tower.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: 탱크와의 거리 찾기
	// 탱크가 사거리 안에 있는지 확인하기
	// 사거리 안에 있을 시 터렛을 회전시키기
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

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// 발포 쿨타임에 쓸 타이머 설정하기
	GetWorldTimerManager().SetTimer(FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true);
}

void ATower::CheckFireCondition()
{
	// 탱크가 살아있고 사거리 안에 들어오면 발포
	if (Tank == nullptr)
	{
		return;
	}
	if (InFireRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	// 탱크가 사거리 안에 있는지 확인
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}
