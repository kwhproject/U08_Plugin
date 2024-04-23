#include "AssetViewer.h"
#include "AssetViewer_Viewport.h"
#include "AdvancedPreviewSceneModule.h"
#include "IDetailsView.h"

TSharedPtr<FAssetViewer> FAssetViewer::Instance = nullptr;
const static FName ToolkitName = TEXT("AssetViewer");
const static FName ViewportTabID = TEXT("Viewport");
const static FName PreviewTabID = TEXT("Preview");
const static FName DetailsTabID = TEXT("Details");

void FAssetViewer::OpenWindow(UObject* InAsset)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}

	Instance = MakeShareable(new FAssetViewer());
	Instance->OpenWindow_International(InAsset);
}

void FAssetViewer::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();
	}
}

void FAssetViewer::OpenWindow_International(UObject* InAsset)
{
	Viewport = SNew(SAssetViewer_Viewport);

	FAdvancedPreviewSceneModule& previewScene = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");
	PreviewSceneSettings = previewScene.CreateAdvancedPreviewSceneSettingsWidget(Viewport->GetScene());

	FPropertyEditorModule& propertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs args(false, false, true, FDetailsViewArgs::ENameAreaSettings::ObjectsUseNameArea);
	DetailsView = propertyEditor.CreateDetailView(args);
	DetailsView->SetObject(InAsset);

	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("AssetViewer_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			// Toolbar
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			// Big Panel
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.75f)
				// Middle Panel
				->Split
				(
					FTabManager::NewStack()
					->AddTab(ViewportTabID, ETabState::OpenedTab)
				) // End Middle Panel

				// Right Panel
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.25f)

					// Preview Panel
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PreviewTabID, ETabState::OpenedTab)
					) // End Preview Panel

					// Detail Panel
					->Split
					(
						FTabManager::NewStack()
						->AddTab(DetailsTabID, ETabState::OpenedTab)
					) // End Detail Panel

				)// Right Panel

			) // End Big Panel

		);

	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), ToolkitName, layout, true, true, InAsset);

}

void FAssetViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	TabManager->RegisterTabSpawner(ViewportTabID, FOnSpawnTab::CreateSP(this, &FAssetViewer::Spawn_ViewportTab));
	TabManager->RegisterTabSpawner(PreviewTabID, FOnSpawnTab::CreateSP(this, &FAssetViewer::Spawn_PreviewSceneSettingsTab));
	TabManager->RegisterTabSpawner(DetailsTabID, FOnSpawnTab::CreateSP(this, &FAssetViewer::Spawn_DetailsViweTab));


}

FName FAssetViewer::GetToolkitFName() const
{
	return ToolkitName;
}

FText FAssetViewer::GetBaseToolkitName() const
{
	return FText::FromName(ToolkitName);
}

FString FAssetViewer::GetWorldCentricTabPrefix() const
{
	return ToolkitName.ToString();
}

FLinearColor FAssetViewer::GetWorldCentricTabColorScale() const
{
	return FLinearColor::Yellow;
}

TSharedRef<SDockTab> FAssetViewer::Spawn_ViewportTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			Viewport.ToSharedRef()
		];
}

TSharedRef<SDockTab> FAssetViewer::Spawn_PreviewSceneSettingsTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			PreviewSceneSettings.ToSharedRef()
		];
}

TSharedRef<SDockTab> FAssetViewer::Spawn_DetailsViweTab(const FSpawnTabArgs& inArgs)
{
	return SNew(SDockTab)
		[
			DetailsView.ToSharedRef()
		];
}
