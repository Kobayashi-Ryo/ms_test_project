//=============================================================================
//
// �E�B���h�E�N���X [CWindow.h]
//
// Date : 2015/1/31
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CWindow.h"
#include "CThread.h"
#include <common/DebugUtil.h>

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
// �E�B���h�E�X�^�C��
const int CWindow::GAME_WINDOW = (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX));

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWindow::CWindow()
    : m_hWnd(0)
    , m_desc()
    , m_pThread(nullptr)
    , m_bInitialized(false)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWindow::~CWindow()
{
    // �X���b�h�̊J��
    m_pThread->release();
    // �E�B���h�E�N���X�o�^����
    UnregisterClass(m_desc.strClassName.c_str(), GetModuleHandle(NULL));
}

//=============================================================================
// ��������
//=============================================================================
CWindow* CWindow::Create(const WindowDesc& desc)
{
    CWindow* pWnd = new CWindow();

    if(pWnd)
    {
        pWnd->InnerCreate(desc);
        _CriticalAssertExpr(pWnd, "�E�B���h�E�̐����Ɏ��s");
        _PrintConsole("�E�B���h�E\n");
    }

    return pWnd;
}

//=============================================================================
// �J��
//=============================================================================
void CWindow::Release()
{
    delete this;
}

//=============================================================================
// ���b�Z�[�W����
//=============================================================================
CWindow::Message CWindow::ProcMessage(MSG& msg)
{
    // ���b�Z�[�W������ꍇ����
    Message message = MESSAGE_OK;
    BOOL bIsMessageExist = PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
    if(TRUE == bIsMessageExist)
    {
      // �I�����b�Z�[�W������ꂽ�ꍇ
      if(msg.message == WM_QUIT)
      {
        message = MESSAGE_TERMINATE;
      }
      // �����Ă��Ȃ��ꍇ
      else
      {
        // ���b�Z�[�W�̖|��Ƒ��o
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

    return message;
}

//=============================================================================
// �E�B���h�E�\��
//=============================================================================
void CWindow::ShowWindow()
{
    // �E�B���h�E�\��
    ::ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
}

//=============================================================================
// �E�B���h�E�����擾
//=============================================================================
DWORD CWindow::GetWidth() const
{
    return m_desc.uWidth;
}

//=============================================================================
// �E�B���h�E�c���擾
//=============================================================================
DWORD CWindow::GetHeight() const
{
    return m_desc.uHeight;
}

//=============================================================================
// �E�B���h�E�n���h���擾
//=============================================================================
HWND CWindow::GetHandle() const
{
    return m_hWnd;
}

//=============================================================================
// �L���v�V�����ݒ�
//=============================================================================
void CWindow::SetCaption(const std::string& strCaption)
{
    m_desc.strCaption = strCaption;
    // �E�B���h�E�̃L���v�V������ݒ�
    SetWindowText(m_hWnd, m_desc.strCaption.c_str());
}

//=============================================================================
// �J�[�\�����N���b�v����
//=============================================================================
void CWindow::ClipCursor(const int x, const int y)
{
    POINT p = {x, y};
    ClientToScreen(m_hWnd, &p);
    RECT clip = {p.x - 1, p.y - 1,
            p.x + 1, p.y + 1};
    ::ClipCursor(&clip);
}

//=============================================================================
// �J�[�\���̃N���b�v����������
//=============================================================================
void CWindow::UnclipCursor()
{
    ::ClipCursor(NULL);
}

//=============================================================================
// �������ςݔ���
//=============================================================================
bool CWindow::IsInitialized()
{
    return m_bInitialized;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CWindow::Initialize()
{
    HRESULT hr = S_OK;

    HINSTANCE hInstance = GetModuleHandle(NULL);

    RECT rc;
    // �E�B���h�E��`�͈͐ݒ�
    rc.top = 0;
    rc.left = 0;
    rc.right = m_desc.uWidth;
    rc.bottom = m_desc.uHeight;

    // �E�B���h�E�N���X������
    WNDCLASSEX wcex =
    {
        sizeof(WNDCLASSEX),
        CS_CLASSDC,
        m_desc.pWndProc,  // �E�B���h�E�v���V�[�W���֐�
        0,
        0,
        hInstance,
        NULL,
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW + 1),
        NULL,
        m_desc.strClassName.c_str(),
        NULL
    };

    // �E�B���h�E�N���X�o�^
    if(FAILED(RegisterClassEx(&wcex)))
    {
        MessageBox(NULL, "�E�B���h�E�N���X�o�^���s", "�G���[", MB_OK);
        return E_FAIL;
    }

    // �E�B���h�E�����킹
    AdjustWindowRect(
      &rc,    // �E�B���h�E��
      GAME_WINDOW, // �E�B���h�E�X�^�C��
      FALSE);    // ���j���[�̗L��

    // �E�B���h�E���W�ݒ�
    // �^�X�N�o�[���������f�B�X�v���C���擾
    int nDisplayWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    int nDisplayHeight = GetSystemMetrics(SM_CYFULLSCREEN);

    // �E�B���h�E�쐬
    int nWindowWidth = rc.right - rc.left;  // �E�B���h�E����
    int nWindowHeight = rc.bottom - rc.top;  // �E�B���h�E�c��
    int nWindowPosX = (nDisplayWidth >> 1) - (nWindowWidth >> 1);  // �E�B���h�E����X���W
    int nWindowPosY = (nDisplayHeight >> 1) - (nWindowHeight >> 1);  // �E�B���h�E����Y���W

    // �E�B���h�E�̍쐬
    m_hWnd = CreateWindowEx(0,
        m_desc.strClassName.c_str(),
        m_desc.strCaption.c_str(),
        // �Ϙg�A�ő剻�{�^������菜��
        GAME_WINDOW,
        nWindowPosX,
        nWindowPosY,
        nWindowWidth,
        nWindowHeight,
        NULL,
        NULL,
        hInstance,
        NULL);

    // �쐬���s�\��
    if(!m_hWnd)
    {
        MessageBox(NULL, "�E�B���h�E�쐬���s", "�G���[", MB_OK);
        return E_FAIL;
    }

    m_bInitialized = true;

    return hr;
}

//=============================================================================
// ������������
//=============================================================================
HRESULT CWindow::InnerCreate(const WindowDesc& desc)
{
    m_desc = desc;

    // �X���b�h����
    HRESULT hr = E_FAIL;
    CThread::create(&m_pThread);
    hr = m_pThread->start(m_desc.pAsyncData, m_desc.pAsyncProc, true) ? S_OK : E_FAIL;

    return hr;
}

// EOF
