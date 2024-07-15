#include "Turret.h"

#include "DroneGame/Core/Health/HealthComponent.h"
#include "DroneGame/Core/Weapon/WeaponComponent.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(FName("WeaponComponent"));
}

void ATurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto bIsIdle = Target == nullptr;
	const auto CurrentRotation = HeadComponent->GetComponentRotation();
	const auto DesiredRotation = bIsIdle
		? FRotator::MakeFromEuler(FVector(0, 0, CurrentRotation.Yaw + IdleRotationSpeed))
		: (Target->GetActorLocation() - HeadComponent->GetComponentLocation()).Rotation();
	
	HeadComponent->SetWorldRotation(
		FMath::RInterpConstantTo(
			CurrentRotation,
			DesiredRotation,
			DeltaSeconds,
			bIsIdle ? IdleRotationSpeed: AimRotationSpeed
		)
	);
}

void ATurret::LockTarget(const TWeakObjectPtr<AActor> InTarget)
{
	Target = InTarget;
	WeaponComponent->StartFire();
}

void ATurret::ReleaseTarget()
{
	Target = nullptr;
	WeaponComponent->StopFire();
}
