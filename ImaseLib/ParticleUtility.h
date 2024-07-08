//--------------------------------------------------------------------------------------
// File: ParticleUtil.h
//
// �p�[�e�B�N�����[�e�B���e�B�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
class ParticleUtility
{
	//�ϐ�
private:


	//�֐�
private:
	//���W
	DirectX::SimpleMath::Vector3 m_position;

	//���x
	DirectX::SimpleMath::Vector3 m_velocity;

	//�����x
	DirectX::SimpleMath::Vector3 m_accele;

	//��]
	DirectX::SimpleMath::Vector3 m_rotateSpeed;

	//�X�P�[��
	DirectX::SimpleMath::Vector3 m_nowScale;
	DirectX::SimpleMath::Vector3 m_startScale;
	DirectX::SimpleMath::Vector3 m_endScale;

	//��������
	float m_life;
	float m_startLife;

	//�J���[
	DirectX::SimpleMath::Color m_nowColor;
	DirectX::SimpleMath::Color m_startColor;
	DirectX::SimpleMath::Color m_endColor;

	//�֐�
public:
	//�R���X�g���N�^�i�����ݒ�j
	ParticleUtility(
		float life,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 velocity,
		DirectX::SimpleMath::Vector3 accele,
		DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor,
		DirectX::SimpleMath::Vector3 rotateSpeed = DirectX::SimpleMath::Vector3::Zero
	);
	//�f�X�g���N�^
	~ParticleUtility();

	// �X�V
	bool Update(float elapsedTime);

	// �X�V
	void RotateUpdate();

	//getter
	DirectX::SimpleMath::Vector3 GetPosition()const { return m_position; }

	DirectX::SimpleMath::Vector3 GetVelocity()const { return m_velocity; }

	DirectX::SimpleMath::Vector3 GetAccele() const { return m_accele; }

	DirectX::SimpleMath::Vector3 GetNowScale() const { return m_nowScale; }
	DirectX::SimpleMath::Vector3 GetStartScale() const { return m_startScale; }
	DirectX::SimpleMath::Vector3 GetEndScale()const { return m_endScale; }

	float GetLife() const { return m_life; }
	float GetStartLife() const { return m_startLife; }
	DirectX::SimpleMath::Color GetNowColor()const { return m_nowColor; }
	DirectX::SimpleMath::Color GetStartColor() const { return m_startColor; }
	DirectX::SimpleMath::Color GetEndColor()const { return m_endColor; }



};

