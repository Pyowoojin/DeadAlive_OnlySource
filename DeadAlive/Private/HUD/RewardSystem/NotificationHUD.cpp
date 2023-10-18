#include "HUD/RewardSystem/NotificationHUD.h"

#include "Components/TextBlock.h"

void UNotificationHUD::SetNotificationMsg(const FText& NewText)
{
	if(NotificationText)
		NotificationText->SetText(NewText);
}