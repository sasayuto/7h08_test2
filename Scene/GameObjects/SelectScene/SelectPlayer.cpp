#include "pch.h"
#include"SelectPlayer.h"
#include <math.h>

#include"Scene/GameObjects/PlayScene/Character/Player/PlayerPartFactory.h"
//#include"Scene/GameObjects/PlayScene/MiniMap/GetPosotion/GetPosition.h"
//#include"Scene/GameObjects/PlayScene/Character/Airship/AirshipManager.h"
//#include"Scene/GameObjects/PlayScene/ObjectModel/Windmill/WindmillManager.h"
//#include"Scene/GameObjects/PlayScene/ObjectModel/Objects/Walls/BigBrickWall/BigBrickWallManager.h"
//#include"Scene/GameObjects/PlayScene/Sandstorm/SandstormManager.h"
//#include"Scene/GameObjects/PlayScene/Character/Turret/TurretManager.h"
#include"Scene/GameObjects/PlayScene/Effect/PlayerEffect.h"

using namespace DirectX;

const float  SelectPlayer::PLAYER_BEND_ACCELERATION(30.0f);
const int SelectPlayer::PLAYER_MAX_HP(2000);							//�v���C���[��HP	

SelectPlayer::SelectPlayer() :
	m_cameraRotate(SimpleMath::Quaternion::Identity),
	m_AnimetionRotate(),
	m_TiltAnimation(0.0f),
	m_playerEffect(nullptr),
	m_position(SimpleMath::Vector3(0,1,0)),
	m_velcity(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_bulletCoolTime(),
	m_HP(PLAYER_MAX_HP),
	m_fuel(PLAYER_MAX_FUEL),
	m_offensivePower(PLAYER_OFFENSIVE_POWER),
	m_speed(),
	m_angle(SimpleMath::Vector3::Zero),
	m_bulletType(Bullet::BulletType::None),
	m_pBulletManager(nullptr),
	m_gravity(){
}

SelectPlayer::~SelectPlayer()
{
}

void SelectPlayer::Initialize(BulletManager* bulletManager)
{
	//�Q�[�W�ƃx�[�X��`�悷��
	for (int i = 0; i < 2; i++)
	{
		//�Q�[�W�̂̃��X�|�[���̃C���X�^���X�𐶐�����
		m_HorizontalTriangle[i] = std::make_unique<tito::MoveUserInterface>();
		m_HorizontalTrianglecol[i] = std::make_unique<Collider::Box2D>();

	}
	//�K�v�ȏ����Z�b�g����
	m_HorizontalTriangle[0]->Create(
		L"Resources/Textures/HorizontalTrianglel.png"
		, DirectX::SimpleMath::Vector2(-1120, 0)
		, DirectX::SimpleMath::Vector2::One
		, tito::ANCHOR::MIDDLE_RIGHT
		, tito::POSITION_ANCHOR::MIDDLE_RIGHT
	);
	//�K�v�ȏ����Z�b�g����
	m_HorizontalTriangle[1]->Create(
		L"Resources/Textures/HorizontalTriangle.png"
		, DirectX::SimpleMath::Vector2(-90, 0)
		, DirectX::SimpleMath::Vector2::One
		, tito::ANCHOR::MIDDLE_RIGHT
		, tito::POSITION_ANCHOR::MIDDLE_RIGHT
	);

	for (int i = 0; i < 2; i++)
	{
		//�����蔻��̏�����
		//�ʒu�A�T�C�Y���C�������l��n��
		m_HorizontalTrianglecol[i]->Initialize(
			m_HorizontalTriangle[i]->TexPositionCalculation(),
			m_HorizontalTriangle[i]->TexSizeCalculation()
		);
	}

	//������]
	m_angle.y = 15.0f;
	m_velcity.y = 15.0f;

	//���̃A�h���X
	m_pBulletManager = bulletManager;

	m_playerEffect = std::make_unique<PlayerEffect>();
	m_playerEffect->Initialize();
	//�����蔻��𐶐�
	m_collider = std::make_unique<Collider::Sphere>();

	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	m_collider->SetPosition(m_position);

	m_collider->SetRadius(1.3f);

	//���Z�b�g�̌�ɏ����i�ʒu��p�x���������邩��j
	// �v���C���[�Ƀv���y����ǉ�����
	AddParts(PlayerPartFactory::CreatePlayerBody(nullptr, GetPosition(), GetRotate()));

	for (auto& parts : m_parts)
	{
		// �p�[�c��������
		parts->Initialize(DirectX::SimpleMath::Vector3::Zero);
	}

}

void SelectPlayer::Update(const float& elapsedTime, const bool& decisionFlag, const bool& returnDecisionFlag)
{
	//�����蔻��Ɉʒu�Ɣ��a���Z�b�g
	m_collider->SetPosition(m_position);

	//���肵�Ă���O�i
	if (decisionFlag)
	{
		if (!returnDecisionFlag)
		{
			m_speed += 0.5f / 60.0f;
			//�j�󂳂������ɔ�΂�
			m_position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, -m_speed), m_rotate);


			for (auto& parts : m_parts)
			{
				// �p�[�c���X�V����
				parts->Speed();
			}
			m_playerEffect->Update(elapsedTime, m_position, m_rotate, m_HP);
		}
	}

	//���肵�ĂȂ������獶�E�I���\
	if (!decisionFlag)
	{
		//�O�̃V�[���ɖ߂�Ƃ��ɂ���߂�
		if (!returnDecisionFlag)
		{
			auto mouseTr = KeyboardTracker::GetInstance()->GetMouseTracker();
			auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

			if (m_HorizontalTrianglecol[0]->CheckHitPoint(mouse.x, mouse.y))
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
					m_angle.y += SelectPlayer::PLAYER_BEND_ACCELERATION;
			if (m_HorizontalTrianglecol[1]->CheckHitPoint(mouse.x, mouse.y))
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
					m_angle.y -= SelectPlayer::PLAYER_BEND_ACCELERATION; 

		}
	}

	//�p�x�ɍ�����������
	m_velcity.y = ((m_angle.y - m_velcity.y) * 0.10f) + m_velcity.y;

	//�N�I�[�^�j�I����]�����
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(m_velcity.y));

	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->Update(GetPosition(), GetRotate());
	}

}

void SelectPlayer::Render()
{	
	m_playerEffect->Render();
	for (auto& part : m_parts)
	{
		//�p�[�c���X�V����
		part->Render();
	}

}

void SelectPlayer::Finalize()
{
}

void SelectPlayer::ShadowMapRender()
{
	for (auto& part : m_parts)
	{
		//�p�[�c���X�V����
		part->RenderShadowTex();
	}

}

void SelectPlayer::PartsInitialize()
{
	for (auto& parts : m_parts)
	{
		// �p�[�c��������
		parts->Initialize(DirectX::SimpleMath::Vector3::Zero);
	}
}

void SelectPlayer::PartsUpdate()
{
}

void SelectPlayer::PartsExplosion()
{
	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->Explosion();
	}
}

void SelectPlayer::PartsMotion()
{
	for (auto& parts : m_parts)
	{
		// �p�[�c���X�V����
		parts->Speed();
	}
}

void SelectPlayer::PartsRender()
{
	for (auto& part : m_parts)
	{
		//�p�[�c���X�V����
		part->Render();
	}

}
