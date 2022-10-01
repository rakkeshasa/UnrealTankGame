// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		// ��ũ�� ���� �� ��ũ �� ��Ʈ���� �Լ� ȣ�� �� �Է� �ȵǰ� ����
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		// Ÿ���� ������ Ÿ��Ŭ������ ��Ʈ���� �Լ� ȣ��
		DestroyedTower->HandleDestruction();
		--TargetTowers;

		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	// ��� ����Ʈ�� �� �̺�Ʈ ����
	StartGame();

	// �� �ʵڿ� ���� �����ϰ� �����
	if (ToonTanksPlayerController)
	{
		// ���۽� ��Ʈ�� ���ϰ� false�� ����
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		// SetTimer���� ����
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
		);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	// ���� �ͷ��� ���� ���ϱ�
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}