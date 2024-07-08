#pragma once
#include "Keyboard.h"
#include "Mouse.h"

//����
#include"ImaseLib/UserInterface.h"
#include"Scene/GameObjects/Models/Textures.h"
//

/// <summary>
/// KeyboardTracker�N���X���`����
/// </summary>
class KeyboardTracker
{
public:
	//�L�[�{�[�h�g���b�J�[�̃Q�b�^�[
	DirectX::Keyboard::KeyboardStateTracker GetKeyboardTracker() { return m_keyboardTracker; };

	//�}�E�X�g���b�J�[�̃Q�b�^�[
	DirectX::Mouse::ButtonStateTracker GetMouseTracker() { return m_mouseTracker; };

public:
	/// <summary>
	/// �`��N���X�̃C���X�^���X���擾����
	/// </summary>
	/// <returns>�`��N���X�̃C���X�^���X</returns>
	static KeyboardTracker*  GetInstance();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	KeyboardTracker();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// ����{�^��
	/// </summary>
	/// <returns>����{�^���������ꂽ��true</returns>
	bool Decision();

	/// <summary>
	/// ���{�^��
	/// </summary>
	/// <returns>���{�^���������ꂽ��true</returns>
	bool Left();

	/// <summary>
	/// �E�{�^��
	/// </summary>
	/// <returns>�E�{�^���������ꂽ��true</returns>
	bool Right();

	/// <summary>
	/// ��{�^��
	/// </summary>
	/// <returns>��{�^���������ꂽ��true</returns>
	bool Up();

	/// <summary>
	/// ���{�^��
	/// </summary>
	/// <returns>���{�^���������ꂽ��true</returns>
	bool Down();

private:
	// �`��̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<KeyboardTracker> m_tracker;

	// �L�[�{�[�h�X�e�[�g�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

	// �}�E�X�X�e�[�g�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_mouseTracker;

};

class KeyboardSingleton
{
public:
	//�L�[�{�[�h�̃Q�b�^�[
	DirectX::Keyboard::State GetKeyboardState() { return m_keyboardState; };

	//�}�E�X�̃Q�b�^�[
	DirectX::Mouse::State GetMouseState() { return m_mouseState; };

	/// <summary>
	/// �`��N���X�̃C���X�^���X���擾����
	/// </summary>
	/// <returns>�`��N���X�̃C���X�^���X</returns>
	static KeyboardSingleton* GetInstance();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	KeyboardSingleton();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// ����]�{�^��
	/// </summary>
	/// <returns>���{�^���������ꂽ��true</returns>
	bool Left();

	/// <summary>
	/// �E��]�{�^��
	/// </summary>
	/// <returns>�E�{�^���������ꂽ��true</returns>
	bool Right();

	/// <summary>
	/// �㏸�{�^��
	/// </summary>
	/// <returns>��{�^���������ꂽ��true</returns>
	bool Up();

	/// <summary>
	/// ���~�{�^��
	/// </summary>
	/// <returns>���{�^���������ꂽ��true</returns>
	bool Down();

	/// <summary>
	/// �����[���{�^��
	/// </summary>
	/// <returns>���{�^���������ꂽ��true</returns>
	bool LeftRool();

	/// <summary>
	/// �����[���{�^��
	/// </summary>
	/// <returns>���{�^���������ꂽ��true</returns>
	bool RightRool();

	/// <summary>
	/// ������{�^��
	/// </summary>
	/// <returns></returns>
	bool AvoidanceLeft();

	/// <summary>
	/// �E����{�^��
	/// </summary>
	/// <returns></returns>
	bool AvoidanceRight();

private:
	// �`��̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<KeyboardSingleton> m_keyboardSingleton;

	//�L�[�{�[�h
	DirectX::Keyboard::State m_keyboardState;

	//�}�E�X
	DirectX::Mouse::State m_mouseState;

};

/// <summary>
/// �摜�̈ʒu�����߂�
/// </summary>
/// <param name="position"></param>
/// <param name="textuerSize"></param>
/// <param name="scale"></param>
/// <param name="anchor"></param>
/// <param name="positionAnchor"></param>
/// <returns></returns>
static DirectX::SimpleMath::Vector2 TexPositionCorrection(
	const DirectX::SimpleMath::Vector2& position,
	const int& textuerSize_X,
	const int& textuerSize_Y,
	const DirectX::SimpleMath::Vector2& scale,
	const tito::ANCHOR& anchor,
	const tito::POSITION_ANCHOR& positionAnchor
)
{
	//�摜�̃A���J�[�̕�����
	const int TEXTURE_ANCHOR_RATIO_NUM = 3;
	DirectX::SimpleMath::Vector2 Pos = position;

	//�摜�T�C�Y�̔䗦���P�Q�W�O�C�V�Q�O�ő����Ă�̂Ńt���X�N���[���ɂȂ������Ɉʒu�����킹��v�Z
	DirectX::SimpleMath::Vector2 windowSizeRatio = DirectX::SimpleMath::Vector2(
		(static_cast<float>(Textures::GetInstance()->GetWindowWidth()) / static_cast<float>(Textures::GetInstance()->GetFullScreenNoneWindowWidth())),
		(static_cast<float>(Textures::GetInstance()->GetWindowHeight()) / static_cast<float>(Textures::GetInstance()->GetFullScreenNoneWindowHeight()))
	);
	Pos.x = position.x * windowSizeRatio.x;
	Pos.y = position.y * windowSizeRatio.y;

	//�����蔻��̂��߂Ɉʒu������o��
	int anc = static_cast<int>(anchor);
	Pos.x -=
		(
			(textuerSize_X * windowSizeRatio.x * scale.x) -
			(
				textuerSize_X * 
				(TEXTURE_ANCHOR_RATIO_NUM - 1 - (anc % TEXTURE_ANCHOR_RATIO_NUM)) * 
				scale.x * 
				windowSizeRatio.x
				)
			) / 
		2.f;

	Pos.y -=
		(
			(textuerSize_Y * windowSizeRatio.y * scale.y) -
			(textuerSize_Y * (anc / TEXTURE_ANCHOR_RATIO_NUM) * scale.y * windowSizeRatio.y)
			) /
		2.f;

	DirectX::SimpleMath::Vector2 windouSize = DirectX::SimpleMath::Vector2(static_cast<float>(Textures::GetInstance()->GetWindowWidth()), static_cast<float>(Textures::GetInstance()->GetWindowHeight()));

	//�����蔻��̂��߂Ɉʒu������o��
	int PosAnc = static_cast<int>(positionAnchor);
	Pos.x += (windouSize.x * (PosAnc % 3)) / 2.0f;
	Pos.y -= (windouSize.y * (PosAnc / 3)) / 2.0f;

	//UI�̈ʒuY�̓}�C�i�X�ɂȂ��Ă����̂Ń}�E�X�̈ʒu�ƍ��킹�邽�߂�-1��
	Pos.y *= -1;
	return Pos;
}

/// <summary>
/// �摜�̑傫���𒲐�
/// </summary>
/// <param name="textuerSize_X">�摜�T�C�YX</param>
/// <param name="textuerSize_Y">�摜�T�C�YY</param>
/// <returns>�C����̉摜�T�C�Y</returns>
static DirectX::SimpleMath::Vector2 TexSizeCorrection(
	const int& textuerSize_X,
	const int& textuerSize_Y
)
{
	//�摜�T�C�Y�̔䗦���P�Q�W�O�C�V�Q�O�ő����Ă�̂Ńt���X�N���[���ɂȂ������Ɉʒu�����킹��v�Z
	DirectX::SimpleMath::Vector2 windowSizeRatio = DirectX::SimpleMath::Vector2(
		(static_cast<float>(Textures::GetInstance()->GetWindowWidth()) / static_cast<float>(Textures::GetInstance()->GetFullScreenNoneWindowWidth())),
		(static_cast<float>(Textures::GetInstance()->GetWindowHeight()) / static_cast<float>(Textures::GetInstance()->GetFullScreenNoneWindowHeight()))
	);
	//���S����̃T�C�Y
	return DirectX::SimpleMath::Vector2(textuerSize_X * windowSizeRatio.x, textuerSize_Y * windowSizeRatio.y) / 2.0f;
}
