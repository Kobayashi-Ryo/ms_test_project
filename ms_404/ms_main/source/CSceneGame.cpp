//=============================================================================
//
// �Q�[���V�[��
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CSceneGame.h"
#include "AppDelegate.h"

#include "CGameStage.h"

#include <common/DebugUtil.h>

CSceneGame* CSceneGame::CreateScene()
{
    CSceneGame* scene = new CSceneGame();

    bool success = scene->Init();
    _CriticalAssert(success);

    return scene;
}

bool CSceneGame::Init()
{
    // �����̖��O�ݒ�
    SetName("SceneGame");

    m_pGameStage = CGameStage::Create("st001");
    AddChild(m_pGameStage);

    return true;
}

void CSceneGame::Update()
{
    CNode::Update();
}

void CSceneGame::Draw()
{
    // HACK �K��2���
    CApplication* app = CApplication::GetInstance();
    auto sys = app->GetSystem();
    auto holder = sys->GetDeviceHolder();
    auto d3dDev = holder->GetDevice();
    D3DVIEWPORT9 vp;
    d3dDev->GetViewport(&vp);

    // ����ʕ`�揈��
    // start�Ȃǂ̕\��

    // ui�͂��ꂼ��̉�ʂŕ`�悷��悤�ɂ���
    // ���S�Ƀ��C�A�E�g�����߂邩
    // �v���C���[�}�l�[�W��������āAUI���������邩

    // ����
    D3DVIEWPORT9 left = vp;
    left.X = 0;
    left.Y = 0;
    left.Width = (u32)(holder->GetBackBufferWidth() * 0.5f);
    left.Height = holder->GetBackBufferHeight();
    d3dDev->SetViewport(&left);
    d3dDev->Clear(
                0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
                D3DXCOLOR(1.0f, 0.5f, 0.5f,0), 1, 0);
    // �����`�揈��
    // �J�����ݒ�
    // UI�ݒ�
    m_pGameStage->Draw();

    // �E��
    D3DVIEWPORT9 right = vp;
    right.X = (u32)(holder->GetBackBufferWidth() * 0.5f);
    right.Y = 0;
    right.Width = (u32)(holder->GetBackBufferWidth() * 0.5f);
    right.Height = holder->GetBackBufferHeight();
    d3dDev->SetViewport(&right);
    d3dDev->Clear(
                0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
                D3DXCOLOR(0.5f, 1.0f, 0.5f,0), 1, 0);

    // ���ɖ߂�
    d3dDev->SetViewport(&vp);
}

// EOF
