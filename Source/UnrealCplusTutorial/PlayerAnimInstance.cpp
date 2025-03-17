// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "MyCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{

		MyCharacter = Cast<AMyCharacter>(Pawn);
		if (IsValid(MyCharacter))
		{
			CharacterMovement = MyCharacter->GetCharacterMovement();
			UE_LOG(LogTemp, Log, TEXT("Character Movement is valid"));

		}

	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(MyCharacter))
	{
		Speed = MyCharacter->GetVelocity().Size2D();
	}
}
