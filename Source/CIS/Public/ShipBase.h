// Flynn's Rad Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "ShipBase.generated.h"

UCLASS()
class CIS_API AShipBase : public APawn
{
	GENERATED_BODY()

public:
	AShipBase();
    
    virtual void Tick(float DeltaTime) override;
    
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ship Setup")
    UBoxComponent* CollisionBox = nullptr;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ship Setup")
    UStaticMeshComponent* ShipMesh = nullptr;
    
    UPROPERTY(BlueprintReadOnly, Category="Ship Setup")
    float Pitch = 0.f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ship Setup")
    float MovementSpeed = 20.f;
    
    UPROPERTY(BlueprintReadOnly, Category="Ship Setup")
    float VerticalSpeed = 0.f;
    
    UPROPERTY(BlueprintReadOnly, Category="Ship Setup")
    float HorizontalSpeed = 0.f;

private:
    void SetVerticalSpeed(float AxisValue);
    void SetHorizontalSpeed(float AxisValue);
    void UpdateShipHorizontalLocation();
    void UpdateShipVerticalLocation();
    
    float DeltaSeconds = 0.f;
};
