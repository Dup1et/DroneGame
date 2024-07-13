#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "UObject/Object.h"
#include "BasePawn.generated.h"


UCLASS(Abstract, Blueprintable)
class DRONEGAME_API ABasePawn : public APawn, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

	UPROPERTY(Category=GameplayTags, EditAnywhere)
	FGameplayTagContainer GameplayTags;
	
public:
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
};
