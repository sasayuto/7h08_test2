//--------------------------------------------------------------------------------------
// File: Gaueg.h
//
// ���j���[�N���X
//
//-------------------------------------------------------------------------------------

#pragma once

#include "ImaseLib/ParticleUtility.h"
#include "ImaseLib/ParticleSandstorm.h"
#include <random>
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
class BenchManager;
class StreetLightManager;
/// <summary>
/// ���̃G�t�F�N�g�̃N���X���`����
/// </summary>
class SandstormEffect
{
public:

	static const float SPEED;
	static const float COLLIDER_ADJUSTMENT;
	static const int SANDSTORM_OFFENSIVE_POWER = 200;
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }


	//��܂��ȓ����蔻��̃Q�b�^�[
	Collider::Box* GetCollider() { return m_colloder.get(); }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SandstormEffect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SandstormEffect();

	////������
	void Initialize(BenchManager* benchManager, StreetLightManager* streetLightManager);


	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">�t���[������</param>
	/// <param name="position">�`��ʒu</param>
	/// <param name="rotate">�`�撲���p�x</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	void SetpositionRandam(const float& min, const float& max);

private:
	//�p�[�e�B�N���̃|�C���^
	std::unique_ptr<ParticleSandstorm> m_particle;

	//�p�[�e�B�N���̃|�C���^
	std::unique_ptr<Collider::Box> m_colloder;

	DirectX::SimpleMath::Vector3 m_position;

	//�`��N�[���^�C��
	float m_timer;

	bool m_survival;

	BenchManager* m_pBenchManager;

	StreetLightManager* m_pStreetLightManager;
};
