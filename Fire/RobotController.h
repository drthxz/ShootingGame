// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "RobotController.generated.h"

/**
 * 
 */
class UBlackboardData;
class UBehaviorTree;
class ARobotShooter;

UCLASS()
class FIRE_API ARobotController : public AAIController
{
	GENERATED_BODY()
	
public:
	ARobotController();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintPure,Category = "RobotController")
	ARobotShooter* GetRobotShooter();

protected:
	UPROPERTY(BlueprintReadOnly,VisibleDefaultsOnly,Category="RobotController")
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "RobotController")
	UBlackboardData* BlackboardData;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "RobotController")
	UBehaviorTree* BehaviorTree;
};
