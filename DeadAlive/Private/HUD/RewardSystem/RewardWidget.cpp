#include "HUD/RewardSystem/RewardWidget.h"
#include "LoadBlueprintClass.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void URewardWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Initialization();
	RightButton->OnClicked.AddDynamic(this, &URewardWidget::ClickRightButton);
	LeftButton->OnClicked.AddDynamic(this, &URewardWidget::ClickLeftButton);
}


// 모든 Row들 중 중복되지 않는 2개를 뽑아냄
void URewardWidget::Initialization()
{
	RewardTableAsset->GetAllRows<FRewardDataTableRow>(TEXT(""), RewardArray);

	int first = FMath::RandRange(0, RewardArray.Num()-1);
	int second = FMath::RandRange(0, RewardArray.Num()-1);

	// 선택할 수 있는 보상이 1개 이상일 경우 실행한다. - 무한 루프 방지
	if(RewardArray.Num() != 1)
	{
		while(first == second)
		{
			// UE_LOG(LogTemp, Warning, TEXT("중복중복"));
			second = FMath::RandRange(0, RewardArray.Num()-1);
		}
	}

	LeftInfo = RewardArray[first];
	RightInfo = RewardArray[second];

	SetViewOfWidgets();
	
}

void URewardWidget::SelectInputOnly()
{
	if(APlayerController* MyController = GetWorld()->GetFirstPlayerController())
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(MyController);
		MyController->SetShowMouseCursor(true);
	}
}

// 랜덤으로 선택된 두 개의 보상을 선택할 수 있게 위젯을 구성함
void URewardWidget::SetViewOfWidgets()
{
	// 이미지, 이름, 설명 설정해주기
	LeftSelectionName->SetText(LeftInfo->SelectionName);
	LeftDescriptionText->SetText(LeftInfo->Description);
	LeftDescriptionText->SetAutoWrapText(true);
	
	FSlateBrush Brush; Brush.SetResourceObject(LeftInfo->SelectionImage);
	LeftImage->SetBrush(Brush);

	// 오른쪽
	RightSelectionName->SetText(RightInfo->SelectionName);
	RightDescriptionText->SetText(RightInfo->Description);
	RightDescriptionText->SetAutoWrapText(true);
	
	Brush.SetResourceObject(RightInfo->SelectionImage);
	RightImage->SetBrush(Brush);

	// 마우스 보이게 하고 UI 클릭 가능하게
	SelectInputOnly();
}


void URewardWidget::DistributeItems(const FRewardDataTableRow& Info)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	const FVector PlayerLocation = (UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation() + FVector(0.f, 0.f, 30.f));
	for(int32 i = 0; i < Info.Count; i++)
	{
		if(!Info.InvenItem.IsNull())
		{
			if(UClass* SpawnClass = Info.InvenItem.LoadSynchronous())
			{
				GetWorld()->SpawnActor(SpawnClass, &PlayerLocation, &FRotator::ZeroRotator, SpawnParams);
			}
		}
		else
		{
			FString NewPath = Info.LoadPathString;
			if(UObject* BluePrintObject = LoadObject<UObject>(nullptr, *NewPath))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *NewPath);
				UClass* BluePrintUClass = Cast<UClass>(BluePrintObject);
				GetWorld()->SpawnActor(BluePrintUClass, &PlayerLocation, &FRotator::ZeroRotator, SpawnParams);
			}
		}
		/*if(!Info.InvenItem.IsNull())
		{
			if(UClass* SpawnClass = Info.InvenItem.LoadSynchronous())
			{
				GetWorld()->SpawnActor(SpawnClass, &PlayerLocation, &FRotator::ZeroRotator, SpawnParams);
			}
		}*/
		/*FString NewPath = Info.LoadPathString;
		if(UObject* BluePrintObject = LoadObject<UObject>(nullptr, *NewPath))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *NewPath);
			UClass* BluePrintUClass = Cast<UClass>(BluePrintObject);
			GetWorld()->SpawnActor(BluePrintUClass, &PlayerLocation, &FRotator::ZeroRotator, SpawnParams);
		}
		else
		{
			
		}*/
	}
	// 게임 모드로 변경
	GameInputOnly();
	this->RemoveFromParent();
}

void URewardWidget::ClickLeftButton()
{
	DistributeItems(*LeftInfo);
}

void URewardWidget::ClickRightButton()
{
	DistributeItems(*RightInfo);
}


// 활성화된다면 6개 중 2개를 뽑아서 화면에 출력해줄 것임
void URewardWidget::Test()
{
	if(!RewardTableAsset)
		UE_LOG(LogTemp, Error, TEXT("데이터 테이블을 삽입하십시오."));
	
	/*if(auto k = RewardTableAsset->FindRow<FRewardDataTableRow>(FName("DamageUpgrade"), TEXT("")))
	{
		const FString LoadPathString = k->LoadPath;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LoadPathString);
		
		LeftSelectionName->SetText(k->SelectionName);
		FSlateBrush Brush; Brush.SetResourceObject(k->SelectionImage);
		LeftImage->SetBrush(Brush);

		LeftDescriptionText->SetText(k->Description);
		
		GetWorld()->SpawnActor(LoadBlueprintClass->LoadToBlueprintAsset(LoadPathString));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("없는데?"));
	}*/
}

void URewardWidget::GameInputOnly()
{
	if(APlayerController* MyController = GetWorld()->GetFirstPlayerController())
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(MyController);
		MyController->SetShowMouseCursor(false);
	}
}
