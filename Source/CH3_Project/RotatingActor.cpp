#include "RotatingActor.h"

ARotatingActor::ARotatingActor()
{
	PrimaryActorTick.bCanEverTick = true;

  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  SetRootComponent(Mesh);
}

void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  AddActorLocalRotation(RotationSpeed * DeltaTime);
}

