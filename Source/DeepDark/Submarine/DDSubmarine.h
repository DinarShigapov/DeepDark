
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DDSubmarine.generated.h"

class UBatteryComponent;

UCLASS()
class DEEPDARK_API ADDSubmarine : public AActor
{
	GENERATED_BODY()
	
public:	
	ADDSubmarine();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Submarine", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SubmarineMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Submarine", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBatteryComponent> BatteryComponent = nullptr;
	
};
