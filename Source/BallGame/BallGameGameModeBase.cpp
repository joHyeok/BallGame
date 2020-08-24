// Copyright Epic Games, Inc. All Rights Reserved.


#include "BallGameGameModeBase.h"
#include "MyBall.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ABallGameGameModeBase::ABallGameGameModeBase() {
	DefaultPawnClass = AMyBall::StaticClass();
}

void ABallGameGameModeBase::CheckNextLevel() {
	TArray<AActor*> Output;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Coin"), Output);
	if (Output.Num() == 0) {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("CompleteLevel"));

		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, this, &ABallGameGameModeBase::CheckCoinTimer, 3.0f, true);
	}
}

void ABallGameGameModeBase::GameOver() {
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GameOver"));
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &ABallGameGameModeBase::CheckGameOverTimer, 3.0f, true);
}

void ABallGameGameModeBase::CheckCoinTimer() {

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Map02"));
}

void ABallGameGameModeBase::CheckGameOverTimer() {
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Map01"));
}