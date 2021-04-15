// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Animation/AnimationAsset.h"
#include "Animation/Skeleton.h"
#include "CurveDataAsset.h"
#include "MyBlueprintFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS()
class ANIMCURVECOLLECTOR_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "MyFunction|MyClass")
	static TArray<UAnimationAsset*> GetAllAnimationOfSkeleton(USkeleton* Skeleton);

	UFUNCTION(BlueprintCallable, Category = "MyFunction|MyClass")
	static void SearchReferenceCurve(UAnimSequence* InSeq, TArray<FName> CurveName, TArray<FAnimRef> CurRef, TArray<FAnimRef>& RefData);

	UFUNCTION(BlueprintCallable, Category = "MyFunction|MyClass")
	static TArray<FAnimRef> SearchReferenceCurveWithSkeleton(
		TArray<FAnimSeqCurveInfo> seqTable,
		TArray<FAnimMontageCurveInfo> montageTable,
		TArray<FAnimBaseCurveInfo> baseTable);

	UFUNCTION(BlueprintPure, Category = "AnimationBlueprintLibrary|Animation")
	static void GetAnimSeqBaseCurveNames(const UAnimSequenceBase* AnimationSequence, ERawCurveTrackTypes CurveType, TArray<FName>& CurveNames);
	
};
