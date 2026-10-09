#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Submarine.generated.h"

class UPowerComponent;
class ABattery;
class UPropulsionComponent;

UCLASS()
class DEEPDARK_API ASubmarine : public AActor
{
	GENERATED_BODY()
	
public:	
	ASubmarine();

protected:
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Submarine", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SubmarineMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Submarine", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<ABattery> Battery = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Submarine", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPowerComponent> PowerComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Submarine", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPropulsionComponent> PropulsionComponent = nullptr;
};
