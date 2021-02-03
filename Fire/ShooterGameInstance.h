// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FKillInfoUpdateDelegate, FString, KillerName, FString, KilledName, int, KillerSide, int, KilledSide, UTexture2D*, Icon);

UCLASS()
class FIRE_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="ShooterGameInstance")
	FKillInfoUpdateDelegate OnKillInfoUpdate;
};
