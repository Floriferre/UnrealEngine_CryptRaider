// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Called when the game starts
UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}



void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor!=nullptr)	// overlap되는 것이 있으면 언락 
	{
		UE_LOG(LogTemp,Display,TEXT("UNLOCKING"));	
	}
	else
	{
		// overlap되는 것이 없으면 락 
		UE_LOG(LogTemp,Display,TEXT("RELOCKING"));
	}
	
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);	// 해당 actor가 overlapping중인 모든 actor를 반환한다
	
	// 포인터를 사용해서 Range Base For문 
	for (AActor* Actor: Actors)
	{
		//  Actor의 태그가 맞는지 확인
		if (Actor->ActorHasTag(AcceptableActorTag))
		{
			return Actor;
		}
	}
	return nullptr;	// 발견되는 것이 없으면 널포인터 반환
}


