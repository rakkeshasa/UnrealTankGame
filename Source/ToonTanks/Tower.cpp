// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Tower.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: ��ũ���� �Ÿ� ã��
	// ��ũ�� ��Ÿ� �ȿ� �ִ��� Ȯ���ϱ�
	// ��Ÿ� �ȿ� ���� �� �ͷ��� ȸ����Ű��
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

	// ���� ��Ÿ�ӿ� �� Ÿ�̸� �����ϱ�
	GetWorldTimerManager().SetTimer(FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true);
}

void ATower::CheckFireCondition()
{
	// ��ũ�� ����ְ� ��Ÿ� �ȿ� ������ ����
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
	// ��ũ�� ��Ÿ� �ȿ� �ִ��� Ȯ��
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
