#include "DGPlayer.h"

#include "GameFramework/FloatingPawnMovement.h"

ADGPlayer::ADGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(FName("MovementComponent"));
}
