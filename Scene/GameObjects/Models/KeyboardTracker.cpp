#include "pch.h"
#include "KeyboardTracker.h"

using namespace DirectX;
std::unique_ptr<KeyboardTracker> KeyboardTracker::m_tracker = nullptr;
std::unique_ptr<KeyboardSingleton> KeyboardSingleton::m_keyboardSingleton = nullptr;

KeyboardTracker::KeyboardTracker():
	m_keyboardTracker(),
	m_mouseTracker()
{
}

void KeyboardTracker::Update()
{    
	// �L�[�{�[�h�X�e�[�g�g���b�J�[�̍X�V
	m_keyboardTracker.Update(KeyboardSingleton::GetInstance()->GetKeyboardState());

	// �}�E�X�X�e�[�g�g���b�J�[�̍X�V
	m_mouseTracker.Update(Mouse::Get().GetState());
}

KeyboardTracker* KeyboardTracker::GetInstance()
{
	//���łɐ�������Ă邩�`�F�b�N
	if (m_tracker == nullptr)
	{
		//�`��̃C���X�^���X�𐶐�����
		m_tracker = std::make_unique<KeyboardTracker>();
	}
	//�`��̃C���X�^���X��Ԃ�
	return m_tracker.get();
}
bool KeyboardTracker::Decision()
{
	if (m_keyboardTracker.pressed.Enter) return true;
	if (m_keyboardTracker.pressed.Space) return true;
	if (m_mouseTracker.leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED) return true;

	return false;
}

bool KeyboardTracker::Left()
{
	if (m_keyboardTracker.pressed.Left) return true;
	if (m_keyboardTracker.pressed.A) return true;

	return false;
}

bool KeyboardTracker::Right()
{
	if (m_keyboardTracker.pressed.Right) return true;
	if (m_keyboardTracker.pressed.D) return true;

	return false;
}

bool KeyboardTracker::Up()
{
	if (m_keyboardTracker.pressed.Up) return true;
	if (m_keyboardTracker.pressed.W) return true;

	return false;
}

bool KeyboardTracker::Down()
{
	if (m_keyboardTracker.pressed.Down) return true;
	if (m_keyboardTracker.pressed.S) return true;

	return false;
}



KeyboardSingleton::KeyboardSingleton():
	m_keyboardState()
{
}

void KeyboardSingleton::Update()
{
	//�L�[�{�[�h���X�V
	m_keyboardState = Keyboard::Get().GetState();
	m_mouseState = Mouse::Get().GetState();
}

KeyboardSingleton* KeyboardSingleton::GetInstance()
{
	//���łɐ�������Ă邩�`�F�b�N
	if (m_keyboardSingleton == nullptr)
	{
		//�L�[�{�[�h�̃C���X�^���X�𐶐�����
		m_keyboardSingleton = std::make_unique<KeyboardSingleton>();
	}
	//�L�[�{�[�h�̃C���X�^���X��Ԃ�
	return m_keyboardSingleton.get();
}

bool KeyboardSingleton::Left()
{
	if (m_keyboardState.Left) return true;
	if (m_keyboardState.A) return true;

	return false;
}

bool KeyboardSingleton::Right()
{
	if (m_keyboardState.Right) return true;
	if (m_keyboardState.D) return true;

	return false;
}

bool KeyboardSingleton::LeftRool()
{
	if (m_keyboardState.Q) return true;

	return false;
}

bool KeyboardSingleton::RightRool()
{
	if (m_keyboardState.E) return true;

	return false;
}

bool KeyboardSingleton::AvoidanceLeft()
{
	if (m_keyboardState.Left)
		if (m_keyboardState.LeftShift)
			return true;

	return false;
}

bool KeyboardSingleton::AvoidanceRight()
{
	if (m_keyboardState.Right)
		if (m_keyboardState.LeftShift)
			return true;

	return false;
}

bool KeyboardSingleton::Up()
{
	if (m_keyboardState.Up) return true;
	if (m_keyboardState.W) return true;

	return false;
}

bool KeyboardSingleton::Down()
{
	if (m_keyboardState.Down) return true;
	if (m_keyboardState.S) return true;

	return false;
}

