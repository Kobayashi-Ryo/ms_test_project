//=============================================================================
//
// �A�v���P�[�V����
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CApplication.h"
#include "CScene.h"
#include <common/D3DX.h>

#include <system/impl/CSystem.h>
#include <system/impl/CHardwareTimer.h>
#include <system/impl/CDeviceHolder.h>

#include <common/DebugUtil.h>

namespace
{
    const DWORD DIFF_MILLISEC = 16;
};

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CApplication* CApplication::m_spApp = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CApplication::CApplication()
    : m_bIsRunning(true)
    , m_pCurrentScene(nullptr)
    , m_pHardwareTimer(nullptr)
    , m_pSystem(nullptr)
{
    m_pSystem = new CSystem();
    _CriticalAssert(!IS_NULL(m_pSystem));
    HRESULT hr = m_pSystem->Initialize("");
    _CriticalAssert(SUCCEEDED(hr));
    
    // �n�[�h�E�F�A�^�C�}�[
    m_pHardwareTimer = CHardwareTimer::Create();
    _Assert(m_pHardwareTimer);

    m_spApp = this;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CApplication::~CApplication()
{
    SafeRelease(m_pCurrentScene);
    SafeRelease(m_pSystem);
    SafeRelease(m_pHardwareTimer);
    m_spApp = nullptr;
}

//=============================================================================
// �A�v���P�[�V�������I��������
//=============================================================================
void CApplication::Finish()
{
    m_bIsRunning = false;
    m_pSystem->Finish();
}

//=============================================================================
// �V�X�e���̎擾
//=============================================================================
ISystem* CApplication::GetSystem()
{
    return m_pSystem;
}

//=============================================================================
// ���݂̃V�[���擾
//=============================================================================
CScene* CApplication::GetCurrentScene()
{
    return m_pCurrentScene;
}

//=============================================================================
// �A�v���P�[�V�����J�n
//=============================================================================
s32 CApplication::Run()
{
    if(!m_spApp->Init())
    {
        return -1;
    }

    while(m_pSystem->IsRunning())
    {
        m_pHardwareTimer->Start();
        
        // �V�X�e���X�V
        m_pSystem->Update();
        // �V�[���X�V
        if(m_pCurrentScene)
        {
            m_pCurrentScene->Update();
        }

        if(SUCCEEDED(m_pSystem->BeginDraw()))
        {
            // �A�v���P�[�V�����`��
            // HACK ��ʃN���A
            m_pSystem->GetDeviceHolder()->GetDevice()->Clear(
                0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
                D3DXCOLOR(0.3f, 0.3f, 0.3f,0), 1, 0);
            // �`�揈��
            if(m_pCurrentScene)
            {
                m_pCurrentScene->Draw();
            }

            m_pSystem->DebugDraw();

            m_pSystem->EndDraw();
        }
        
        // �o�b�t�@�X���b�v
        m_pSystem->SwapBuffers();

        m_pHardwareTimer->End();

        // �X���b�h���x��
        m_pHardwareTimer->Sleep(DIFF_MILLISEC);
    }

    return 0;
}

//=============================================================================
// �V�[����ʂ̃V�[���Œu������
//=============================================================================
void CApplication::ReplaceScene(CScene* pScene)
{
    if(!pScene) return;
    if(m_pCurrentScene == pScene) return;

    if(m_pCurrentScene)
    {
        // �V�[�����J��
        SafeRelease(m_pCurrentScene);
    }
    m_pCurrentScene = pScene;
}

//=============================================================================
// �A�v���P�[�V�����C���X�^���X�擾
//=============================================================================
CApplication* CApplication::GetInstance()
{
    return m_spApp;
}

// EOF
