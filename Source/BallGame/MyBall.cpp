// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBall.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AMyBall::AMyBall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	RootComponent = Sphere;
	Body->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT(
		"StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SM_Body.Succeeded()) {
		Body->SetStaticMesh(SM_Body.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> M_Body(TEXT(
		"Material'/Game/Data/Player/M_PLayer.M_PLayer'"));
	if (M_Body.Succeeded()) {
		Body->SetMaterial(0, M_Body.Object);
	}
	
	Sphere->SetSphereRadius(32.f);
	Sphere->SetSimulatePhysics(true);
	Sphere->SetMassOverrideInKg(NAME_None, 10.0f, true);
	Sphere->SetCollisionProfileName(TEXT("PhysicsActor"));

	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	bollSpeed = 50000.f;
	ForwardBackwardSpeed = 1.f;
	LeftRightSpeed = 0;

	Tags.Add(TEXT("Player"));
}

// Called when the game starts or when spawned
void AMyBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Sphere->AddForce(FVector(ForwardBackwardSpeed, LeftRightSpeed, 0) * bollSpeed, NAME_None);
}

// Called to bind functionality to input
void AMyBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("ForwardBackward"), this, &AMyBall::ForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyBall::LeftRight);
}

void AMyBall::ForwardBackward(float value) {
	ForwardBackwardSpeed = value;
}

void AMyBall::LeftRight(float value) {
	LeftRightSpeed = value;
}

void AMyBall::SetSpeed(float speed) {
	bollSpeed = speed;
	UE_LOG(LogClass, Warning, TEXT("Setting speed"));
}