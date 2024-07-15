#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UWeaponComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS(Abstract, Blueprintable)
class DRONEGAME_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category=Collision, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(Category=Movement, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

public:
	ABaseProjectile();

protected:
	virtual void BeginPlay() override;
};
