#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  SetRootComponent(Mesh);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

  StartLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  const float CurrentX = GetActorLocation().X;
  const float MaxX = StartLocation.X + MaxRange;

  if (CurrentX >= MaxX)
  {
    MoveDirection = -1.0f;
  }
  else if (CurrentX <= StartLocation.X)
  {
    MoveDirection = 1.0f;
  }

  const float MoveAmount = MoveSpeed * DeltaTime * MoveDirection;
  AddActorLocalOffset(FVector(MoveAmount, 0.0f, 0.0f));
}

