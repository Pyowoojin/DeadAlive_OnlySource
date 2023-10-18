#pragma once

class LoadBlueprintClass
{
public:
	// 에셋 레퍼런스를 리턴함, 직접 Spawn해서 사용하던가 하면 됨!
	UClass* LoadToBlueprintAsset(FString& Text);
};
