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
	
	// 루트컴포넌트를 캡슐컴포넌트로 만들기
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	// 탱크 베이스 토대가 될 메쉬 컴포넌트를 캡슐 컴포넌트에 부착
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	// 탱크 터렛 메쉬를 베이스메쉬에 부착
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// 포가 나갈 위치를 터렛메쉬에 부착
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// TODO: 죽었을 때의 시각적 청각적 효과
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
	// 터렛과 마우스의 위치 사이의 거리 계산하기
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	// 터렛 메쉬가 마우스 위치로 회전하기
	// FMath라이브러리의 RInterpTo클래스를 이용하여 터렛 회전을 부드럽게 만들기
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
	
	// 발사한 매개체에 대한 오너 설정
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}
