#include "pch.h"
#include"Sun.h"
#include<random>
using namespace DirectX;

//‰Šúƒ|ƒWƒVƒ‡ƒ“
const DirectX::SimpleMath::Vector3 Sun::INITIAL_POSITION(1100, 600, 600);

//‰Šú‰ñ“]
const DirectX::SimpleMath::Quaternion Sun::INITIAL_ROTATE(
	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(0),						//X‰ñ“]
		DirectX::XMConvertToRadians(0),						//Y‰ñ“]
		DirectX::XMConvertToRadians(225)						//Z‰ñ“]
	)
);

const float Sun::SUNSET_TIME(4);						//“ú–vŽžŠÔ	()
const float Sun::LIGHT_INTENSITY_LOWER_LIMIT(0.0f);		//Œõ‚Ì‰ºŒÀ	(0`)
const float Sun::LIGHT_INTENSITY_UPPER_LIMIT(1);		//Œõ‚ÌãŒÀ	(0`)
const float Sun::SUNSHINE_HOURS(180.0f / 100.0f);				//“úÆŽžŠÔ	(m/s)



Sun::Sun() :
	m_position(SimpleMath::Vector3::Zero),
	m_pSupplyPointModel(nullptr),
	m_rotate(DirectX::SimpleMath::Quaternion::Identity),
	m_rightDirect(DirectX::SimpleMath::Vector3::Zero),
	m_objectsRight(0)
{
}

Sun::~Sun()
{

}

void Sun::Initialize()
{
	//•½–Ê‚É‰ñ“]‚·‚éƒNƒI[ƒ^ƒjƒIƒ“
	//‚S‚T“x‹N‚«ã‚ª‚ç‚¹‚½x•ûŒüƒxƒNƒgƒ‹(‘¾—z‚ÌŒõ‚Ì•ûŒüƒxƒNƒgƒ‹)
	m_rightDirect = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitX,INITIAL_ROTATE);

	//‘¾—z‚ÌˆÊ’u‚ðŒvŽZ
	m_position = m_rightDirect * INITIAL_POSITION;

	m_objectsRight = m_rightDirect.y * 1.7320509f * SUNSET_TIME;
	if (m_objectsRight >= LIGHT_INTENSITY_UPPER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_UPPER_LIMIT;

	if (m_objectsRight <= LIGHT_INTENSITY_LOWER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_LOWER_LIMIT;

}

void Sun::Update(const float& elapsedTime)
{
	//•½–Ê‚É‰ñ“]‚·‚éƒNƒI[ƒ^ƒjƒIƒ“
	DirectX::SimpleMath::Quaternion q;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(elapsedTime * SUNSHINE_HOURS));
	m_rotate = q * m_rotate;

	//‚S‚T“x‹N‚«ã‚ª‚ç‚¹‚½x•ûŒüƒxƒNƒgƒ‹(‘¾—z‚ÌŒõ‚Ì•ûŒüƒxƒNƒgƒ‹)
	m_rightDirect = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitX,m_rotate * INITIAL_ROTATE);

	//‘¾—z‚ÌˆÊ’u‚ðŒvŽZ
	m_position = m_rightDirect * INITIAL_POSITION;

	m_objectsRight = m_rightDirect.y * 1.7320509f * SUNSET_TIME;
	if (m_objectsRight >= LIGHT_INTENSITY_UPPER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_UPPER_LIMIT;

	if (m_objectsRight <= LIGHT_INTENSITY_LOWER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_LOWER_LIMIT;


}

void Sun::Render()
{
	//ƒXƒP[ƒŠƒ“ƒOAˆÊ’u’²®A‰ñ“]‚ð‚³‚¹‚é
}

void Sun::Finalize()
{
}
