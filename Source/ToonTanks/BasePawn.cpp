// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Projectile.h"
#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// ��Ʈ������Ʈ�� ĸ��������Ʈ�� �����
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	// ��ũ ���̽� ��밡 �� �޽� ������Ʈ�� ĸ�� ������Ʈ�� ����
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	// ��ũ �ͷ� �޽��� ���̽��޽��� ����
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// ���� ���� ��ġ�� �ͷ��޽��� ����
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// TODO: �׾��� ���� �ð��� û���� ȿ��
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,
			DeathParticles,
			GetActorLocation(),
			GetActorRotation()
		);
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,
			DeathSound,
			GetActorLocation()
		);
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	// �ͷ��� ���콺�� ��ġ ������ �Ÿ� ����ϱ�
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	// �ͷ� �޽��� ���콺 ��ġ�� ȸ���ϱ�
	// FMath���̺귯���� RInterpToŬ������ �̿��Ͽ� �ͷ� ȸ���� �ε巴�� �����
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		20.f)
	);
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	
	// �߻��� �Ű�ü�� ���� ���� ����
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}
