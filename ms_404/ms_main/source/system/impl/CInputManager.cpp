//=============================================================================
//
// ���̓}�l�[�W���[�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CInputManager.h"

// input object
#include "CInputObject.h"
// input
#include "CKeyboard.h"
#include "CMouse.h"

// debug
#include <common/DebugUtil.h>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputManager::CInputManager()
    : m_pInputObject(nullptr)
    , m_pKeyboard(nullptr)
    , m_pMouse(nullptr)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputManager::~CInputManager()
{
    SafeRelease(m_pMouse);
    SafeRelease(m_pKeyboard);
    SafeRelease(m_pInputObject);
}

//=============================================================================
// ����
//=============================================================================
CInputManager* CInputManager::Create(HWND hWnd)
{
    CInputManager* pMgr = new CInputManager();

    if(pMgr)
    {
        INIT_CHECK(pMgr->Init(hWnd));
        _PrintConsole("���̓}�l�[�W���[\n");
    }

    return pMgr;
}

//=============================================================================
// �J��
//=============================================================================
void CInputManager::Release()
{
    delete this;
}

//=============================================================================
// �X�V
//=============================================================================
void CInputManager::Update()
{
    m_pKeyboard->Update();
    m_pMouse->Update();
}

//=============================================================================
// �L�[�{�[�h�擾
//=============================================================================
IKeyboard* CInputManager::GetKeyboard() const
{
    return m_pKeyboard;
}

//=============================================================================
// �}�E�X�擾
//=============================================================================
IMouse* CInputManager::GetMouse() const
{
    return m_pMouse;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CInputManager::Init(HWND hWnd)
{
    // ���̓I�u�W�F�N�g
    m_pInputObject = CInputObject::Create();
    if(IS_NULL(m_pInputObject))
    {
        return E_FAIL;
    }

    // �L�[�{�[�h
    m_pKeyboard = CKeyboard::Create(m_pInputObject, hWnd);
    if(IS_NULL(m_pKeyboard))
    {
        return E_FAIL;
    }
    
    // �}�E�X
    m_pMouse = CMouse::Create(m_pInputObject, hWnd);
    if(IS_NULL(m_pMouse))
    {
        return E_FAIL;
    }

    return S_OK;
}

// EOF
