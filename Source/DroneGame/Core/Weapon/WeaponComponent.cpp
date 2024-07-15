#include "WeaponComponent.h"

#include "BaseProjectile.h"
#include "GameplayTagAssetInterface.h"
#include "Engine/DamageEvents.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::StartFire()
{
	bIsNeedToFiring = true;
	
	if (bIsFiring) return;
	GetWorld()->GetTimerManager().SetTimer(
		FireHandle,
		this,
		&UWeaponComponent::HandleFire,
		1.f / ShotsPerSecond,
		true,
		0
	);
	bIsFiring = true;
}

void UWeaponComponent::StopFire()
{
	bIsNeedToFiring = false;
}

void UWeaponComponent::RefillAmmo(int AmmoAmount)
{
	AddAmmoInternal(AmmoAmount);
}

int UWeaponComponent::GetCurrentAmmo()
{
	return CurrentAmmo;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentAmmo = MaxAmmo;
}

void UWeaponComponent::HandleFire()
{
	if (!bIsNeedToFiring)
	{
		GetWorld()->GetTimerManager().ClearTimer(FireHandle);
		bIsFiring = false;
		return;
	}
	
	if (CurrentAmmo <= 0 && !bIsInfiniteAmmo) return;

	// can be improved using an object pooling if needed
	const auto Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(
		ProjectileClass,
		MuzzleComponent->GetComponentTransform()
	);
	Projectile->OnActorHit.AddUniqueDynamic(this, &UWeaponComponent::HandleProjectileHit);
	Projectile->FinishSpawning(MuzzleComponent->GetComponentTransform());

	if (bIsInfiniteAmmo) return;
	AddAmmoInternal(-1.f);
}

bool UWeaponComponent::CanApplyDamage(AActor* Actor) const
{
	const auto GameplayTagProvider = Cast<IGameplayTagAssetInterface>(Actor);
	if (GameplayTagProvider == nullptr) return false;

	FGameplayTagContainer ActorTags;
	GameplayTagProvider->GetOwnedGameplayTags(ActorTags);
	
	if (!ActorTags.HasAny(TagsToDamage)) return false;
	
	return true;
}

void UWeaponComponent::HandleProjectileHit(
	AActor* SelfActor,
	AActor* OtherActor,
	FVector NormalImpulse,
	const FHitResult& Hit
) {
	
	if (CanApplyDamage(OtherActor))
	{		
		OtherActor->TakeDamage(
			Damage,
			FPointDamageEvent(
				Damage,
				Hit,
				NormalImpulse,
				UDamageType::StaticClass()
			),
			GetOwner()->GetInstigatorController(),
			GetOwner()
		);
	}

	SelfActor->Destroy();
}

void UWeaponComponent::AddAmmoInternal(const int Amount)
{
	const auto OldAmmo = CurrentAmmo;
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo);

	if (OldAmmo == CurrentAmmo) return;
	OnAmmoChange.Broadcast(OldAmmo, CurrentAmmo);
}

