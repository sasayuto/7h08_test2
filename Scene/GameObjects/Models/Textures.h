#pragma once

class Sun;
/// <summary>
/// Textures�N���X���`����
/// </summary>
class Textures
{
public:
	//�f�o�C�X�̃Z�b�^�[�A�Q�b�^�[
	Sun* GetSun() { return m_pSun; }
	void SetSun(Sun* sun) { m_pSun = sun; }

	//�E�B���h�E�T�C�Y�̃Z�b�^�[�A�Q�b�^�[
	int GetWindowWidth() const { return m_windowWidth; }
	int GetWindowHeight() const { return m_windowHeight; }

	//�E�B���h�E�T�C�Y�̃Z�b�^�[�A�Q�b�^�[
	int GetFullScreenNoneWindowWidth() const { return m_fullScreenNoneWindowWidth; }
	int GetFullScreenNoneWindowHeight() const { return m_fullScreenNoneWindowHeight; }

	void SetWindowSize(const int& windowWidth, const int& windowHeight) { m_windowHeight = windowHeight; m_windowWidth = windowWidth; }
	void SetFullScreenNoneWindowSize(const int& windowWidth, const int& windowHeight) { m_fullScreenNoneWindowHeight = windowHeight; m_fullScreenNoneWindowWidth = windowWidth; }

public:

	//�e�N�X�`���[�̃��\�[�X�擾
	ID3D11ShaderResourceView* GetSmoke() { return m_smoke.Get(); };
	ID3D11ShaderResourceView* GetHouse_01NormalMap() { return m_House_01NormalMap.Get(); };
	ID3D11ShaderResourceView* GetNoNormalMap() { return m_NoNormalMap.Get(); };
	ID3D11ShaderResourceView* GetCoinlight() { return m_Coinlight.Get(); };
	ID3D11ShaderResourceView* GetPillarTexture_01NormalMap() { return m_PillarTexture_01NormalMap.Get(); };

public:
	/// <summary>
	/// �`��N���X�̃C���X�^���X���擾����
	/// </summary>
	/// <returns>�`��N���X�̃C���X�^���X</returns>
	static Textures*  GetInstance();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Textures();

	void LoadResource();

private:
	// �`��̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<Textures> m_textures;

	//�J�����̃|�C���^
	int m_windowHeight, m_windowWidth;

	//�t���X�N���[������Ȃ��Ƃ��̃E�B���h�E�T�C�Y(�V�F�[�_�[�ł͔䗦�Ȃ̂ő傫�����ς���Ă��܂�����)
	int m_fullScreenNoneWindowHeight, m_fullScreenNoneWindowWidth;

	//�R���e�L�X�g�̃|�C���^
	ID3D11DeviceContext1* m_pContext;

	//�f�o�C�X�̃|�C���^
	ID3D11Device1* m_pDevice;

	Sun* m_pSun;
	//�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_proj;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Coinlight;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_smoke;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_House_01NormalMap;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_NoNormalMap;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_PillarTexture_01NormalMap;
};


