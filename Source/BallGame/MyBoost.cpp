// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBoost.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MyBall.h"

// Sets default values
AMyBoost::AMyBoost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));

	RootComponent = Box;
	Body->SetupAttachment(RootComponent);

	Box->SetBoxExtent(FVector(50.f, 50.f, 20.f));
	Body->SetRelativeLocation(FVector(0, 0, -20.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT(
		"StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (SM_Body.Succeeded()) {
		Body->SetStaticMesh(SM_Body.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> M_Body(TEXT(
		"Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (M_Body.Succeeded()) {
		Body->SetMaterial(0, M_Body.Object);
	}

}

// Called when the game starts or when spawned
void AMyBoost::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AMyBoost::ProcessBeginOverlap);
}

// Called every frame
void AMyBoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyBoost::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	if (OtherActor->ActorHasTag(TEXT("Player"))) {
		AMyBall* MyBall = Cast<AMyBall>(OtherActor);
		MyBall->SetSpeed(-10000.0f);
		UE_LOG(LogClass, Warning, TEXT("On the Boost"));
	}
}