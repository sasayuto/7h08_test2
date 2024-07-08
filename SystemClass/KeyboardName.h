#pragma once
/// <summary>
/// KeyboardName�N���X���`����
/// </summary>
class KeyboardName
{
public:
	/// <summary>
	/// �`��N���X�̃C���X�^���X���擾����
	/// </summary>
	/// <returns>�`��N���X�̃C���X�^���X</returns>
	static KeyboardName*  GetInstance();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	KeyboardName();

	void Update();
	void SetName(std::wstring& name);
	void SetName(std::string& name);

private:
	// �`��̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<KeyboardName> m_KeyboardName;

	// �`��̃C���X�^���X�ւ̃|�C���^
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	// �`��̃C���X�^���X�ւ̃|�C���^
	DirectX::Keyboard::State m_Keyboard;
};


