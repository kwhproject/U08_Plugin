#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class TOYPLUGIN_API FStaticMesh_DetailPanel : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	FReply OnClicked_ShuffleMaterial();
	FReply OnClicked_SaveMesh();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
