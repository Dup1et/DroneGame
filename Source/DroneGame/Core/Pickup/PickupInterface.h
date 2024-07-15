#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

class DRONEGAME_API IPickupInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Apply(AActor* Target);
};
