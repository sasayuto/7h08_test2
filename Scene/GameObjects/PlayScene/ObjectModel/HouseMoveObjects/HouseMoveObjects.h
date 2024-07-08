#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"../Objects.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"

#include"IHouseMoveObjectsComponent.h"
class Player;
class HouseMoveObjectsManager;
struct Num {
	int ONE = 1;
	int TWO = 2;
	int THREE = 3;
	int FOUR = 4;
	int FIVE = 5;
	int SIX = 6;
	int SEVEN = 7;
	int EIGHT = 8;
	int NINE = 9;
	int TEN = 10;
	int ELEVEN = 11;
	int TWELVE = 12;
	int THIRTEEN = 13;
	int FOURTEEN = 14;
	int FIFTEEN = 15;
	int SIXTEEN = 16;
	int SEVENTEEN = 17;
	int EIGHTEEN = 18;
	int NINETEEN = 19;
	int TWENTY = 20;
	int TWENTY_ONE = 21;
	int TWENTY_TWO = 22;
	int TWENTY_THREE = 23;
	int TWENTY_FOUR = 24;
	int TWENTY_FIVE = 25;
	int TWENTY_SIX = 26;
	int TWENTY_SEVEN = 27;
	int TWENTY_EIGHT = 28;
	int TWENTY_NINE = 29;
	int THIRTY = 30;
	int THIRTY_ONE = 31;
	int THIRTY_TWO = 32;
	int THIRTY_THREE = 33;
	int THIRTY_FOUR = 34;
	int THIRTY_FIVE = 35;
	int THIRTY_SIX = 36;
	int THIRTY_SEVEN = 37;
	int THIRTY_EIGHT = 38;
	int THIRTY_NINE = 39;
	int FORTY = 40;
	int FORTY_ONE = 41;
	int FORTY_TWO = 42;
	int FORTY_THREE = 43;
	int FORTY_FOUR = 44;
	int FORTY_FIVE = 45;
	int FORTY_SIX = 46;
	int FORTY_SEVEN = 47;
	int FORTY_EIGHT = 48;
	int FORTY_NINE = 49;
	int FIFTY = 50;
	int FIFTY_ONE = 51;
	int FIFTY_TWO = 52;
	int FIFTY_THREE = 53;
	int FIFTY_FOUR = 54;
	int FIFTY_FIVE = 55;
	int FIFTY_SIX = 56;
	int FIFTY_SEVEN = 57;
	int FIFTY_EIGHT = 58;
	int FIFTY_NINE = 59;
	int SIXTY = 60;
	int SIXTY_ONE = 61;
	int SIXTY_TWO = 62;
	int SIXTY_THREE = 63;
	int SIXTY_FOUR = 64;
	int SIXTY_FIVE = 65;
	int SIXTY_SIX = 66;
	int SIXTY_SEVEN = 67;
	int SIXTY_EIGHT = 68;
	int SIXTY_NINE = 69;
	int SEVENTY = 70;
	int SEVENTY_ONE = 71;
	int SEVENTY_TWO = 72;
	int SEVENTY_THREE = 73;
	int SEVENTY_FOUR = 74;
	int SEVENTY_FIVE = 75;
	int SEVENTY_SIX = 76;
	int SEVENTY_SEVEN = 77;
	int SEVENTY_EIGHT = 78;
	int SEVENTY_NINE = 79;
	int EIGHTY = 80;
	int EIGHTY_ONE = 81;
	int EIGHTY_TWO = 82;
	int EIGHTY_THREE = 83;
	int EIGHTY_FOUR = 84;
	int EIGHTY_FIVE = 85;
	int EIGHTY_SIX = 86;
	int EIGHTY_SEVEN = 87;
	int EIGHTY_EIGHT = 88;
	int EIGHTY_NINE = 89;
	int NINETY = 90;
	int NINETY_ONE = 91;
	int NINETY_TWO = 92;
	int NINETY_THREE = 93;
	int NINETY_FOUR = 94;
	int NINETY_FIVE = 95;
	int NINETY_SIX = 96;
	int NINETY_SEVEN = 97;
	int NINETY_EIGHT = 98;
	int NINETY_NINE = 99;
	int HUNDRED = 100;
};

struct PartListObj
{
	std::vector<PartListObj> childrenParts;
	DirectX::Model* model;
	ID3D11ShaderResourceView* normalMap;
	std::unique_ptr<Collider::MultipleHitDetermination> col;
	std::unique_ptr<Collider::Sphere> colSphere;
};

/// <summary>
/// �I�u�W�F�N�g�̃N���X���`����
/// </summary>
class HouseMoveObjects
{
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	void SetRotateJson(const DirectX::SimpleMath::Vector3& rotate) {
		m_rotate = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(rotate.x),
			DirectX::XMConvertToRadians(rotate.y),
			DirectX::XMConvertToRadians(rotate.z)
		);	//GetRoughCollider()->SetPosition(GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.f, 5.f, -1.f), GetRotate()));

	}
	//���[���h�s��
	DirectX::SimpleMath::Matrix GetWorld()const { return m_world; };

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//��܂��ȓ����蔻��̃Q�b�^�[
	Collider::Sphere* GetRoughCollider() { return m_roughCollider.get(); }

	//���f���̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetModel() { return m_pPartModel; }
	void SetModel(DirectX::Model* supplyPointModel) { m_pPartModel = supplyPointModel; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	bool GetAllSurvivalFlag() const { return m_allSurvivalFlag; }

	std::vector<std::unique_ptr<IHouseMoveObjectsComponent>>& GetParts() { return m_parts; };

	static const float ANIMATION_TIME;//�������[�V�����̎���

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	HouseMoveObjects();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~HouseMoveObjects();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize(
		BulletManager* bulletManager, 
		HouseMoveObjectsManager* benchManager,
		std::vector<DirectX::SimpleMath::Vector3> ColiderPosition[],
		std::vector<DirectX::SimpleMath::Vector3> ColliderExtents[],
		std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate[]
	);

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render();
		
	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	virtual void RenderShadowTex();

	virtual void SetpositionRandam(const float& min, const float& max);

public:
	/// <summary>
	/// �p�[�c�𐶐�����
	/// </summary>
	/// <param name="Parts">�p�[�c�̃|�C���^</param>
	void AddParts(std::unique_ptr<IHouseMoveObjectsComponent> Parts) { m_parts.emplace_back(move(Parts)); }
	PartListObj m_PartList;
	Num m_nums;
	void CreateModelsFromCMONum(PartListObj& partsList, DirectX::Model* model, int& arrayNum,
		std::vector<DirectX::SimpleMath::Vector3> ColiderPosition,
		std::vector<DirectX::SimpleMath::Vector3> ColliderExtents,
		std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate,
		ID3D11ShaderResourceView* normalMap = nullptr
	);
	ID3D11ShaderResourceView* GetNormalMap() { return m_normalMap; };
	void SetNormalMap(ID3D11ShaderResourceView* normalMap) { m_normalMap = normalMap; };

private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//��]�N�I�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;

	//��܂��ȓ����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_roughCollider;

	BulletManager* m_pBulletManager;

	HouseMoveObjectsManager* m_pBenchManager;
	//����
	bool m_survival;

	//�o�ߎ���
	float m_timer;

	bool m_killCountFlag;

	//�S�Đ����Ă��邩
	bool m_allSurvivalFlag;

	//�v���y���̃��f��
	DirectX::Model* m_pPartModel;

	////�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IHouseMoveObjectsComponent>> m_parts;

	//normal�}�b�v�̃e�N�X�`��
	ID3D11ShaderResourceView* m_normalMap;
};
class HouseMove_03 :public HouseMoveObjects
{
public:
	static const int PART_NUM = 16;
	/// <summary>
/// �R���X�g���N�^
/// </summary>
	HouseMove_03();

	/// <summary>
/// ����������
/// </summary>
	void Initialize(BulletManager* bulletManager, HouseMoveObjectsManager* benchManager,
		std::vector<DirectX::SimpleMath::Vector3> ColiderPosition[],
		std::vector<DirectX::SimpleMath::Vector3> ColliderExtents[],
		std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate[])override;
	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

}; class HouseMove_02 :public HouseMoveObjects
{
public:
	static const int PART_NUM = 10;

	/// <summary>
/// �R���X�g���N�^
/// </summary>
	HouseMove_02();

	/// <summary>
/// ����������
/// </summary>
	void Initialize(BulletManager* bulletManager, HouseMoveObjectsManager* benchManager,
		std::vector<DirectX::SimpleMath::Vector3> ColiderPosition[],
		std::vector<DirectX::SimpleMath::Vector3> ColliderExtents[],
		std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate[])override;
		/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

}; class HouseMove_01 :public HouseMoveObjects
{
public:
	static const int PART_NUM = 7;

	/// <summary>
/// �R���X�g���N�^
/// </summary>
	HouseMove_01();

	/// <summary>
/// ����������
/// </summary>
	void Initialize(BulletManager* bulletManager, HouseMoveObjectsManager* benchManager,
		std::vector<DirectX::SimpleMath::Vector3> ColiderPosition[],
		std::vector<DirectX::SimpleMath::Vector3> ColliderExtents[],
		std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate[])override;
		/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

};