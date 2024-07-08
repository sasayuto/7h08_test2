//--------------------------------------------------------------------------------------
// File: ParticleUtil.cpp
//
// �p�[�e�B�N�����[�e�B���e�B�N���X
// position�⑬�x�Ȃǃp�[�e�B�N���P�ɕK�v�ȗv�f���i�[
//
//-------------------------------------------------------------------------------------
#include "pch.h"
#include "Particleutility.h"


using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// �����͏����ݒ�p�̐��l
/// </summary>
/// <param name="life">��������</param>
/// <param name="pos">���W</param>
/// <param name="velocity">���x</param>
/// <param name="accele">�����x</param>
/// <param name="startScale">�����T�C�Y</param>
/// <param name="endScale">�ŏI�T�C�Y</param>
/// <param name="startColor">�����F</param>
/// <param name="endColor">�ŏI�F</param>
ParticleUtility::ParticleUtility(
	float life,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 velocity,
	DirectX::SimpleMath::Vector3 accele,
	DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
	DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor,
	DirectX::SimpleMath::Vector3 rotateSpeed
)
{
	m_startLife =
		m_life = life;

	m_position = pos;
	m_velocity = velocity;
	m_accele = accele;

	m_startScale =
		m_nowScale = startScale;
	m_endScale = endScale;

	m_startColor =
		m_nowColor = startColor;
	m_endColor = endColor;

	m_rotateSpeed = rotateSpeed;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
ParticleUtility::~ParticleUtility()
{
}
/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">Game������StepTimer���󂯎��</param>
/// <returns>��������(life)������Ԃ�true</returns>
bool ParticleUtility::Update(float elapsedTime)
{
	// �X�P�[��
	m_nowScale = SimpleMath::Vector3::Lerp(m_startScale, m_endScale, 1.0f - m_life / m_startLife);
	// �F
	m_nowColor = SimpleMath::Color::Lerp(m_startColor, m_endColor, 1.0f - m_life / m_startLife);
	// ���x�̌v�Z
	m_velocity += m_accele * elapsedTime;
	// ���W�̌v�Z
	m_position += m_velocity * elapsedTime;
	m_life -= elapsedTime;
	// ���C�t���O�Ŏ��g�������Ă��炤
	if (m_life < 0.0f)
	{
		return false;
	}

	return true;
}

void ParticleUtility::RotateUpdate()
{
	SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, m_life * m_rotateSpeed.x);
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, m_life * m_rotateSpeed.y);
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, m_life * m_rotateSpeed.z);
	m_position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, 1), q);
}


