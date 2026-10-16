#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDefinition.generated.h"

class AItemBase;

UCLASS()
class DEEPDARK_API UItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FName ItemName = NAME_None;
	
	UPROPERTY(EditDefaultsOnly)
	FText DisplayName;
	
	UPROPERTY(EditDefaultsOnly)
	FText Description;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> WorldMesh = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItemBase> ItemActorClass = nullptr;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
