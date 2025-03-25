// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"



UPlayerAnimInstance::UPlayerAnimInstance()
{

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'"));

	if (AM.Succeeded())
	{
		FireMontage = AM.Object;
		UE_LOG(LogTemp, Log, TEXT("0"));
	}
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
		}

	}

}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(CharacterMovement))
	{
		Velocity = CharacterMovement->Velocity;
		FRotator Rotation = MyCharacter->GetActorRotation();
		FVector UnrotateVector = Rotation.UnrotateVector(Velocity);

		Speed = MyCharacter->GetVelocity().Size2D();

		auto Acceleration = CharacterMovement->GetCurrentAcceleration();

		ShouldMove = Speed > 0.3f && Acceleration != FVector::Zero();

		IsFalling = CharacterMovement->IsFalling();

		AimRotation = MyCharacter->GetBaseAimRotation();
		FRotator RotFromX = UKismetMathLibrary::MakeRotFromX(Velocity);

		FRotator DeltaRotation = AimRotation - RotFromX;
		DeltaRotation.Normalize();

		YawOffset = DeltaRotation.Yaw;

		if (ShouldMove || IsFalling)
		{

			RotateYaw = FMath::FInterpTo(RotateYaw, 0.f, DeltaSeconds, 20.f);
			MovingRotation = MyCharacter->GetActorRotation();
			PrevRotation = MovingRotation;

		}
		else
		{
			PrevRotation = MovingRotation;
			MovingRotation = MyCharacter->GetActorRotation();
			FRotator Delta = MovingRotation - PrevRotation;
			Delta.Normalize();
			RotateYaw -= Delta.Yaw;

			float TurnValue = GetCurveValue("Turn");

			//애니메이션이 실행 되고 있다면
			if (TurnValue > 0.f)
			{
				//Delta값을 구하기 위해서
				PrevDistanceCurve = DistanceCurve;
				DistanceCurve = GetCurveValue("DistanceCurve");
				DeltaDistanceCurve = DistanceCurve - PrevDistanceCurve;
				//왼쪽회전 오른쪽 회전 구분
				if (RotateYaw > 0.f)
				{
					RotateYaw -= DeltaDistanceCurve;
				}
				else
				{
					RotateYaw += DeltaDistanceCurve;
				}

				//회전값이 있을 경우
				float AbsRotateYawOffset = FMath::Abs(RotateYaw);
				if (AbsRotateYawOffset > 0.f)
				{
					//90도 회전이라 회전 값에 90.f을 뺌
					float YawExcess = AbsRotateYawOffset - 90.f;

					//왼쪽회전 오른쪽 회전 구분
					if (RotateYaw > 0.f)
					{
						RotateYaw -= YawExcess;
					}
					else
					{
						RotateYaw += YawExcess;
					}

				}

			}
		}

		UE_LOG(LogTemp, Log, TEXT("RotateYaw : %f"), RotateYaw);
	
		
		
	}
}

void UPlayerAnimInstance::PlayFireMontage()
{
	if (IsValid(FireMontage))
	{
		if (!Montage_IsPlaying(FireMontage))
		{
			Montage_Play(FireMontage);
		}
	}
}
