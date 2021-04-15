// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "Algo/Transform.h"
#include "Persona/Public/IAnimSequenceCurveEditor.h"


TArray<UAnimationAsset*> UMyBlueprintFunctionLibrary::GetAllAnimationOfSkeleton(USkeleton* Skeleton)
{
	TArray<UAnimationAsset*> AnimList;

	if (Skeleton == nullptr)
	{
		return AnimList;
	}

	for (TObjectIterator<UAnimationAsset> Iter; Iter; ++Iter)
	{
		if(Skeleton->GetWorld()!=(*Iter)->GetWorld()) {continue;}

		if (Skeleton == (*Iter)->GetSkeleton())
		{
			AnimList.Add(*Iter);
		}
	}
	return AnimList;
}


void UMyBlueprintFunctionLibrary::SearchReferenceCurve(UAnimSequence* InSeq, TArray<FName> CurveName, TArray<FAnimRef> CurRef, TArray<FAnimRef>& RefData)
{
	RefData.Empty();

	for (FName name : CurveName)
	{
		bool HasName = false;
		for (auto& Ref : CurRef)
		{
			if (Ref.CurveName == name)
			{
				Ref.RefAnimSequence.AddUnique(InSeq);
				HasName = true;
				break;
			}
		}

		if (!HasName)
		{
			FAnimRef animref;
			animref.CurveName = name;
			animref.RefAnimSequence.Add(InSeq);
			RefData.Add(animref);
		}
	}
}


TArray<FAnimRef> UMyBlueprintFunctionLibrary::SearchReferenceCurveWithSkeleton(
	TArray<FAnimSeqCurveInfo> seqTable,
	TArray<FAnimMontageCurveInfo> montageTable,
	TArray<FAnimBaseCurveInfo> baseTable)
{
	TArray<FAnimRef> RefList;

	for (auto& curveInfo : baseTable)
	{
		UAnimSequenceBase* base = curveInfo.AnimBase;
		TArray<FName> seqCurveName = curveInfo.CurveNames;

		for (FName name : seqCurveName)
		{
			bool HasName = false;
			for (auto& Ref : RefList)
			{
				if (Ref.CurveName == name)
				{
					Ref.RefALL.AddUnique(base);
					HasName = true;
					break;
				}
			}

			if (!HasName)
			{
				FAnimRef animref;
				animref.CurveName = name;
				animref.RefALL.Add(base);
				RefList.Add(animref);
			}
		}
	}

	for (auto& curveInfo : seqTable)
	{
		UAnimSequence* seq = curveInfo.AnimSeq;
		TArray<FName> seqCurveName = curveInfo.CurveNames;

		for (FName name : seqCurveName)
		{
			bool HasName = false;
			for (auto& Ref : RefList)
			{
				if (Ref.CurveName == name)
				{
					Ref.RefAnimSequence.AddUnique(seq);
					HasName = true;
					break;
				}
			}

			if (!HasName)
			{
				FAnimRef animref;
				animref.CurveName = name;
				animref.RefAnimSequence.Add(seq);
				RefList.Add(animref);
			}
		}
	}

	for (auto& curveInfo : montageTable)
	{
		UAnimMontage* montage = curveInfo.AnimMontage;
		TArray<FName> seqCurveName = curveInfo.CurveNames;

		for (FName name : seqCurveName)
		{
			bool HasName = false;
			for (auto& Ref : RefList)
			{
				if (Ref.CurveName == name)
				{
					Ref.RefAnimMontage.AddUnique(montage);
					HasName = true;
					break;
				}
			}

			if (!HasName)
			{
				FAnimRef animref;
				animref.CurveName = name;
				animref.RefAnimMontage.Add(montage);
				RefList.Add(animref);
			}
		}
	}

	return RefList;
}

void UMyBlueprintFunctionLibrary::GetAnimSeqBaseCurveNames(const UAnimSequenceBase* AnimationSequence, ERawCurveTrackTypes CurveType, TArray<FName>& CurveNames)
{
	CurveNames.Empty();
	if (AnimationSequence)
	{
		auto GetCurveName = [](const auto& Curve) -> FName
		{
			return Curve.Name.DisplayName;
		};

		switch (CurveType)
		{
		case ERawCurveTrackTypes::RCT_Float:
		{
			Algo::Transform(AnimationSequence->RawCurveData.FloatCurves, CurveNames, GetCurveName);
			break;
		}

		case ERawCurveTrackTypes::RCT_Vector:
		{
			Algo::Transform(AnimationSequence->RawCurveData.VectorCurves, CurveNames, GetCurveName);
			break;
		}

		case ERawCurveTrackTypes::RCT_Transform:
		{
			Algo::Transform(AnimationSequence->RawCurveData.TransformCurves, CurveNames, GetCurveName);
			break;
		}

		default:
		{
			//UE_LOG(LogAnimationBlueprintLibrary, Warning, TEXT("Invalid CurveType supplied for GetAnimationCurveNames"));
		}
		}

	}
	else
	{
		//UE_LOG(LogAnimationBlueprintLibrary, Warning, TEXT("Invalid Animation Sequence supplied for GetAnimationCurveNames"));
	}
}
