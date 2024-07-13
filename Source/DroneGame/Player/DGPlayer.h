#pragma once

#include "CoreMinimal.h"
#include "DroneGame/Core/Pawn/BasePawn.h"
#include "GameFramework/Pawn.h"
#include "DGPlayer.generated.h"

class UFloatingPawnMovement;

UCLASS()
class DRONEGAME_API ADGPlayer : public ABasePawn
{
	GENERATED_BODY()

public:
	UPROPERTY(Category=Movement, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> MovementComponent;
	
	ADGPlayer();
};
