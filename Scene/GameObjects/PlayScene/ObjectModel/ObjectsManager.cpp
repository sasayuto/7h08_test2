#include"pch.h"
#include"ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/Enemy.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"

//�I�u�W�F�N�g���
#include"House.h"
#include"Objects/Houses/House_02.h"
#include"Objects/Houses/House_03.h"
#include"Objects/StoneStairs/StoneStairs.h"
#include"Objects/Walls/BigBrickWall/BigBrickWall.h"
using namespace DirectX;


ObjectsManager::ObjectsManager() 
{	
}

//�R���X�g���N�^�ƌĂ΂��֐�
ObjectsManager::~ObjectsManager()
{

}

//�Q�[���̏��������s���֐�
void ObjectsManager::Intialize()
{
	std::ifstream obj("Resources/json/TwonScene/Json_TwonObjects.Json");
	Json::CharReaderBuilder reader;
	Json::Value root;

	// �t�@�C�����J����Ă��邩���m�F���܂��B
	if (obj.is_open()) {
		std::string errors;

		// �t�@�C������JSON���p�[�X���܂��B
		if (Json::parseFromStream(reader, obj, &root, &errors))
		{
			// JSON�� "house" �����݂��A�z��ł��邩�ǂ������m�F���܂��B
			if (root.isMember("objects") && root["objects"].isArray())
			{
				// "house" �z����擾���܂��B
				const Json::Value& stoneStairsArray = root["objects"][0]["stoneStairs"];

				// "house" �z����̊e�v�f�ɑ΂��ă��[�v�����s���܂��B
				for (unsigned i = 0; i < stoneStairsArray.size(); i++)
				{
					// �V�����I�u�W�F�N�g���쐬���A�ʒu�Ɖ�]��ݒ肵�܂��B
					std::unique_ptr<Objects> stoneStairs = std::make_unique<StoneStairs>();
					stoneStairs->SetPosition(SimpleMath::Vector3(
						stoneStairsArray[i]["position"][0].asFloat(),
						stoneStairsArray[i]["position"][1].asFloat(),
						stoneStairsArray[i]["position"][2].asFloat()
					));
					stoneStairs->SetRotateJson(SimpleMath::Vector3(
						stoneStairsArray[i]["rotate"][0].asFloat(),
						stoneStairsArray[i]["rotate"][1].asFloat(),
						stoneStairsArray[i]["rotate"][2].asFloat()
					));
					// ���X�g�ɃI�u�W�F�N�g��ǉ����܂��B
					m_objectsList.push_back(std::move(stoneStairs));

				}
			}
			else {
				std::cerr << "JSON�� 'house' �f�[�^���܂܂�Ă��܂���B" << std::endl;
			}
		}
		else {
			std::cerr << "JSON�̃p�[�X�G���[: " << errors << std::endl;
		}
		obj.close();
	}
	else {
		std::cerr << "JSON�t�@�C�����J���ۂɃG���[���������܂����B" << std::endl;
	}

	// �I�u�W�F�N�g�����������܂��B
	for (int i = 0; i < m_objectsList.size(); i++) {
		m_objectsList[i]->Initialize();
	}
}

void ObjectsManager::CollJson(const Json::Value& ary, Objects* objects)
{
	// �����蔻����m�F�������Ƃ��Ɏg�����
	std::ofstream outputfile("Resources/ColliderDate/ColDateHouse_03.txt");
	for (unsigned j = 0; j < ary["Colliders"].size(); j++) {
		const Json::Value& nowcol = ary["Colliders"][j];
		DirectX::SimpleMath::Vector3 pos = SimpleMath::Vector3::Transform(SimpleMath::Vector3(
			nowcol["Pos"][0].asFloat(),
			nowcol["Pos"][1].asFloat(),
			nowcol["Pos"][2].asFloat()),objects->GetRotate());
		if (nowcol.isMember("OOMA") && nowcol["OOMA"].isArray())
		{
			float Rud = nowcol["Ees"][0].asFloat();
			objects->GetRoughCollider()->SetPosition(objects->GetPosition() + pos);
			objects->GetRoughCollider()->SetRadius(Rud);
			std::ostringstream oss;
			oss << "GetRoughCollider()->SetPosition(GetPosition()+DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(" << pos.x << "f, " << pos.y << "f, " << pos.z << "f),GetRotate()));" << std::endl;
			oss << "GetRoughCollider()->SetRadius(" << Rud << "f);" << std::endl;
			outputfile << oss.str() << std::endl << std::endl;
		}

		if (nowcol.isMember("S") && nowcol["S"].isArray()) {
			float Rud = objects->GetObjectsModel()->meshes[0]->boundingSphere.Radius + nowcol["Ees"][0].asFloat();
			objects->GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateSphereCollider(objects->GetPosition(), pos, Rud));
			std::ostringstream oss;
			oss << "GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateSphereCollider(" << std::endl;
			oss << "GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(" << pos.x << "f, " << pos.y << "f, " << pos.z << "f),GetRotate())," << std::endl;
			oss << Rud << "f));" << std::endl;
			outputfile << oss.str() << std::endl << std::endl;
		}

		if (nowcol.isMember("O") && nowcol["O"].isArray() || nowcol.isMember("B") && nowcol["B"].isArray()) {

			DirectX::SimpleMath::Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				DirectX::XMConvertToRadians(nowcol["Rot"][0].asFloat()),
				DirectX::XMConvertToRadians(nowcol["Rot"][1].asFloat()),
				DirectX::XMConvertToRadians(nowcol["Rot"][2].asFloat()));

			DirectX::SimpleMath::Vector3 Eex =SimpleMath::Vector3(
				nowcol["Ees"][0].asFloat(),
				nowcol["Ees"][1].asFloat(),
				nowcol["Ees"][2].asFloat());
			//�����蔻������
			objects->GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(objects->GetPosition(), objects->GetRotate(), pos, rot, Eex));
			std::ostringstream oss;
			if (nowcol.isMember("O") && nowcol["O"].isArray()) {
				oss << "GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(" << std::endl;
				oss << "GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(" << pos.x << "f, " << pos.y << "f, " << pos.z << "f),GetRotate())," << std::endl;
				oss << "DirectX::SimpleMath::Quaternion(" << rot.x << "f," << rot.y << "f," << rot.z << "f," << rot.w << "f)*GetRotate()," << std::endl;;
				oss << "DirectX::SimpleMath::Vector3(" << Eex.x << "f," << Eex.y << "f," << Eex.z << "f)));" << std::endl;;
			}
			if (nowcol.isMember("B") && nowcol["B"].isArray()) {
				oss << "GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(" << std::endl;
				oss << "GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(" << pos.x << "f, " << pos.y << "f, " << pos.z << "f),GetRotate())," << std::endl;
				oss << "DirectX::SimpleMath::Vector3(" << Eex.x << "f," << Eex.y << "f," << Eex.z << "f)));" << std::endl;;
			}
			outputfile << oss.str() << std::endl << std::endl;

		}

	}
}

//�Q�[���̍X�V���s���֐�
void ObjectsManager::Update()
{
	//m_objectsList.clear();
	//Intialize();

	//���̍X�V
	for (int i = 0; i < m_objectsList.size(); i++)
	{		
		//�I�u�W�F�N�g�̍X�V
		m_objectsList[i]->Update();
	}
}

//�Q�[���̍X�V�������s���֐�
void ObjectsManager::Render()
{
	//���̕`��
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->DistanceRange(m_objectsList[i]->GetPosition()))
			continue;

		//�I�u�W�F�N�g�̕`��
		m_objectsList[i]->Render();
	}
}

void ObjectsManager::RenderShadowTex()
{
	//���̕`��
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//���E�ɓ����Ă��邩
		if (Draw::GetInstance()->DistanceRange(m_objectsList[i]->GetPosition()))
			continue;

		//�I�u�W�F�N�g�̕`��
		m_objectsList[i]->RenderShadowTex();
	}
}

//�Q�[���̏I���������s���֐��B����������K�v�ȏꍇ�@�iRelease�֐��Ȃǂ��Ăяo���j�́A���̊֐����ł���邷��
void ObjectsManager::Finalize()
{
	//�㏈��
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		m_objectsList[i].reset();
	}
}

void ObjectsManager::CheckHitCharacter(Player* player)
{
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//��܂��ȃv���C���[�Ƃ̓����蔻��
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(player->GetCollider()))
			continue;

		//�v���C���[�Ƃ̓����蔻��
		if (!m_objectsList[i]->GetCollider()->CheckHitOneOrMore(player->GetCollider()))
			continue;

		for (auto& playerParts : player->GetParts())
		{
			//�p�[�c�Ƃ̓����蔻��
			if (!playerParts->CollisionObjects(m_objectsList[i].get()))
				continue;

			player->Damage(player->GetHP());
			//�����y���̂��߁i�������Ă�����I���j
			return;
		}
	}
}

void ObjectsManager::CheckHitEnemy(Enemy* enemy)
{
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//��܂��ȃv���C���[�Ƃ̓����蔻��
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(enemy->GetCollider()))
			continue;

		//�v���C���[�Ƃ̓����蔻��
		if (!m_objectsList[i]->GetCollider()->CheckHitOneOrMore(enemy->GetCollider()))
			continue;

		for (auto& enemyParts : enemy->GetParts())
		{
			//�p�[�c�Ƃ̓����蔻��
			if (!enemyParts->CollisionObjects(m_objectsList[i].get()))
				continue;

			enemy->Damage(enemy->GetHP());
			//�����y���̂��߁i�������Ă�����I���j
			return;
		}
		return;
	}
}
void ObjectsManager::CheckHitAirship(Airship* airship)
{
	for (int i = 0; i < m_objectsList.size(); i++)
	{
		//��܂��ȃv���C���[�Ƃ̓����蔻��
		if (!m_objectsList[i]->GetRoughCollider()->CheckHitSphere(airship->GetCollider()))
			continue;

		//�v���C���[�Ƃ̓����蔻��
		if (!m_objectsList[i]->GetCollider()->CheckHitOneOrMore(airship->GetCollider()))
			continue;

		for (auto& airshipParts : airship->GetParts())
		{
			if (!airshipParts->Collision(m_objectsList[i].get()))
				continue;

			//�����y���̂��߁i�������Ă�����I���j
			return;
		}
		return;
	}
}
