// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CreateServerMainWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/TestMultiPlayGameInstance.h"

void UCreateServerMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CreateButton)
	{
		CreateButton->OnClicked.AddDynamic(this, &UCreateServerMainWidget::OnCreateButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UCreateServerMainWidget::OnJoinButtonClicked);
	}
	if (DisconnectButton)
	{
		DisconnectButton->OnClicked.AddDynamic(this, &UCreateServerMainWidget::OnDisconnectButtonClicked);
	}
}

void UCreateServerMainWidget::OnCreateButtonClicked()
{
	UTestMultiPlayGameInstance* GI = Cast<UTestMultiPlayGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->CreateServer();
	}
}

void UCreateServerMainWidget::OnJoinButtonClicked()
{
	UTestMultiPlayGameInstance* GI = Cast<UTestMultiPlayGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		FString IPAddress = GI->GetIPAddress();
		if (InputIPAddress)
		{
			FString InputIP = InputIPAddress->GetText().ToString();
			if (!InputIP.IsEmpty())
			{
				IPAddress = InputIP;
			}
		}

		GI->JoinServer(IPAddress);
	}
}

void UCreateServerMainWidget::OnDisconnectButtonClicked()
{
	UTestMultiPlayGameInstance* GI = Cast<UTestMultiPlayGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->DisconnectServer();
	}
}
