#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::Heal(const float HealthAmount)
{
	AddHealthInternal(HealthAmount);
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &ThisClass::HandleDamageTaken);
}

void UHealthComponent::HandleDamageTaken(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser
) {
	AddHealthInternal(-Damage);
}

void UHealthComponent::AddHealthInternal(const float Amount)
{
	const auto OldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);

	if (OldHealth == CurrentHealth) return;
	OnHealthChange.Broadcast(OldHealth, CurrentHealth);

	if (CurrentHealth > 0.f) return;
	OnDeath.Broadcast();
}

