//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include"Scene/GameTitle.h"
#include"Scene/StageSelectScene.h"
#include"Scene/PlayScene/TutorialScene.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/Models/Textures.h"
#include"Scene/GameObjects/Models/KeyboardTracker.h"
#include"Scene/GameObjects/Models/SingletonDeviceResources.h"
#include"SystemClass/KeyboardName.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
    : m_fullscreen(FALSE),
    m_colliderSceneFlag(false), m_PlaySceneFlag(false), m_debugFontDrawFlag(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);
     m_deviceResources->CreateDeviceResources();
     SingletonDeviceResources::GetInstance();
     SingletonDeviceResources::GetInstance()->SetDeviceResources(m_deviceResources.get());

  //�V���O���g���N���X�̃C���X�^���X����
    Draw::GetInstance();
    Resources::GetInstance();
    Textures::GetInstance();
    KeyboardSingleton::GetInstance();
    KeyboardTracker::GetInstance();
    KeyboardName::GetInstance();
    Draw::GetInstance()->SetWindowSize(width, height);
    Textures::GetInstance()->SetWindowSize(width, height);
    Textures::GetInstance()->SetFullScreenNoneWindowSize(width, height);

    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    SingletonDeviceResources::GetInstance()->Initialize();

    Draw::GetInstance()->Initialize();

    //�����N���V�[��
    m_sceneManager->SetScene<GameTitle>();
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
        {
            Update(m_timer);
        });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.

    KeyboardSingleton::GetInstance()->Update();

    KeyboardTracker::GetInstance()->Update();
    auto kb = KeyboardSingleton::GetInstance()->GetKeyboardState();
    auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
    KeyboardName::GetInstance()->Update();
    auto context = m_deviceResources->GetD3DDeviceContext();
    context;

    if (kb.LeftAlt)
        if (kb.LeftControl)
            if (kbTracker.pressed.Z)
            {
                if (m_colliderSceneFlag)
                {
                    //m_sceneManager->SetNextScene<GameTitle>();
                    m_PlaySceneFlag = false;
                    m_colliderSceneFlag = false;
                }
                else
                {
                    //m_sceneManager->SetNextScene<ModelSampleScene>();
                    m_PlaySceneFlag = false;
                    m_colliderSceneFlag = true;
                }
            }
    if (!kb.LeftAlt)
        if (kb.LeftControl)
            if (kbTracker.pressed.Z)
            {
                if (m_PlaySceneFlag)
                {
                    m_sceneManager->SetNextScene<GameTitle>();
                    m_PlaySceneFlag = false;
                    m_colliderSceneFlag = false;
                }
                else
                {
                    m_sceneManager->SetNextScene<TutorialScene>();
                    m_PlaySceneFlag = true;
                    m_colliderSceneFlag = false;
                }
            }

    if (kb.LeftControl)
        if (kbTracker.pressed.F)
        {
            if (m_debugFontDrawFlag)  m_debugFontDrawFlag = false;
            else                      m_debugFontDrawFlag = true;
        }

    //�V�[���̍X�V
    m_sceneManager->Update(elapsedTime);


}

#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

    //// fps�̕\��
    std::wostringstream oss;
    oss << "fps:" << m_timer.GetFramesPerSecond();
    SingletonDebugFont::GetInstance()->AddString(oss.str().c_str(), SimpleMath::Vector2(0.0f, 0.0f),DirectX::Colors::Black);

    //�V�[���̕`��
    m_sceneManager->Render();
   
    // �f�o�b�O�p������̕`��
   if (m_debugFontDrawFlag)
        SingletonDebugFont::GetInstance()->Render(m_states.get());

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();

}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
    Draw::GetInstance()->SetWindowSize(r.right, r.bottom);
    Textures::GetInstance()->SetWindowSize(r.right, r.bottom);

    // �t���X�N���[�������ׂ�
    BOOL fullscreen = FALSE;
    m_deviceResources->GetSwapChain()->GetFullscreenState(&fullscreen, nullptr);
    // �t���X�N���[������������Ă��܂������̏���
    if (m_fullscreen != fullscreen)
    {
        m_fullscreen = fullscreen;
        // ResizeBuffers�֐����Ăяo��
        m_deviceResources->CreateWindowSizeDependentResources();
    }
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    Draw::GetInstance()->SetWindowSize(width, height);
    Textures::GetInstance()->SetWindowSize(width, height);
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1280;
    height = 720;
}
#pragma endregion

// ��ʃ��[�h��ݒ肷��֐��iTRUE�F�t���X�N���[���j
void Game::SetFullscreenState(BOOL value)
{
    m_fullscreen = value;
    m_deviceResources->GetSwapChain()->SetFullscreenState(m_fullscreen, nullptr);
    if (value) m_deviceResources->CreateWindowSizeDependentResources();
}


#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).
     // ���ʃX�e�[�g�I�u�W�F�N�g�̍쐬
    //�`��̐ݒ�

    m_states = std::make_unique<CommonStates>(device);
    SingletonDeviceResources::GetInstance()->SetCommonStates(m_states.get());

    // �f�o�b�O�p������\���I�u�W�F�N�g�̍쐬
    SingletonDebugFont::GetInstance()->Initialize(device, context, L"Resources/Font/SegoeUI_18.spritefont");

    //�X�R�A�̌v�Z���쐬�i�V�[�����܂����̂ł����ō���ēn���B�������ȂǋC���t����j
    m_scoreCalculation = std::make_unique<ScoreCalculation>();

    // ���[�U�[���\�[�X�̍쐬
    if (!m_userResources) m_userResources = std::make_unique<UserResources>();

    // �V�[���}�l�[�W���[�̍쐬
    if (!m_sceneManager) m_sceneManager = std::make_unique<Imase::SceneManager<UserResources>>(m_userResources.get());

    m_userResources->SetStepTimerStates(&m_timer);
    m_userResources->SetScoreCalculation(m_scoreCalculation.get());
    m_userResources->SetCommonStates(m_states.get());

    // ���\�[�X�����[�h����	
    Textures::GetInstance()->LoadResource();

    // ���\�[�X�����[�h����	
    Resources::GetInstance()->LoadResource();
    //�V�[���̃f�o�C�X�Ɉˑ����鏉�������s��
    m_sceneManager->CreateDeviceDependentResources();

}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

    //�V�[���̃E�B���h�E�Y�T�C�Y���ύX���ꂽ�Ƃ��ɌĂ΂�鏈��
    m_sceneManager->CreateWindowSizeDependentResources();
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    //�V�[���Ƀf�o�C�X���X�g���̏���
    m_sceneManager->OnDeviceLost();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
