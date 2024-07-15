#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChangeSignature, float, OldHealth, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int MaxHealth;

	float CurrentHealth;

public:
	UPROPERTY(BlueprintAssignable)
	FHealthChangeSignature OnHealthChange;
	
	UPROPERTY(BlueprintAssignable)
	FDeathSignature OnDeath;
	
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	void Heal(const float HealthAmount);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentHealth();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void HandleDamageTaken(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser
	);

	void AddHealthInternal(const float Amount);
};
