//=============================================================================
//
// �V�X�e���N���X
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CSystem.h"

// window
#include "CWindow.h"
// device holder
#include "CDeviceHolder.h"
// sound manager
#include "CSoundManager.h"
// input manager
#include "CInputManager.h"
// debug
#include "CDebug.h"
// resource manager
#include "CResourceManager.h"

// hardware timer
#include "CHardwareTimer.h"

// thread
#include <process.h>

// util
#include <common/DebugUtil.h>

//*****************************************************************************
// ���O���
//*****************************************************************************
namespace
{
    static const DWORD DIFF_MILLISEC = 16;
};

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> CSystem::m_sWndProcHook = nullptr;

//*****************************************************************************
// ���O���
//*****************************************************************************
namespace
{
unsigned __stdcall WindowProc(void* pData)
{
    //=============================================================================
    // �E�B���h�E����
    //=============================================================================
    CSystem *pSys = (CSystem*)pData;

    CWindow *pWindow = pSys->GetWindowInst();
    HRESULT hr = pWindow->Initialize();
    if(FAILED(hr))
    {
      _endthreadex(0);
      return 0;
    }

    // �E�B���h�E�\��
    pWindow->ShowWindow();

    MSG Msg;
    Msg.message = WM_NULL;
    volatile bool bLoop = true;
    while(bLoop)
    {
      // �I��
      if(CWindow::MESSAGE_TERMINATE == pWindow->ProcMessage(Msg))
      {
        pSys->Finish();
        bLoop = false;
        break;
      }
      Sleep(16);
    }

    _endthreadex(0);
    return 0;
}
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSystem::CSystem()
    : m_pWindow(nullptr)
    , m_pDeviceHolder(nullptr)
    , m_pSoundManager(nullptr)
    , m_pInputManager(nullptr)
    , m_pDebug(nullptr)
    , m_pResourceManager(nullptr)
    , m_pHardwareTimer(nullptr)
    , m_bIsRunning(false)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSystem::~CSystem()
{
    SafeRelease(m_pResourceManager);
    SafeRelease(m_pDebug);
    SafeRelease(m_pInputManager);
    SafeRelease(m_pSoundManager);
    SafeRelease(m_pDeviceHolder);
    SafeRelease(m_pWindow);
    SafeRelease(m_pHardwareTimer);
}

//=============================================================================
// �V�X�e���̎��s
//=============================================================================
s32 CSystem::Run(const std::string& arg)
{
    CSystem* pSys = new CSystem();

    HRESULT hr = pSys->Initialize(arg);
    _CriticalAssert(SUCCEEDED(hr));

    s32 result = 0;

    while(pSys->IsRunning())
    {
        result = pSys->Update();
    }

    pSys->Release();

    return result;
}

//=============================================================================
// �`��J�n
//=============================================================================
HRESULT CSystem::BeginDraw()
{
    HRESULT suc = m_pDeviceHolder->GetDevice()->BeginScene();
    return suc;
}

//=============================================================================
// �f�o�b�O�`��
//=============================================================================
void CSystem::DebugDraw()
{
    m_pDebug->Draw();
}

//=============================================================================
// �`��I��
//=============================================================================
void CSystem::EndDraw()
{
    m_pDeviceHolder->GetDevice()->EndScene();
    m_pDebug->Clear();
}

//=============================================================================
// �o�b�N�o�b�t�@����
//=============================================================================
void CSystem::SwapBuffers()
{
    HRESULT hr = m_pDeviceHolder->GetDevice()->Present(nullptr, nullptr, nullptr, nullptr);
    if(!SUCCEEDED(hr))
    {
        // �f�o�C�X���X�g
        m_pResourceManager->Reset();
    }
}

//=============================================================================
// ������
//=============================================================================
HRESULT CSystem::Initialize(const std::string& arg)
{
    HRESULT hr = S_OK;

    // �n�[�h�E�F�A�^�C�}�[
    m_pHardwareTimer = CHardwareTimer::Create();
    _Assert(m_pHardwareTimer);

    // �E�B���h�E
    hr = CreateWindowMS();
    _Assert(SUCCEEDED(hr));

    // �f�o�C�X
    hr = CreateDeviceHolder();
    _Assert(SUCCEEDED(hr));
    
    // ���\�[�X�}�l�[�W���[
    hr = CreateResourceManager();
    _Assert(SUCCEEDED(hr));

    // ���̓}�l�[�W���[
    hr = CreateInputManager();
    _Assert(SUCCEEDED(hr));

    // �T�E���h�}�l�[�W���[
    hr = CreateSoundManager();
    _Assert(SUCCEEDED(hr));

    // �f�o�b�O
    hr = CreateDebug();
    _Assert(SUCCEEDED(hr));

    m_bIsRunning = true;
    _PrintConsole("�V�X�e��\n");

    return hr;
}

//=============================================================================
// �J��
//=============================================================================
void CSystem::Release()
{
    delete this;
}

//=============================================================================
// �X�V
//=============================================================================
s32 CSystem::Update()
{
    // �e�V�X�e���X�V
    m_pInputManager->Update();

    /*
    m_pHardwareTimer->Start();

    // �e�V�X�e���X�V
    m_pInputManager->Update();

    // �A�v���P�[�V�����X�V
    m_pDebug->Print("�f�o�b�O�e�X�g\n");
    auto key = m_pInputManager->GetKeyboard();
    if(key->GetPress(DIK_P))
    {
        m_pDebug->Print("�ҁ[\n");
    }

    HRESULT suc = m_pDeviceHolder->GetDevice()->BeginScene();
    if(SUCCEEDED(suc))
    {
        // �A�v���P�[�V�����`��
        // HACK ��ʃN���A
        m_pDeviceHolder->GetDevice()->Clear(
            0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
            D3DXCOLOR(0,0,0,0), 1, 0);

        // �V�X�e���n�`��
        m_pDebug->Draw();

        m_pDeviceHolder->GetDevice()->EndScene();
    }
    else
    {
        m_pDebug->Clear();
    }

    // HACK ��ʃX���b�v
    HRESULT hr = m_pDeviceHolder->GetDevice()->Present(nullptr, nullptr, nullptr, nullptr);
    if(!SUCCEEDED(hr))
    {
        // �f�o�C�X���X�g
        m_pResourceManager->Reset();
    }

    m_pHardwareTimer->End();

    // �X���b�h���x��
    m_pHardwareTimer->Sleep(DIFF_MILLISEC);
    */

    // TODO : �����K���Ȓl
    return 0;
}

//=============================================================================
// �I��
//=============================================================================
void CSystem::Finish()
{
    m_bIsRunning = false;
}

//=============================================================================
// �V�X�e���N�������ǂ���
//=============================================================================
bool CSystem::IsRunning()
{
    return m_bIsRunning;
}

//=============================================================================
// �E�B���h�E�擾
//=============================================================================
IWindow* CSystem::GetWindow() const
{
    return m_pWindow;
}

//=============================================================================
// �f�o�C�X�z���_�[�擾
//=============================================================================
IDeviceHolder* CSystem::GetDeviceHolder() const
{
    return m_pDeviceHolder;
}

//=============================================================================
// �f�o�C�X�z���_�[�擾
//=============================================================================
ISound* CSystem::GetSound() const
{
    return m_pSoundManager;
}

//=============================================================================
// ���̓}�l�[�W���擾
//=============================================================================
IInputManager* CSystem::GetInputManager() const
{
    return m_pInputManager;
}

//=============================================================================
// �f�o�b�O�擾
//=============================================================================
IDebug* CSystem::GetDebug() const
{
    return m_pDebug;
}

//=============================================================================
// ���\�[�X�擾
//=============================================================================
IResource* CSystem::GetResource() const
{
    return m_pResourceManager;
}

//=============================================================================
// �����I��
//=============================================================================
void CSystem::Abort()
{
    Finish();
    _AbortExpr("�����I�ɒ��f����܂���");
}

//=============================================================================
// �E�B���h�E����
//=============================================================================
HRESULT CSystem::CreateWindowMS()
{
    WindowDesc desc;
    // TODO �E�B���h�E�T�C�Y�͐ݒ�t�@�C������
    desc.uWidth = 960;
    desc.uHeight = 540;
    desc.strCaption = "MS 404";
    desc.strClassName = "g_04_fever";
    desc.pWndProc = WndProc;
    desc.pAsyncData = this;
    desc.pAsyncProc = ::WindowProc;
    m_pWindow = CWindow::Create(desc);
    if(IS_NULL(m_pWindow))
    {
        return E_FAIL;
    }

    return S_OK;
}

//=============================================================================
// �f�o�C�X�z���_�[����
//=============================================================================
HRESULT CSystem::CreateDeviceHolder()
{
    while(!m_pWindow->IsInitialized()){}
    DeviceDesc desc;
    desc.bWindowed = TRUE;
    desc.hWnd = m_pWindow->GetHandle();
    desc.uBackBufferWidth = m_pWindow->GetWidth();
    desc.uBackBufferHeight = m_pWindow->GetHeight();
    m_pDeviceHolder = CDeviceHolder::Create(desc);

    if(IS_NULL(m_pDeviceHolder))
    {
        return E_FAIL;
    }

    return S_OK;
}

//=============================================================================
// �T�E���h�}�l�[�W���[����
//=============================================================================
HRESULT CSystem::CreateSoundManager()
{
    m_pSoundManager = CSoundManager::Create();
    if(IS_NULL(m_pSoundManager))
    {
        return E_FAIL;
    }
    return S_OK;
}

//=============================================================================
// ���̓}�l�[�W���[����
//=============================================================================
HRESULT CSystem::CreateInputManager()
{
    while(!m_pWindow->IsInitialized()){}
    m_pInputManager = CInputManager::Create(m_pWindow->GetHandle());
    if(IS_NULL(m_pInputManager))
    {
        return E_FAIL;
    }
    return S_OK;
}

//=============================================================================
// �f�o�b�O����
//=============================================================================
HRESULT CSystem::CreateDebug()
{
    m_pDebug = CDebug::Create(m_pDeviceHolder, m_pResourceManager);
    if(IS_NULL(m_pDebug))
    {
        return E_FAIL;
    }

    return S_OK;
}

//=============================================================================
// ���\�[�X�}�l�[�W������
//=============================================================================
HRESULT CSystem::CreateResourceManager()
{
    m_pResourceManager = CResourceManager::Create(m_pDeviceHolder);
    if(IS_NULL(m_pResourceManager))
    {
        return E_FAIL;
    }
    return S_OK;
}

//=============================================================================
// �t�b�N�֐��ݒ�
//=============================================================================
void CSystem::SetWndProcHook(WND_PROC_HOOK Hook)
{
    m_sWndProcHook = Hook;
}

//=============================================================================
// �E�B���h�E�擾
//=============================================================================
CWindow* CSystem::GetWindowInst() const
{
    return m_pWindow;
}

//=============================================================================
// �f�o�C�X�z���_�[�擾
//=============================================================================
CDeviceHolder* CSystem::GetDeviceHolderInst() const
{
    return m_pDeviceHolder;
}

//=============================================================================
// �E�B���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK CSystem::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if(m_sWndProcHook)
  {
    m_sWndProcHook(hWnd, uMsg, wParam, lParam);
  }

  // ���b�Z�[�W�ɂ���ĕ���
  switch(uMsg)
  {
    // �E�B���h�E�j��
  case WM_DESTROY:
    // �I�����b�Z�[�W���o
    PostQuitMessage(0);
    break;

    // �L�[����
  case WM_KEYDOWN:
    // �L�[���͏���
    KeyInputProc(hWnd, wParam);
    break;

    // �E�B���h�E�T�C�Y�ύX��
  case WM_SIZE:
    break;

  default:
    break;
  }

  // �W�������ɓ�����
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// �L�[���͏���
//=============================================================================
void CSystem::KeyInputProc(HWND hWnd, WPARAM wParam)
{
  switch(wParam)
  {
    // �G�X�P�[�v�������ꂽ�Ƃ�
  case VK_ESCAPE:
    DestroyWindow(hWnd);
    break;
  }
}

// EOF
