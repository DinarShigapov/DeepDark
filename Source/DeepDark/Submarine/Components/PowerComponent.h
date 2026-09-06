#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPowerStateChanged, FName, ConsumerName);

USTRUCT(BlueprintType)
struct FPowerConsumer
{
	GENERATED_BODY()

	// Название модуля
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	// Сколько мощности требует модуль 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PowerRequired = 0.0f;

	// Включен ли модуль
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnabled = false;
};

UCLASS()
class DEEPDARK_API UPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPowerComponent();

	// Текущая нагрузка
	UFUNCTION(BlueprintPure, Category="Power")
	float GetCurrentLoad() const;
	
	// Процент нагрузки
	UFUNCTION(BlueprintPure, Category="Power")
	float GetLoadPercent() const;
	
	// Можно ли включить модуль
	UFUNCTION(BlueprintPure, Category="Power")
	bool TryEnableConsumer(FName ConsumerName) const;
	
	// Включить модуль
	UFUNCTION(BlueprintCallable, Category="Power")
	bool EnableConsumer(FName ConsumerName);
	
	// Выключить модуль
	UFUNCTION(BlueprintCallable, Category="Power")
	bool DisableConsumer(FName ConsumerName);
	
protected:
	// Массив модулей, которые используют батарею
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Power")
	TArray<FPowerConsumer> Consumers;

	// Проверить, включен ли модуль
	UFUNCTION(BlueprintPure, Category="Power")
	bool IsConsumerEnabled(FName ConsumerName) const;
	
	// Событие изменения питания
	UPROPERTY(BlueprintAssignable, Category="Power")
	FOnPowerStateChanged OnPowerStateChanged;

private:
	// Максимальная мощность электросети
	UPROPERTY(VisibleAnywhere)
	float MaxPower = 100.0f;

	FPowerConsumer* FindConsumer(FName ConsumerName);

	const FPowerConsumer* FindConsumer(FName ConsumerName) const;
};
