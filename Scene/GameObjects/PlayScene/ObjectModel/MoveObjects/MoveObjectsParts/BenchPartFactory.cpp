#include "pch.h"

#include "BenchPartFactory.h"

#include"BenchBackWood.h"
#include"BenchFrame_Left.h"
#include"BenchFrame_Right.h"
#include"BenchUnderWood.h"

std::unique_ptr<IBenchComponent> BenchPartFactory::CreateBenchBackWood(IBenchComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IBenchComponent> benchBackWood = std::make_unique<BenchBackWood>(parent, position, angle);
	// 初期化する
	benchBackWood->Initialize();
	//プロペラののインスタンスを返す
	return move(benchBackWood);
}
std::unique_ptr<IBenchComponent> BenchPartFactory::CreateBenchFrame_Left(IBenchComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IBenchComponent> benchFrame_Left = std::make_unique<BenchFrame_Left>(parent, position, angle);
	// 初期化する
	benchFrame_Left->Initialize();
	//プロペラののインスタンスを返す
	return move(benchFrame_Left);
}

std::unique_ptr<IBenchComponent> BenchPartFactory::CreateBenchFrame_Right(IBenchComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IBenchComponent> benchFrame_Right = std::make_unique<BenchFrame_Right>(parent, position, angle);
	// 初期化する
	benchFrame_Right->Initialize();
	//プロペラののインスタンスを返す
	return move(benchFrame_Right);
}

std::unique_ptr<IBenchComponent> BenchPartFactory::CreateBenchUnderWood(IBenchComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//プロペラのインスタンスを生成する
	std::unique_ptr<IBenchComponent> benchUnderWood = std::make_unique<BenchUnderWood>(parent, position, angle);
	// 初期化する
	benchUnderWood->Initialize();
	//プロペラののインスタンスを返す
	return move(benchUnderWood);
}
