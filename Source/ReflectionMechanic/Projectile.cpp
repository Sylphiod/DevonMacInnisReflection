// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile(const class FPostConstructInitializeProperties& PCIP)
    : Super(PCIP)
{
    PrimaryActorTick.bCanEverTick = true;
    fSpeed = 3000.f;
    fBounceSpeedLoss = 0.7f;


    CollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlap);   // set up a notification for when this component overlaps something
    CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnOverlap);     // set up a notification for when this component overlaps something
    RootComponent = CollisionComponent;


    InitialLifeSpan = 3.0f;
}

void AProjectile::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    MyVelocity = GetActorForwardVector() * fSpeed;
}

void Projectile::OnOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
    {
        
        if (OtherComp->IsSimulatingPhysics())
        {
            OtherComp->AddImpulseAtLocation(MyVelocity * 100.f, GetActorLocation());

            Destroy();
        }
    }
}

void Projectile::ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp,
    bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::ReceiveHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    
    FVector ReflectedVelocity = fBounceSpeedLoss * (-2 * FVector::DotProduct(MyVelocity, HitNormal) * HitNormal + MyVelocity);
    MyVelocity = ReflectedVelocity;
    ReflectedVelocity.Normalize();
    SetActorRotation(ReflectedVelocity.Rotation());

    bReflected = true;
}

void Projectile::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    FColor LineColor = bReflected ? FColor::Red : FColor::Green;
    DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + MyVelocity * DeltaSeconds, LineColor, false, 2.f, 0, 1.f);

    SetActorLocation(GetActorLocation() + MyVelocity * DeltaSeconds, true);
}
