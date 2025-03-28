// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Attackable.h"

UBTDecorator_Attackable::UBTDecorator_Attackable()
{
	NodeName = TEXT("Attackable");
}

bool UBTDecorator_Attackable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);



	return false;
}
