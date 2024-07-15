#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAmmoChangeSignature, int, OldAmmo, int, NewAmmo);

class ABaseProjectile;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEGAME_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float ShotsPerSecond;

	UPROPERTY(EditAnywhere)
	float MaxAmmo;

	UPROPERTY(EditAnywhere)
	bool bIsInfiniteAmmo = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	FGameplayTagContainer TagsToDamage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> MuzzleComponent;

	float CurrentAmmo = 0.f;
	bool bIsFiring = false;
	bool bIsNeedToFiring = false;
	
	FTimerHandle FireHandle;
	
public:

	UPROPERTY(BlueprintAssignable)
	FAmmoChangeSignature OnAmmoChange;
	
	UWeaponComponent();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void RefillAmmo(int AmmoAmount);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentAmmo();

protected:
	virtual void BeginPlay() override;

private:
	void HandleFire();

	bool CanApplyDamage(AActor* Actor) const;

	UFUNCTION()
	void HandleProjectileHit(
		AActor* SelfActor,
		AActor* OtherActor,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	void AddAmmoInternal(const int Amount);
};
