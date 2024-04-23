#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class TOYPLUGIN_API FAssetViewer : public FAssetEditorToolkit
{
public:
	static void OpenWindow(UObject* InAsset);
	static void Shutdown();

private:
	void OpenWindow_International(UObject* InAsset);

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

public:
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

private:
	TSharedRef<SDockTab> Spawn_ViewportTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_PreviewSceneSettingsTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_DetailsViweTab(const FSpawnTabArgs& inArgs);

private:
	static TSharedPtr<FAssetViewer> Instance;

	TSharedPtr<class SAssetViewer_Viewport> Viewport;
	TSharedPtr<class SWidget> PreviewSceneSettings;
	TSharedPtr<class IDetailsView> DetailsView;
};
