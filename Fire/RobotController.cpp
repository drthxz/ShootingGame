// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RobotShooter.h"

ARobotController::ARobotController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
}

void ARobotController::BeginPlay()
{
	Super::BeginPlay();

	UBlackboardComponent* BlackboardComponent;
	UseBlackboard(BlackboardData, BlackboardComponent);
	RunBehaviorTree(BehaviorTree);

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ARobotController::OnPerception);
}

void ARobotController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	UBlackboardComponent* Comp = UAIBlueprintHelperLibrary::GetBlackboard(this);
	UObject* Object = Comp->GetValueAsObject("Enemy");

	if (Object != Actor){
		return;
	}

	Comp->SetValueAsBool("CanSeeEnemy", Stimulus.WasSuccessfullySensed());
}

ARobotShooter* ARobotController::GetRobotShooter()
{
	return Cast<ARobotShooter>(GetPawn());
}
