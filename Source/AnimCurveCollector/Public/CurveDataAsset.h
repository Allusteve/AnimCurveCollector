// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimationAsset.h"
#include "Animation/Skeleton.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimComposite.h"
#include "CurveDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FAnimRef
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurveName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimSequence*> RefAnimSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> RefAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimationAsset*> RefALL;

};

USTRUCT(BlueprintType)
struct FAnimSeqCurveInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequence* AnimSeq = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> CurveNames;
};

USTRUCT(BlueprintType)
struct FAnimMontageCurveInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AnimMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> CurveNames;
};

USTRUCT(BlueprintType)
struct FAnimBaseCurveInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequenceBase* AnimBase = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> CurveNames;
};

/**
 * 
 */
UCLASS(Blueprintable)
class ANIMCURVECOLLECTOR_API UCurveDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	USkeleton* SourceSkeleton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")
	TArray<FAnimRef> AnimRefArray;
	
};
