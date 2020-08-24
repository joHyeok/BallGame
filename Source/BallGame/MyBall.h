// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyBall.generated.h"

UCLASS()
class BALLGAME_API AMyBall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera;

	void ForwardBackward(float value);
	void LeftRight(float value);
	void SetSpeed(float speed);

	float bollSpeed;
	float ForwardBackwardSpeed;
	float LeftRightSpeed;

};
