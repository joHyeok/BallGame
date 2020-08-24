// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCoin.generated.h"

UCLASS()
class BALLGAME_API AMyCoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCoin();

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
		class USoundBase* CoinSound;
};
