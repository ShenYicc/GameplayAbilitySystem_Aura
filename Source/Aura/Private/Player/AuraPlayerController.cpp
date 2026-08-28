// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	SetReplicates(true);
	PrimaryActorTick.bCanEverTick = true;	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = CurrentActor;
	CurrentActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	/**
	 *  Line trace from cursor. There are several scenarios;
	 *  
	 *  A. LastActor is null && CurrentActor is null
	 *		- Do nothing;
	 *		
	 *	B. LastActor is null && CurrentActor is valid
	 *		- CurrentActor->HighlightActor();
	 *		
	 *	C. LastActor is valid && CurrentActor is null
	 *		- LastActor->UnHighlightActor();
	 *		
	 *	D. LastActor is valid && CurrentActor is valid
	 *	{
	 *		D1. LastActor == CurrentActor;
	 *			- Do nothing;
	 *			
	 *		D2. LastActor != CurrentActor;
	 *			- LastActor->UnHighlightActor();
	 *			- CurrentActor->HighlightActor();
	 *	}
	 */
	
	if (LastActor == nullptr)
	{
		if (CurrentActor != nullptr)
		{
			CurrentActor->HighlightActor();
		}
	}
	else // LastActor != nullptr
	{
		if (CurrentActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else if (LastActor != CurrentActor)
		{
			LastActor->UnHighlightActor();
			CurrentActor->HighlightActor();
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	SetShowMouseCursor(true);
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	check(MoveAction);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
