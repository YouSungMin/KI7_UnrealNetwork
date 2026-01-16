// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMultiPlayGameInstance.h"
#include "Kismet/GameplayStatics.h"
UTestMultiPlayGameInstance::UTestMultiPlayGameInstance()
{
	ServerIP = "127.0.0.1";
}

void UTestMultiPlayGameInstance::CreateServer()
{
	FString MapName;
	if (!ServerLevelAsset.IsNull())
	{
		MapName = ServerLevelAsset.GetLongPackageName();
	}
	else
	{
		MapName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	}

	UWorld* World = GetWorld();
	if(!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World가 없습니다. 서버를 만들 수 없습니다."));
		return;
	}

	FString Options = FString::Printf(TEXT("listen?MaxPlayers=%d"),MaxPlayers);
	UE_LOG(LogTemp, Log, TEXT("리슨 서버 생성 : %s, 최대 인원 : %d"),*MapName,MaxPlayers);

	UGameplayStatics::OpenLevel(World, FName(*MapName), true, Options);
	UE_LOG(LogTemp, Log, TEXT("리슨 서버 시작 "));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, TEXT("리슨 서버 시작 "));
	}
}

void UTestMultiPlayGameInstance::JoinServer(FString IPAddress)
{
	if (IPAddress.IsEmpty())
	{
		IPAddress = ServerIP;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World가 없습니다. 서버에 접속할 수 없습니다."));
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController가 없습니다. 서버에 접속할 수 없습니다."));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("서버에 접속합니다 : %s"), *IPAddress);
	PC->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);

	UE_LOG(LogTemp, Log, TEXT("서버에 접속 시작"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, TEXT("서버 접속 시작"));
	}

}

void UTestMultiPlayGameInstance::DisconnectServer()
{
	FString MapName;
	if (!MainLevelAsset.IsNull())
	{
		MapName = MainLevelAsset.GetLongPackageName();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MainLevelAsset이 없습니다!!! 맵을 이동 할 수 없습니다."));
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World가 없습니다"));
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController가 없습니다"));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("서버에서 나가는 중입니다."));
	PC->ClientTravel(MapName, ETravelType::TRAVEL_Absolute);

	UE_LOG(LogTemp, Error, TEXT("서버 접속 해제"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, TEXT("서버 접속 해제 "));
	}
}
