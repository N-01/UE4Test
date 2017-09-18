// Fill out your copyright notice in the Description page of Project Settings.

#include "Key.h"

TCHAR* KeyColorToString(KeyColor c) {
	switch (c)
	{
	case KeyColor::Red:
		return L"Red";
	case KeyColor::Green:
		return L"Green";
	case KeyColor::Blue:
		return L"Blue";

	default:
		return L"";
	}
}