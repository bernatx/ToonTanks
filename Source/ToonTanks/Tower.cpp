// Copyright Denys Kryvytskyi. All Rights Reserved.

#include "Tower.h"
#include "Tank.h"

#include "TimerManager.h"

#include "Kismet/GameplayStatics.h"

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    bIsDestroyed = true;
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (!Tank) {
        return;
    }

    bIsDestroyed = false;

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this,
                                    &ATower::TryFire, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bIsDestroyed && Tank && CanFire()) {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::TryFire()
{
    if (!bIsDestroyed && CanFire()) {
        Fire();
    }
}

bool ATower::CanFire() const
{
    return Tank && Tank->IsAlive() && FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange && !bIsDestroyed;
}

bool ATower::IsDestroyed() const
{
    return bIsDestroyed;
}
