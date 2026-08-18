#include "PuzzlePawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"

APuzzlePawn::APuzzlePawn()
{
  PrimaryActorTick.bCanEverTick = true;

  Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
  Capsule->InitCapsuleSize(42.0f, 96.0f);
  Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  Capsule->SetCollisionProfileName(TEXT("Pawn"));
  Capsule->SetSimulatePhysics(false);
  SetRootComponent(Capsule);

  Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
  Mesh->SetupAttachment(Capsule);
  Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
  Mesh->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
  Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
  Mesh->SetSimulatePhysics(false);

  SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
  SpringArm->SetupAttachment(Capsule);
  SpringArm->TargetArmLength = 300.0f;
  SpringArm->bUsePawnControlRotation = false;

  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
  Camera->bUsePawnControlRotation = false;
}

void APuzzlePawn::BeginPlay()
{
  Super::BeginPlay();

}

void APuzzlePawn::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  const FVector MoveOffset(
    MoveInput.X * MoveSpeed * DeltaTime, MoveInput.Y * MoveSpeed * DeltaTime, 0.0f
  );

  AddActorLocalOffset(MoveOffset, true);

  const float YawAmount = LookInput.X * LookSpeed * DeltaTime;
  AddActorLocalRotation(FRotator(0.0f, YawAmount, 0.0f));

  const float PitchAmount = LookInput.Y * LookSpeed * DeltaTime;
  SpringArm->AddLocalRotation(FRotator(PitchAmount, 0.0f, 0.0f));
}



void APuzzlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
  {
    if (MoveAction)
    {
      EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APuzzlePawn::Move);
      EnhancedInput->BindAction(MoveAction, ETriggerEvent::Completed, this, &APuzzlePawn::Move);
    }
    if (LookAction)
    {
      EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APuzzlePawn::Look);
      EnhancedInput->BindAction(LookAction, ETriggerEvent::Completed, this, &APuzzlePawn::Look);
    }
  }
  if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
  {
    if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
    {
      if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
      {
        if (InputMappingContext)
        {
          Subsystem->AddMappingContext(InputMappingContext, 0);
        }
      }
    }
  }
}

void APuzzlePawn::Move(const FInputActionValue& Value)
{
  MoveInput = Value.Get<FVector2D>();
}

void APuzzlePawn::Look(const FInputActionValue& Value)
{
  LookInput = Value.Get<FVector2D>();
}

