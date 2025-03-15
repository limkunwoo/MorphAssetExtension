#include "MEMorphAsset.h"

UMEMorphAsset::UMEMorphAsset()
{
	Parts.Add(EPartsWearType::Face1);
	Parts[EPartsWearType::Face1].AssetElement.Add(EMultiAssetElementType::FaceSubPartsEar);
	Parts[EPartsWearType::Face1].AssetElement.Add(EMultiAssetElementType::FaceSubPartsHead);
	
	Parts.Add(EPartsWearType::Face2);
	Parts[EPartsWearType::Face2].AssetElement.Add(EMultiAssetElementType::FaceSubPartsEyes);

	Parts.Add(EPartsWearType::Face3);
	Parts[EPartsWearType::Face3].AssetElement.Add(EMultiAssetElementType::FaceSubPartsEar);

	Parts.Add(EPartsWearType::Face4);
	Parts[EPartsWearType::Face4].AssetElement.Add(EMultiAssetElementType::FaceSubPartsEar);
}
