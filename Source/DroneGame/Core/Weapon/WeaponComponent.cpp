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
	IsNeedToFiring = true;
	
	if (IsFiring) return;
	GetWorld()->GetTimerManager().SetTimer(
		FireHandle,
		this,
		&UWeaponComponent::HandleFire,
		1.f / ShotsPerSecond,
		true,
		0
	);
	IsFiring = true;
}

void UWeaponComponent::StopFire()
{
	IsNeedToFiring = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
}

void UWeaponComponent::HandleFire()
{
	if (!IsNeedToFiring)
	{
		GetWorld()->GetTimerManager().ClearTimer(FireHandle);
		IsFiring = false;
		return;
	}
	
	if (CurrentAmmo == 0 && !IsInfiniteAmmo) return;

	const auto Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(
		ProjectileClass,
		MuzzleComponent->GetComponentTransform()
	);
	Projectile->OnActorHit.AddUniqueDynamic(this, &UWeaponComponent::HandleProjectileHit);

	Projectile->FinishSpawning(MuzzleComponent->GetComponentTransform());

	if (IsInfiniteAmmo) return;
	CurrentAmmo--;
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

