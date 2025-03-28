// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Attackable.h"
#include "AIController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_Attackable::UBTDecorator_Attackable()
{
	NodeName = TEXT("Attackable");
}

bool UBTDecorator_Attackable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr)
		return false;
	

	auto Target = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));
	if (Target == nullptr)
		return false;

	if (Target->GetDistanceTo(Pawn) > 300.f)
		return false;


	//Result == true
	return Result;
}
