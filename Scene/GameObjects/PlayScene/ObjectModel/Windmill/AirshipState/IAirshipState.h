#pragma once
#include "StepTimer.h"

// IState�C���^�[�t�F�C�X���`���� 
class IStateAirship
{
public:
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="elapsedTime">�t���[������</param>
	virtual void Update(const float& elapsedTime) = 0;

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// ��n��������
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual ~IStateAirship() = default;
};
