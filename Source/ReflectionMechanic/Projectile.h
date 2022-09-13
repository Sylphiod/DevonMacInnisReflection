// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS(config = Game)
class REFLECTIONMECHANIC_API AProjectile : public AActor
{
    GENERATED_UCLASS_BODY()

       
        UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
        TSubobjectPtr<USphereComponent> CollisionComponent;

  
    FVector MyVelocity;

 
    bool bReflected;

 
    UFUNCTION()
        void OnOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

    UPROPERTY(EditAnywhere, Category = Projectile)
        float fSpeed;

  
    UPROPERTY(EditAnywhere, Category = Projectile)
        float fBounceSpeedLoss;

  
    virtual void OnConstruction(const FTransform& Transform) OVERRIDE;
    virtual void ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) OVERRIDE;
    virtual void Tick(float DeltaSeconds) OVERRIDE;
  
};