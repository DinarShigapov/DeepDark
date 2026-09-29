#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PropulsionComponent.generated.h"


UCLASS()
class DEEPDARK_API UPropulsionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPropulsionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
