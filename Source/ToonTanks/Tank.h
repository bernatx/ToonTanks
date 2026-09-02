// Copyright Denys Kryvytskyi. All Rights Reserved.

#pragma once

#include "BasePawn.h"
#include "CoreMinimal.h"
#include "InputActionValue.h"

#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn {
    GENERATED_BODY()

public:
    ATank();

    virtual void HandleDestruction() override;

    APlayerController* GetPlayerController() const { return TankPlayerController; }

    bool IsAlive() const { return bIsAlive; }

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    void Move(const FInputActionValue& Value);
    void Turn(const FInputActionValue& Value);
    void FireFromInput(const FInputActionValue& Value);
    void Cursor(const FInputActionValue& Value);

 private:
    APlayerController* TankPlayerController;

    bool bIsAlive { false };

    bool bIsInitialized;
};
