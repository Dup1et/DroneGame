#pragma once

#include "CoreMinimal.h"
#include "DroneGame/Core/Pawn/BasePawn.h"
#include "GameFramework/Pawn.h"
#include "DGPlayer.generated.h"

class UPickupCollectorComponent;
class UWeaponComponent;
class UHealthComponent;
class UFloatingPawnMovement;

UCLASS()
class DRONEGAME_API ADGPlayer : public ABasePawn
{
	GENERATED_BODY()

public:
	UPROPERTY(Category=Movement, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	UPROPERTY(Category=Health, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(Category=Weapon, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> WeaponComponent;

	UPROPERTY(Category=Pickup, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPickupCollectorComponent> PickupCollectorComponent;
	
	ADGPlayer();
};
