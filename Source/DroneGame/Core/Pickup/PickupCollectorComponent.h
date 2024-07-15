#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupCollectorComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEGAME_API UPickupCollectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPickupCollectorComponent();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void HandleActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
