// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"	// GetWorld 사용
#include "DrawDebugHelpers.h"
// #include "PhysicsEngine/PhysicsHandleComponent.h"	// 물체를 움켜쥐기 위하여 -> 헤더에 넣었으니 삭제



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;	// 현재 위치 + 잡는 위치 
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());

}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
	{
		return;
	}

	
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDiatance;

	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	// persist true로 하면 안 사라진다!
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	// 충돌 감지 하기 위한 형태 - 구 
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;

	// Hit 했는지 아닌지 판별
	bool HashHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
		);

	// Hit 했으면 Component를 가져와서 정확한 위치를 잡아 Rotation을 받아온다
	if (HashHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,	// 정확한 위치를 잡아야 하므로 Impact Point
			GetComponentRotation()	// Grabber의 Rotation
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Released Grabber"));
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber Requires a UPhysiceHandleComponent."));
	}
	return Result;
}
