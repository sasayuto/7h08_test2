
#pragma once

#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"

/// <summary>
/// �w�i�̊��N���X���`����
/// </summary>
class Background
{
public:
    //���f���̃Z�b�^�[�A�Q�b�^�[
    DirectX::Model* GetBackGroundModel() { return m_backgroundModel; }
    void SetBackGroundModel(DirectX::Model* backgroundModel) { m_backgroundModel = backgroundModel; }

    //�傫���̃Z�b�^�[�A�Q�b�^�[
    void SetScale( const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
    DirectX::SimpleMath::Vector3 GetScale() const { return m_scale; }

    //�ʒu�̃Z�b�^�[�A�Q�b�^�[
    void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
    DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }

    //��]�̃Z�b�^�[
    void SetRotateX(const float& rotateX) { m_rotateY = rotateX; }

    static const float ROTATE_SPEED;

public:
    /// <summary>
    /// ��]�̓���
    /// </summary>
    virtual void SelectMotion();

    /// <summary>
    /// �I����ʂ̕`��ݒ�
    /// </summary>
    virtual void RotateRender();

public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Background();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Background();

    /// <summary>
    /// ����������
    /// </summary>
    virtual void Initialize();

    /// <summary>
    /// �`�悷��
    /// </summary>
    virtual void Render();

    /// <summary>
    /// ��n��
    /// </summary>
    virtual void Finalize();

private:
    //�傫��
    DirectX::SimpleMath::Vector3 m_scale;

    //�ʒu
    DirectX::SimpleMath::Vector3 m_position;

    //���f��
    DirectX::Model* m_backgroundModel;

    //��]
    float m_rotateY;
};

