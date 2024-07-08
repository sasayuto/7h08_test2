#include "pch.h"
#include"Sun.h"
#include<random>
using namespace DirectX;

//�����|�W�V����
const DirectX::SimpleMath::Vector3 Sun::INITIAL_POSITION(1100, 600, 600);

//������]
const DirectX::SimpleMath::Quaternion Sun::INITIAL_ROTATE(
	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(0),						//X��]
		DirectX::XMConvertToRadians(0),						//Y��]
		DirectX::XMConvertToRadians(225)						//Z��]
	)
);

const float Sun::SUNSET_TIME(4);						//���v����	()
const float Sun::LIGHT_INTENSITY_LOWER_LIMIT(0.0f);		//���̉���	(0�`)
const float Sun::LIGHT_INTENSITY_UPPER_LIMIT(1);		//���̏��	(0�`)
const float Sun::SUNSHINE_HOURS(180.0f / 100.0f);				//���Ǝ���	(m/s)



Sun::Sun() :
	m_position(SimpleMath::Vector3::Zero),
	m_pSupplyPointModel(nullptr),
	m_rotate(DirectX::SimpleMath::Quaternion::Identity),
	m_rightDirect(DirectX::SimpleMath::Vector3::Zero),
	m_objectsRight(0)
{
}

Sun::~Sun()
{

}

void Sun::Initialize()
{
	//���ʂɉ�]����N�I�[�^�j�I��
	//�S�T�x�N���オ�点��x�����x�N�g��(���z�̌��̕����x�N�g��)
	m_rightDirect = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitX,INITIAL_ROTATE);

	//���z�̈ʒu���v�Z
	m_position = m_rightDirect * INITIAL_POSITION;

	m_objectsRight = m_rightDirect.y * 1.7320509f * SUNSET_TIME;
	if (m_objectsRight >= LIGHT_INTENSITY_UPPER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_UPPER_LIMIT;

	if (m_objectsRight <= LIGHT_INTENSITY_LOWER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_LOWER_LIMIT;

}

void Sun::Update(const float& elapsedTime)
{
	//���ʂɉ�]����N�I�[�^�j�I��
	DirectX::SimpleMath::Quaternion q;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(elapsedTime * SUNSHINE_HOURS));
	m_rotate = q * m_rotate;

	//�S�T�x�N���オ�点��x�����x�N�g��(���z�̌��̕����x�N�g��)
	m_rightDirect = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitX,m_rotate * INITIAL_ROTATE);

	//���z�̈ʒu���v�Z
	m_position = m_rightDirect * INITIAL_POSITION;

	m_objectsRight = m_rightDirect.y * 1.7320509f * SUNSET_TIME;
	if (m_objectsRight >= LIGHT_INTENSITY_UPPER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_UPPER_LIMIT;

	if (m_objectsRight <= LIGHT_INTENSITY_LOWER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_LOWER_LIMIT;


}

void Sun::Render()
{
	//�X�P�[�����O�A�ʒu�����A��]��������
}

void Sun::Finalize()
{
}
