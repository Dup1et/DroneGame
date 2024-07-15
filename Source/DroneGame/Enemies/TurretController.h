#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "TurretController.generated.h"

struct FActorPerceptionUpdateInfo;
class ATurret;
struct FAIStimulus;

UCLASS(Abstract, Blueprintable)
class DRONEGAME_API ATurretController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	int32 LastTargetId = -1;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ATurret> ControlledTurret;

public:
	ATurretController();
	
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

protected:
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void HandleTargetPerceptionInfoUpdate(const FActorPerceptionUpdateInfo& UpdateInfo);
};
