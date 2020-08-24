// Fill out your copyright notice in the Description page of Project Settings.


#include "MySpikeBall.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "BallGameGameModeBase.h"


// Sets default values
AMySpikeBall::AMySpikeBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Movement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Movement"));

	RootComponent = Sphere;
	Body->SetupAttachment(RootComponent);

	Sphere->SetSphereRadius(100.f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT(
		"StaticMesh'/Game/Data/SpikeBall/Mesh/SM_SpikeBall.SM_SpikeBall'"));
	if (SM_Body.Succeeded()) {
		Body->SetStaticMesh(SM_Body.Object);
	}

	Body->SetCollisionProfileName(TEXT("OverlapAll"));

	static ConstructorHelpers::FObjectFinder<USoundBase> S_Coin(TEXT(
		"SoundWave'/Game/Sound/Explosion.Explosion'"));
	if (S_Coin.Succeeded()) {
		SpikeSound = S_Coin.Object;
	}
}

// Called when the game starts or when spawned
void AMySpikeBall::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AMySpikeBall::ProcessBeginOverlap);
}

// Called every frame
void AMySpikeBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMySpikeBall::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	if (OtherActor->ActorHasTag(TEXT("Player"))) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SpikeSound, GetActorLocation());

		ABallGameGameModeBase* GM = Cast<ABallGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		GM->GameOver();

		OtherActor->Destroy();
		Destroy();
	}
}