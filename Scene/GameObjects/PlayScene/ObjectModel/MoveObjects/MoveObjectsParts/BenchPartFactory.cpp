#include "pch.h"

#include "BenchPartFactory.h"

#include"BenchBackWood.h"
#include"BenchFrame_Left.h"
#include"BenchFrame_Right.h"
#include"BenchUnderWood.h"

std::unique_ptr<IBenchComponent> BenchPartFactory::CreateBenchBackWood(IBenchComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IBenchComponent> benchBackWood = std::make_unique<BenchBackWood>(parent, position, angle);
	// ����������
	benchBackWood->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(benchBackWood);
}
std::unique_ptr<IBenchComponent> BenchPartFactory::CreateBenchFrame_Left(IBenchComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IBenchComponent> benchFrame_Left = std::make_unique<BenchFrame_Left>(parent, position, angle);
	// ����������
	benchFrame_Left->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(benchFrame_Left);
}

std::unique_ptr<IBenchComponent> BenchPartFactory::CreateBenchFrame_Right(IBenchComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IBenchComponent> benchFrame_Right = std::make_unique<BenchFrame_Right>(parent, position, angle);
	// ����������
	benchFrame_Right->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(benchFrame_Right);
}

std::unique_ptr<IBenchComponent> BenchPartFactory::CreateBenchUnderWood(IBenchComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//�v���y���̃C���X�^���X�𐶐�����
	std::unique_ptr<IBenchComponent> benchUnderWood = std::make_unique<BenchUnderWood>(parent, position, angle);
	// ����������
	benchUnderWood->Initialize();
	//�v���y���̂̃C���X�^���X��Ԃ�
	return move(benchUnderWood);
}
