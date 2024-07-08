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
/// ���̃G�t�F�N�g�̃N���X���`����
/// </summary>
class SmokeEffect
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SmokeEffect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SmokeEffect();

	////������
	void Initialize();


	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">�t���[������</param>
	/// <param name="position">�`��ʒu</param>
	/// <param name="rotate">�`�撲���p�x</param>
	void Update(const float& elapsedTime, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& rotate
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