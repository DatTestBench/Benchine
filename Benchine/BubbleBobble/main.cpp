// BubbleBobble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "BubbleBobblePCH.h"
#if _DEBUG
#include "vld.h"
#endif
#include "BubbleBobble.h"
#include "BenchineRunner.h"


int main(int, char* [])
{
	BenchineRunner engine;
	engine.Run<BubbleBobble>();
	return 0;
}
