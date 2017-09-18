// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class KeyColor : uint8
{
	Red,
	Green,
	Blue,
	Any
};

TCHAR* KeyColorToString(KeyColor c);
