#include "Turret.h"

#include "DroneGame/Core/Health/HealthComponent.h"
#include "DroneGame/Core/Weapon/WeaponComponent.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(FName("WeaponComponent"));
}

void ATurret::LookAt(const FVector& Point)
{
	HeadComponent->SetRelativeRotation((Point - HeadComponent->GetComponentLocation()).Rotation());
}