#pragma once
#include"HouseMoveObjects.h"

class Enemy;
class Player;
class Airship;
class BulletManager;
class SandstormEffect;

/// <summary>
/// �I�u�W�F�N�g�̊Ǘ��҂̃N���X���`����
/// </summary>
class HouseMoveObjectsManager
{
public:
	//�L���J�E���g
	int GetBenchKillCount() { return m_benchKillCount; }
	void SetBenchKillCount(int benchKillCount) { m_benchKillCount = benchKillCount; }

	//�q�̃p�[�c�𐶐�
	void AddMoveObjects(std::unique_ptr<HouseMoveObjects> moveObjects)  { m_HouseMoveObjectsManager.push_back(std::move(moveObjects)); }

	//�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<HouseMoveObjects>>& GetHouseMoveObjectsManager() { return m_HouseMoveObjectsManager; };

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="mapLoader">�}�b�v�̃A�h���X</param>
	HouseMoveObjectsManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~HouseMoveObjectsManager();

	/// <summary>
	/// ����������
	/// </summary>
	template<typename TTT>
	void Intialize(BulletManager* bulletManager, std::string failName)
	{
		std::vector<DirectX::SimpleMath::Vector3> ColliderPosition[TTT::PART_NUM];
		std::vector<DirectX::SimpleMath::Vector3> ColliderExtents[TTT::PART_NUM];
		std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate[TTT::PART_NUM];

		std::ifstream obj(failName);

		Json::CharReaderBuilder reader;
		Json::Value root;
		if (obj.is_open()) {
			std::string errors;
			// �t�@�C������JSON���p�[�X���܂��B
			if (Json::parseFromStream(reader, obj, &root, &errors))
			{
				if (root.isMember("ColliderDate") && root["ColliderDate"].isArray())
				{
					for (size_t i = 0; i < TTT::PART_NUM; i++)
					{
						std::string numberString = std::to_string(i + 1);
						// �ꌅ�̏ꍇ�͐����̑O��0��ǉ�
						if (numberString.length() == 1) numberString = "0" + numberString;
						// �t�@�C�����J����Ă��邩���m�F���܂��B
								// JSON�� "ColliderDate" �����݂��A�z��ł��邩�ǂ������m�F���܂��B
							// "ColliderDate" �z����擾���܂��B
						const Json::Value& Array = root["ColliderDate"][0][numberString][0];

						// JSON�� "ColliderDate" �����݂��A�z��ł��邩�ǂ������m�F���܂��B
						if (Array.isMember("Obb") && Array["Obb"].isArray())
						{

							// "ColliderDate" �z����̊e�v�f�ɑ΂��ă��[�v�����s���܂��B
							for (auto& houseData : Array["Obb"]) {

								ColliderPosition[i].push_back(
									DirectX::SimpleMath::Vector3(
										houseData["position"][0].asFloat(),
										houseData["position"][1].asFloat(),
										houseData["position"][2].asFloat()
									)
								);

								ColliderExtents[i].push_back(
									DirectX::SimpleMath::Vector3(
									houseData["extents"][0].asFloat(),
									houseData["extents"][1].asFloat(),
									houseData["extents"][2].asFloat()
								)
								);

								ColliderRotate[i].push_back(
									DirectX::SimpleMath::Quaternion(
										houseData["rotate"][0].asFloat(),
										houseData["rotate"][1].asFloat(),
										houseData["rotate"][2].asFloat(),
										houseData["rotate"][3].asFloat()
									)
								);

							}
						}
					}
				}
				if (root.isMember("Posture") && root["Posture"].isArray())
				{
					for (auto& houseData : root["Posture"]) {
						{						//float����Vector3�ɕϊ�
							std::unique_ptr<HouseMoveObjects> windmill = std::make_unique<TTT>();

							windmill->SetPosition(
								DirectX::SimpleMath::Vector3(houseData["position"][0].asFloat(),
									houseData["position"][1].asFloat(),
									houseData["position"][2].asFloat()
								));

							windmill->SetRotateJson(
								DirectX::SimpleMath::Vector3(houseData["rotate"][0].asFloat(),
									houseData["rotate"][1].asFloat(),
									houseData["rotate"][2].asFloat()
								));

							AddMoveObjects(std::move(windmill));
						}

					}
				}
			}
		}

		m_pBulletManager = bulletManager;

		for (int i = 0; i < m_HouseMoveObjectsManager.size(); i++)
		{
			//����������
			m_HouseMoveObjectsManager[i]->Initialize(bulletManager, this, ColliderPosition, ColliderExtents, ColliderRotate);
		}

	}

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	void RenderShadowTex(const bool flag);


	/// <summary>
	/// ��n��
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// �v���C���[�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	void CheckHitCharacter(Player* player);

	/// <summary>
	/// �v���C���[�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	void CheckHitEnemy(Enemy* enemy);
	
	/// <summary>
	/// ��s�D�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="character">�G�̃A�h���X</param>
	virtual void CheckHitAirship(Airship* airship);

	/// <summary>
	/// ��s�D�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="character">�G�̃A�h���X</param>
	void CheckHitSandstorm(SandstormEffect* sandstormEffect);

private:
	//�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<HouseMoveObjects>> m_breakObjectsManager;

	//�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<HouseMoveObjects>> m_HouseMoveObjectsManager;

	BulletManager* m_pBulletManager;

	//�L���J�E���g
	int m_benchKillCount;
};

