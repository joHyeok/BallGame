// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCoin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/Soundbase.h"
#include "BallGameGameModeBase.h"

// Sets default values
AMyCoin::AMyCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Movement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Movement"));

	RootComponent = Sphere;
	Body->SetupAttachment(RootComponent);

	Sphere->SetSphereRadius(75.f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT(
		"StaticMesh'/Game/Data/Coin/Mesh/SM_Coin.SM_Coin'"));
	if (SM_Body.Succeeded()) {
		Body->SetStaticMesh(SM_Body.Object);
	}

	Body->SetRelativeLocation(FVector(0, 0, -75.f));
	Body->SetCollisionProfileName(TEXT("OverlapAll"));

	Tags.Add(TEXT("Coin"));

	static ConstructorHelpers::FObjectFinder<USoundBase> S_Coin(TEXT(
		"SoundWave'/Game/Sound/Coin.Coin'"));
	if (S_Coin.Succeeded()) {
		CoinSound = S_Coin.Object;
	}
}

// Called when the game starts or when spawned
void AMyCoin::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AMyCoin::ProcessBeginOverlap);
}

// Called every frame
void AMyCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCoin::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	if (OtherActor->ActorHasTag(TEXT("Player"))) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), CoinSound, GetActorLocation());
		Destroy();

		ABallGameGameModeBase* GM = Cast<ABallGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		GM->CheckNextLevel();
	}
}