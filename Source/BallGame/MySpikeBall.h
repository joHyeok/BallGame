// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpikeBall.generated.h"

UCLASS()
class BALLGAME_API AMySpikeBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySpikeBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class URotatingMovementComponent* Movement;

	UFUNCTION()
		void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USoundBase* SpikeSound;
};
