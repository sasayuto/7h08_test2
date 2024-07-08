#include "pch.h"
#include"PlayerStopMotion.h"
#include <math.h>
using namespace DirectX;


PlayerStopMotion::PlayerStopMotion(
	Player* motions,
	BulletManager* bulletManager,
	RespawnManager* respawnManager,
	SupplyPointManager* supplyPointManager,
	EnemyManager* enemyManager,
	CoinManager* coinManager
) :
	m_pPlayer(motions),
	m_pRespawnManager(respawnManager),
	m_pSupplyPointManager(supplyPointManager),
	m_pEnemyManager(enemyManager),
	m_pCoinManager(coinManager),
	m_pBulletManager(bulletManager)
{
}

PlayerStopMotion::~PlayerStopMotion()
{

}

void PlayerStopMotion::Initialize()
{
	////���X�|�[���n�_�Ɉʒu���Z�b�g
	//m_pPlayer->SetPosition(m_pRespawnManager->GetRespawnPosition());

	//�v���C���[�̏�Ԃɂ���Ĕ��a���ς��̂ŃZ�b�g
	m_pPlayer->GetCollider()->SetRadius(1.3f);
}

void PlayerStopMotion::Update(const float& elapsedTime)
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

	//���̔R���؂�̃��[�V����
	if (m_pPlayer->GetFuel() <= 0)
	{
		m_pPlayer->SetFuel(m_pPlayer->GetFuel()-1);
		if (m_pPlayer->GetFuel() <= -200)
		{
			//���񂾂̂ŋ����I�Ɍ��̉��o��������
			m_pPlayer->SetHP(0);
			m_pPlayer->GetBloodEffect()->Update(m_pPlayer->GetHP());

			m_pPlayer->SetIState(m_pPlayer->GetKillMotion());
		}

	}

	//�p�[�c�̍X�V
	m_pPlayer->PartsUpdate();

	if (m_pRespawnManager)
		//���X�|�[���̏Փˏ���
		m_pRespawnManager->CheckHitCharacter(m_pPlayer);

	if (m_pSupplyPointManager)
		//�A�C�e���̏Փˏ���
		m_pSupplyPointManager->CheckHitCharacter(m_pPlayer);

	if (m_pEnemyManager)
		//�G�̏Փˏ���
		m_pEnemyManager->CheckHitCharacter(m_pPlayer);

	if (m_pCoinManager)
		//�R�C���̏Փˏ���
		m_pCoinManager->CheckHitCharacter(m_pPlayer);

	if (m_pBulletManager)
		//�R�C���̏Փˏ���
		m_pBulletManager->CheckHitDamegeObjects(m_pPlayer, Bullet::BulletParent::PlayerBullet);
}

void PlayerStopMotion::Render()
{
	m_pPlayer->PartsRender();
	m_pPlayer->GetPlayerEffect()->Render();
	m_pPlayer->GetBloodEffect()->Render();
}

void PlayerStopMotion::Finalize()
{
}

void PlayerStopMotion::Motion(const float& elapsedTime)
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

	//WASD�L�[�Ŋp�x�̉����x�v�Z
	if (KeyboardSingleton::GetInstance()->Up())			playerVelcity.x += Player::PLAYER_BEND_ACCELERATION;
	if (KeyboardSingleton::GetInstance()->Down())		playerVelcity.x -= Player::PLAYER_BEND_ACCELERATION;
	if (KeyboardSingleton::GetInstance()->Left())		playerVelcity.y += Player::PLAYER_BEND_ACCELERATION;
	if (KeyboardSingleton::GetInstance()->Right())		playerVelcity.y -= Player::PLAYER_BEND_ACCELERATION;
	if (KeyboardSingleton::GetInstance()->LeftRool())	playerVelcity.z += Player::PLAYER_BEND_ACCELERATION;
	if (KeyboardSingleton::GetInstance()->RightRool())	playerVelcity.z -= Player::PLAYER_BEND_ACCELERATION;

	//�p�x�ɑ��x�𑫂�
	playerAngle = playerVelcity;

	m_pPlayer->SetTiltAnimation(playerVelcity.y);

	//�N�I�[�^�j�I����]�����
	SimpleMath::Quaternion p;
	p = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, m_pPlayer->GetTiltAnimation()
	);

	//�N�I�[�^�j�I����]�����
	SimpleMath::Quaternion q;
	q = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, XMConvertToRadians(playerAngle.z));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(playerAngle.x));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(playerAngle.y));
	m_pPlayer->SetAnimetionRotate(q * m_pPlayer->GetAnimetionRotate());

	//spase���������猸�����v���y���~�܂�
	if (keystate.LeftShift){}
	else
		if(m_pPlayer->GetFuel() >= 0)
			m_pPlayer->SetIState(m_pPlayer->GetMotion());
		
	//�X�s�[�h�����������痎��
	if (speed <= Player::PLAYER_STRAT_FALLING_SPEED)	gravity += Player::PLAYER_FALL_SPEED__ACCELERATION;

	//�����X�s�[�h�̃}�b�N�X
	if (gravity >= Player::PLAYER_FALL_SPEED_MAX)	gravity = Player::PLAYER_FALL_SPEED_MAX;

	//�j�󂳂������ɔ�΂�
	position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, -speed), m_pPlayer->GetRotate());

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

	//��]���Z�b�g
	m_pPlayer->SetRotate(p * m_pPlayer->GetAnimetionRotate());

	//�J�����̉�]���Z�b�g
	m_pPlayer->SetCameraRotate(m_pPlayer->GetAnimetionRotate());

	//�ʒu���Z�b�g
	m_pPlayer->SetPosition(position);
	//�i�s�x�N�g��
	DirectX::SimpleMath::Vector3 reflectionVector = position - previousposition;
	reflectionVector.Normalize();
	m_pPlayer->SetReflectionVector(reflectionVector);

}
