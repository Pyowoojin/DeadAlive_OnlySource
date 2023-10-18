#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotificationHUD.generated.h"

class UTextBlock;

UCLASS()
class DEADALIVE_API UNotificationHUD : public UUserWidget
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintCallable)
	void SetNotificationMsg(const FText& NewText);

	UPROPERTY(meta =(BindWidget))
	UTextBlock* NotificationText;

private :
	
	
};
