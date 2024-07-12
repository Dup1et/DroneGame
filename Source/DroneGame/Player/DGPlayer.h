#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DGPlayer.generated.h"

class UFloatingPawnMovement;

UCLASS(Blueprintable)
class DRONEGAME_API ADGPlayer : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(Category=Movement, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> MovementComponent;
	
	ADGPlayer();
};
