// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeConsumable.h"

// Sets default values
ACubeConsumable::ACubeConsumable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// Thinking of having a TriggerBox that detects when a certain Class type is in the trigger box.
	// Potential difficulties: Checking how much of the object is inside the trigger box.
	//		Could make the box small so we don't have to worry about that.
	//		Detect overlap in the Blueprint, since it's an event. (Although it might be possible in CPP?)
	// UFUNCTION makes things viewable from the engine code. Lets you add specifiers to it, like BlueprintCallable, allowing you to call it from BluePrints.
	// AddDynamic wnts 2 things: A reference to the class of the function you want this to interact on, and a reference to the class you want to call.
	// AddDynamic(this, &YourClass);
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

}

// Called when the game starts or when spawned
void ACubeConsumable::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACubeConsumable::OnBoxBeginOverlap);
	
}

// Called every frame
void ACubeConsumable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//
void ACubeConsumable::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//UE_LOG(LogTemp, Log, TEXT("Overlap detected!"));
	// Make sure other actor is available, don't want undefined behavior.
	if (OtherActor) {
		if (OtherActor->ActorHasTag("Deletable")) {
			OtherActor->K2_DestroyActor();
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("Does not have tag"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Invalid actor"));
	}
}