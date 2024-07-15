#include "DGPlayer.h"
#include "DroneGame/Core/Health/HealthComponent.h"
#include "DroneGame/Core/Pickup/PickupCollectorComponent.h"
#include "DroneGame/Core/Weapon/WeaponComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ADGPlayer::ADGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(FName("MovementComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(FName("WeaponComponent"));
	PickupCollectorComponent = CreateDefaultSubobject<UPickupCollectorComponent>(FName("PickupCollectorComponent"));
}
