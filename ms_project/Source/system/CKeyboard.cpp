//=============================================================================
//
// �L�[�{�[�h
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CKeyboard.h"
#include "DebugUtil.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKeyboard::CKeyboard()
{
    memset(&m_aKeyState         , 0, sizeof(m_aKeyState));
    memset(&m_aKeyTrigger       , 0, sizeof(m_aKeyTrigger));
    memset(&m_aKeyRelease       , 0, sizeof(m_aKeyRelease));
    memset(&m_aKeyRepeat        , 0, sizeof(m_aKeyRepeat));
    memset(&m_aKeyRepeatCount   , 0, sizeof(m_aKeyRepeatCount));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKeyboard::~CKeyboard()
{
    if(m_pDev) m_pDev->Unacquire();
    SafeRelease(m_pDev);
}

//=============================================================================
// ����
//=============================================================================
CKeyboard* CKeyboard::Create(CInputObject* pObj, HWND hWnd)
{
    CKeyboard* pKey = new CKeyboard();

    if(pKey)
    {
        INIT_CHECK(pKey->Init(pObj, hWnd));
        _PrintConsole("�L�[�{�[�h\n");
    }

    return pKey;
}

//=============================================================================
// �J��
//=============================================================================
void CKeyboard::Release()
{
    delete this;
}

//=============================================================================
// �X�V
//=============================================================================
void CKeyboard::Update()
{
    BYTE aKeyState[MAX_KEY];    // �L�[���͂̃��[�N

    // �L�[�{�[�h�̏��擾
    if(SUCCEEDED(m_pDev->GetDeviceState(sizeof(aKeyState),
                                                &aKeyState[0])))
    {
        // ���͏��̍쐬
        // ���[�v����
        for(int nKeyCnt = 0; nKeyCnt < MAX_KEY; nKeyCnt++)
        {
            // �g���K�[���̍쐬
            m_aKeyTrigger[nKeyCnt] = ((m_aKeyState[nKeyCnt] ^ aKeyState[nKeyCnt]) & aKeyState[nKeyCnt]);

            // �����[�X���̍쐬
            m_aKeyRelease[nKeyCnt] = ((m_aKeyState[nKeyCnt] ^ aKeyState[nKeyCnt]) & ~aKeyState[nKeyCnt]);

            // ���s�[�g���̍쐬
            // �L�[����͂��Ă���Ƃ�
            if(aKeyState[nKeyCnt] & KEY_ON)
            {    
                // �J�E���g��REPEAT_TIME�����̂Ƃ�
                if(m_aKeyRepeatCount[nKeyCnt] < REPEAT_TIME)
                {
                    // �g���K�[���
                    m_aKeyRepeat[nKeyCnt] = m_aKeyTrigger[nKeyCnt];
                }

                // �J�E���g�����ȏ�̂Ƃ�
                else
                {
                    // �������
                    m_aKeyRepeat[nKeyCnt] = aKeyState[nKeyCnt];
                    // �J�E���^��REPEAT_TIME�ɌŒ�
                    m_aKeyRepeatCount[nKeyCnt] = REPEAT_TIME;
                }

                // �J�E���g����
                m_aKeyRepeatCount[nKeyCnt]++;
            }

            // ���͂��Ă��Ȃ��Ƃ�
            else 
            {
                // �g���K�[���
                m_aKeyRepeat[nKeyCnt] = m_aKeyTrigger[nKeyCnt];
                // �J�E���g�� 0 �ɂ���
                m_aKeyRepeatCount[nKeyCnt] = 0;
            }

            // �L�[���͏�Ԃ̍X�V
            m_aKeyState[nKeyCnt] = aKeyState[nKeyCnt];
        }
    }
    else
    {
        // �A�N�Z�X�����Ď擾
        m_pDev->Acquire();
    }
}

//=============================================================================
// �v���X��Ԏ擾
//=============================================================================
bool CKeyboard::GetPress(u8 key) const
{
    return m_aKeyState[key] & KEY_ON ? true : false;
}

//=============================================================================
// �g���K�[��Ԏ擾
//=============================================================================
bool CKeyboard::GetTrigger(u8 key) const
{
    return m_aKeyTrigger[key] & KEY_ON ? true : false;
}

//=============================================================================
// �����[�X��Ԏ擾
//=============================================================================
bool CKeyboard::GetRelease(u8 key) const
{
    return m_aKeyRelease[key] & KEY_ON ? true : false;
}

//=============================================================================
// ���s�[�g��Ԏ擾
//=============================================================================
bool CKeyboard::GetRepeat(u8 key) const
{
    return m_aKeyRepeat[key] & KEY_ON ? true : false;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CKeyboard::Init(CInputObject* pObj, HWND hWnd)
{
    HRESULT hr;

    LPDIRECTINPUT8 pDInput = pObj->GetDInput();

    // �f�o�C�X�̍쐬
    hr = pDInput->CreateDevice(GUID_SysKeyboard,
                                &m_pDev,
                                nullptr);
    _AssertExpr(SUCCEEDED(hr), "�L�[�{�[�h�f�o�C�X�������s");

    // �f�[�^�t�H�[�}�b�g�ݒ�
    hr = m_pDev->SetDataFormat(&c_dfDIKeyboard);
    _AssertExpr(SUCCEEDED(hr), "�L�[�{�[�h�f�[�^�t�H�[�}�b�g���������s");

    // �������[�h�̐ݒ�(���̃A�v���P�[�V�����Ƃ̃f�o�C�X�̋��L���@)
    hr = m_pDev->SetCooperativeLevel(hWnd,
                                            (DISCL_FOREGROUND |        // �t�H�A�O���E���h
                                             DISCL_NONEXCLUSIVE));    // ��r������
    _AssertExpr(SUCCEEDED(hr), "�L�[�{�[�h�������[�h���������s");

    // �L�[�{�[�h�ւ̃A�N�Z�X�����擾
    m_pDev->Acquire();

    return hr;
}

// EOF
