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

	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	// index base for문 
	for (int i=0; i < Actors.Num(); i++)
	{
		FString ActorName = Actors[i]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *ActorName);
	}

	// 포인터를 사용해서 Range Base For문 
	for (AActor* Actor: Actors)
	{
		FString ActorName = Actor->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *ActorName);
	}

}

