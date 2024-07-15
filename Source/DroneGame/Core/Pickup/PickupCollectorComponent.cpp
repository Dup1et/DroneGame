#include "PickupCollectorComponent.h"

#include "PickupInterface.h"

UPickupCollectorComponent::UPickupCollectorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPickupCollectorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UPickupCollectorComponent::HandleActorBeginOverlap);
}

void UPickupCollectorComponent::HandleActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OtherActor->GetClass()->ImplementsInterface(UPickupInterface::StaticClass())) return;
	
	IPickupInterface::Execute_Apply(OtherActor, OverlappedActor);
}

