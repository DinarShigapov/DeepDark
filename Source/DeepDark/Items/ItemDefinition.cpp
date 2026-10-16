// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDefinition.h"

FPrimaryAssetId UItemDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType(TEXT("ItemDefinition")), GetFName());
}
