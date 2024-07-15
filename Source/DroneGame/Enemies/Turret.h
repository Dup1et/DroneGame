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

	UPROPERTY(EditAnywhere)
	float AimRotationSpeed;

	UPROPERTY(EditAnywhere)
	float IdleRotationSpeed;

	UPROPERTY(Category=Health, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(Category=Weapon, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> WeaponComponent;

	UPROPERTY()
	TWeakObjectPtr<AActor> Target;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> HeadComponent;
	
	ATurret();

	virtual void Tick(float DeltaSeconds) override;

	void LockTarget(TWeakObjectPtr<AActor> InTarget);

	void ReleaseTarget();
};
