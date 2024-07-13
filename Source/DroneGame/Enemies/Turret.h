#pragma once

#include "CoreMinimal.h"
#include "DroneGame/Core/Pawn/BasePawn.h"
#include "GameFramework/Pawn.h"
#include "Turret.generated.h"

class UWeaponComponent;
class UHealthComponent;

UCLASS()
class DRONEGAME_API ATurret : public ABasePawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> HeadComponent;

	UPROPERTY(Category=Health, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(Category=Weapon, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> WeaponComponent;

public:
	ATurret();

	UFUNCTION(BlueprintCallable)
	void LookAt(const FVector& Point);
};
