#pragma once
#include"Respawn.h"
struct IPlayerComponent;


/// <summary>
/// ���X�|�[���n�_�̊Ǘ��҂̃N���X���`����
/// </summary>
class RespawnManager
{
public:
	//���X�|�[���̈ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetRespawnPosition() const{ return m_respawnPosition; }
	void SetRespawnPosition(const DirectX::SimpleMath::Vector3& respawnPosition) { m_respawnPosition = respawnPosition; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	RespawnManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~RespawnManager();

	//����������
	void Intialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �v���C���[�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	void CheckHitCharacter(Player* player);

private:
	//���X�|�[���n�_�̃|�C���^
	std::vector<std::unique_ptr<Item>> m_RespawnList;

	//���X�|�[���n�_�̃Z�b�g�|�W�V����
	DirectX::SimpleMath::Vector3 m_respawnPosition;
};