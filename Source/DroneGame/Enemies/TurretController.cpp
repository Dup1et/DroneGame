#include "TurretController.h"

#include "Turret.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionTypes.h"

ATurretController::ATurretController()
{
	PrimaryActorTick.bCanEverTick = false;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
}

void ATurretController::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	if (ControlledTurret == nullptr || ControlledTurret->HeadComponent == nullptr) 
	{
		Super::GetActorEyesViewPoint(OutLocation, OutRotation);
		return;
	}
	
	const auto HeadTransform = ControlledTurret->HeadComponent->GetComponentTransform();
	OutLocation = HeadTransform.GetLocation();
	OutRotation = HeadTransform.GetRotation().Rotator();
}

void ATurretController::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this, &ATurretController::HandleTargetPerceptionInfoUpdate);
}

void ATurretController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledTurret = Cast<ATurret>(InPawn);
}

void ATurretController::HandleTargetPerceptionInfoUpdate(const FActorPerceptionUpdateInfo& UpdateInfo)
{	
	if (!UpdateInfo.Stimulus.WasSuccessfullySensed() && LastTargetId == UpdateInfo.TargetId)
	{
		ControlledTurret->ReleaseTarget();
		return;
	}
	
	ControlledTurret->LockTarget(UpdateInfo.Target);
	LastTargetId = UpdateInfo.TargetId;
}
