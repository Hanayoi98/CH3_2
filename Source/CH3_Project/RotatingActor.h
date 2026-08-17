#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class CH3_PROJECT_API ARotatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotatingActor();

  virtual void Tick(float DeltaTime) override;

protected:
  virtual void BeginPlay() override;

private:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent* Mesh;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
  FRotator RotationSpeed = FRotator(0.0f, 90.0f, 0.0f);

};
