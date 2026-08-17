#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class UStaticMeshComponent;

UCLASS()
class CH3_PROJECT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingPlatform();

  virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent* Mesh;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
  float MoveSpeed = 200.0f;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
  float MaxRange = 300.0f;

  FVector StartLocation;

  float MoveDirection = 1.0f;

};
