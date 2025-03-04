// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"	// GetWorld 사용
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"	// 물체를 움켜쥐기 위하여 



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

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Got Physics Handle: %s"), *PhysicsHandle->GetName());
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle Found!"));
	}
	

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
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

	if (HashHit)
	{
		// HitResult Location : 충돌이 발생한 위치(Impact Point보다는 덜 구체적인 값)
		// HitResult ImpactPoint : 충돌이 실제로 발생한 정확한 지점의 월드 공간 좌표 
		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		
		AActor* HitActor = HitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *HitActor->GetActorNameOrLabel());
	}else
	{
		UE_LOG(LogTemp, Display, TEXT("No Hit"));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Released Grabber"));
}

