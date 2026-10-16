#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataItem.generated.h"

USTRUCT(BlueprintType)
struct FDataItem : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base")
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base")
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base")
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base")
    UStaticMesh* StaticMesh;
};