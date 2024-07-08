#include "pch.h"
#include"Bench.h"
#include <math.h>
#include<random>
using namespace DirectX;
#include"BenchManager.h"

#include"BenchParts/BenchPartFactory.h"

Bench::Bench():
	MoveObjects()
{
	SetModel(Resources::GetInstance()->GetBenchModel());

	AddParts(BenchPartFactory::CreateBenchFrame_Left(nullptr, GetPosition(), GetRotate()));
	AddParts(BenchPartFactory::CreateBenchFrame_Right(nullptr, GetPosition(), GetRotate()));
}

