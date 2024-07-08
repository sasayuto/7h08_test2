//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ���j���[�N���X
//
//-------------------------------------------------------------------------------------

#pragma once

#include "ImaseLib/ParticleUtility.h"
#include "ImaseLib/Particle.h"
#include <random>

/// <summary>
/// ����G�t�F�N�g�̃N���X���`
/// </summary>
class LightEffect
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	LightEffect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LightEffect();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();


	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	/// <param name="position">�`��ʒu</param>
	void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position
	);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

private:
	//�p�[�e�B�N���̃|�C���^
	std::unique_ptr<Particle> m_particle;

	//�`��N�[���^�C��
	float m_timer;
};
