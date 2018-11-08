// Flynn's Rad Copyright.

#include "ShipBase.h"

AShipBase::AShipBase()
{
	PrimaryActorTick.bCanEverTick = true;
    
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;
    ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
    ShipMesh->SetupAttachment(RootComponent);
}

void AShipBase::BeginPlay()
{
	Super::BeginPlay();
    Pitch = GetActorRotation().Pitch;
}

void AShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DeltaSeconds = DeltaTime;
    
    UpdateShipHorizontalLocation();
    UpdateShipVerticalLocation();
}

void AShipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    InputComponent->BindAxis("MoveUp", this, &AShipBase::SetVerticalSpeed);
    InputComponent->BindAxis("MoveRight", this, &AShipBase::SetHorizontalSpeed);
}

void AShipBase::SetVerticalSpeed(float AxisValue)
{
    VerticalSpeed = FMath::FInterpTo(VerticalSpeed, (MovementSpeed * AxisValue), DeltaSeconds, 6);
}

void AShipBase::SetHorizontalSpeed(float AxisValue)
{
    HorizontalSpeed = FMath::FInterpTo(HorizontalSpeed, (MovementSpeed * AxisValue), DeltaSeconds, 6);
}

void AShipBase::UpdateShipHorizontalLocation()
{
    FVector ShipLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    
    FVector HorizontalLocationModifier {HorizontalSpeed, 0.f, 0.f};
    FVector NewHorizontalLocation = ShipLocation + HorizontalLocationModifier;
    SetActorLocation(NewHorizontalLocation, true);
}

void AShipBase::UpdateShipVerticalLocation()
{
    FVector ShipLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    
    FVector VerticalLocationModifier {0.f, 0.f, VerticalSpeed};
    FVector NewVerticalLocation = ShipLocation + VerticalLocationModifier;
    SetActorLocation(NewVerticalLocation, true);
    
    /*float VerticalSpeedModifier = -10.f;
    float InterpolationSpeed = 30.f;
    FRotator TargetRotation {0.f, 0.f, VerticalSpeed * VerticalSpeedModifier + Pitch};
    ShipMesh->SetRelativeRotation(FMath::RInterpConstantTo(ShipMesh->GetRelativeTransform().GetRotation().Rotator(), TargetRotation, DeltaSeconds, InterpolationSpeed), true);*/
}
