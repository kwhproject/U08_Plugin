#include "AssetViewer_Viewport.h"

SAssetViewer_Viewport::SAssetViewer_Viewport()
{
}

void SAssetViewer_Viewport::Construct(const FArguments& InArgs)
{
}

TSharedRef<FEditorViewportClient> SAssetViewer_Viewport::MakeEditorViewportClient()
{
	return TSharedRef<FEditorViewportClient>();
}

void SAssetViewer_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	// Have to Super Call?
	// FGCObject::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(AssetMesh);
	Collector.AddReferencedObject(FloorMesh);
}

