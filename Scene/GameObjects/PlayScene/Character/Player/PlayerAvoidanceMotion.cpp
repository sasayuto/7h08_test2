#include "pch.h"
#include"PlayerAvoidanceMotion.h"
#include <math.h>
using namespace DirectX;
const float AVOIDANCE_SPEED_RESISTANCE(0.1f / 60);

PlayerAvoidanceMotion::PlayerAvoidanceMotion(
	Player* motions,
	RespawnManager* respawnManager,
	SupplyPointManager* supplyPointManager,
	CoinManager* coinManager
) :
	m_pPlayer(motions),
	m_pRespawnManager(respawnManager),
	m_pSupplyPointManager(supplyPointManager),
	m_pCoinManager(coinManager)
{
}

PlayerAvoidanceMotion::~PlayerAvoidanceMotion()
{

}

void PlayerAvoidanceMotion::Initialize()
{
	////���X�|�[���n�_�Ɉʒu���Z�b�g
	//m_pPlayer->SetPosition(m_pRespawnManager->GetRespawnPosition());

	//�v���C���[�̏�Ԃɂ���Ĕ��a���ς��̂ŃZ�b�g
	m_pPlayer->GetCollider()->SetRadius(1.3f);
	//��]���Z�b�g
	m_pPlayer->SetAnimetionRotate(m_pPlayer->GetRotate());
}

void PlayerAvoidanceMotion::Update(const float& elapsedTime)
{
	elapsedTime;
	auto mouse = Mouse::Get().GetState();

	//WASD�ŕ��������߂�
	Motion(elapsedTime);

	m_pPlayer->GetBloodEffect()->Update(m_pPlayer->GetHP());

	//����
	float bulletCoolTime = m_pPlayer->GetBulletCoolTime();

	//���̃N�[���^�C��
	if (bulletCoolTime > 0.0f)
		bulletCoolTime -= elapsedTime;
	else
		bulletCoolTime = 0.0f;

	m_pPlayer->SetBulletCoolTime(bulletCoolTime);

	//�E�N���ŋ�����
	if (mouse.leftButton)
		m_pPlayer->DoubleShot(Player::BULLET_COOL_TIME);

	//hp���Ȃ��Ȃ�����L���̓���
	if (m_pPlayer->GetHP() <= 0)
	{
		m_pPlayer->SetIState(m_pPlayer->GetKillMotion());
	}

	//hp���Ȃ��Ȃ�����L���̓���
	if (m_pPlayer->GetFuel() <= 0)
	{
		m_pPlayer->SetIState(m_pPlayer->GetKillMotion());
	}

	//�p�[�c�̍X�V
	m_pPlayer->PartsUpdate();

	if (m_pRespawnManager)
		//���X�|�[���̏Փˏ���
		m_pRespawnManager->CheckHitCharacter(m_pPlayer);

	if (m_pSupplyPointManager)
		//�A�C�e���̏Փˏ���
		m_pSupplyPointManager->CheckHitCharacter(m_pPlayer);

	if (m_pCoinManager)
		//�R�C���̏Փˏ���
		m_pCoinManager->CheckHitCharacter(m_pPlayer);
}

void PlayerAvoidanceMotion::Render()
{

	m_pPlayer->PartsRender();
	m_pPlayer->GetPlayerEffect()->Render();
	m_pPlayer->GetBloodEffect()->Render();
}

void PlayerAvoidanceMotion::Finalize()
{
}

void PlayerAvoidanceMotion::Motion(const float& elapsedTime)
{
	elapsedTime;
	auto keystate = KeyboardSingleton::GetInstance()->GetKeyboardState();

	//���x���Q�b�g
	SimpleMath::Vector3 playerVelcity = m_pPlayer->GetVelcity();
	//�p�x���Q�b�g
	SimpleMath::Vector3 playerAngle = m_pPlayer->GetAngle();
	//�ʒu���Q�b�g
	SimpleMath::Vector3 position = m_pPlayer->GetPosition();
	SimpleMath::Vector3 previousposition = position;
	//�d�͂��Q�b�g
	float gravity = m_pPlayer->GetGravity();
	//�X�s�[�h���Q�b�g
	float speed = m_pPlayer->GetSpeed();

	//�����_���v���X��������������
	m_pPlayer->SetTiltAnimation(
		m_pPlayer->GetTiltAnimation() +
		((DirectX::XMConvertToRadians(725)) - m_pPlayer->GetTiltAnimation()) *
		0.01f
	);

	//�v���C���[�̃X�s�[�h�̉����x�v�Z
	speed += Player::PLAYER_ACCELERATION;

	//�N�I�[�^�j�I����]�����
	SimpleMath::Quaternion p;
	p = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, m_pPlayer->GetTiltAnimation()
	);

	//spase���������猸�����v���y���~�܂�

	//�X�s�[�h���
	if (speed >= Player::PLAYER_MAX_SPEED)	speed = Player::PLAYER_MAX_SPEED;

	//�X�s�[�h�����������痎��
	if (speed <= Player::PLAYER_STRAT_FALLING_SPEED)	gravity += Player::PLAYER_FALL_SPEED__ACCELERATION;

	//�����X�s�[�h�̃}�b�N�X
	if (gravity >= Player::PLAYER_FALL_SPEED_MAX)	gravity = Player::PLAYER_FALL_SPEED_MAX;

	float ss = 1 - m_pPlayer->GetTiltAnimation() / DirectX::XMConvertToRadians(720);

	//�j�󂳂������ɔ�΂�
	position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(1.f*ss, 0, -speed), m_pPlayer->GetAnimetionRotate());

	if (m_pPlayer->GetTiltAnimation() >= DirectX::XMConvertToRadians(720))
	{
		m_pPlayer->SetIState(m_pPlayer->GetMotion());
	}

	//���W�ɏd�͂�����
	position.y -= m_pPlayer->GetGravity();

	//�d�͂��Z�b�g
	m_pPlayer->SetGravity(gravity);

	//���x���Z�b�g
	m_pPlayer->SetVelcity(playerVelcity);

	//�p�x���Z�b�g
	m_pPlayer->SetAngle(playerAngle);

	//�X�s�[�h���Z�b�g
	m_pPlayer->SetSpeed(speed);

	//�J�����̉�]���Z�b�g
	m_pPlayer->SetRotate(p * m_pPlayer->GetAnimetionRotate()
	);

	//�J�����̉�]���Z�b�g
	m_pPlayer->SetCameraRotate(m_pPlayer->GetCameraRotate());

	//�ʒu���Z�b�g
	m_pPlayer->SetPosition(position);
	//�i�s�x�N�g��
	DirectX::SimpleMath::Vector3 reflectionVector = position - previousposition;
	reflectionVector.Normalize();
	m_pPlayer->SetReflectionVector(reflectionVector);

}
