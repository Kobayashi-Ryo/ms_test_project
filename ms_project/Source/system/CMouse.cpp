//=============================================================================
//
// �}�E�X
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CMouse.h"
#include "DebugUtil.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMouse::CMouse()
    : m_nScroll(0)
{
    // ���W�N���A
    m_pos.x = 0;
    m_pos.y = 0;
    // �ړ������N���A
    m_diff.x = 0;
    m_diff.y = 0;

    // �}�E�X�ϐ��N���A
    memset(&m_MouseState, 0, sizeof(DIMOUSESTATE2));
    memset(&m_MouseTrigger, 0, sizeof(DIMOUSESTATE2));
    memset(&m_MouseRelease, 0, sizeof(DIMOUSESTATE2));
    memset(&m_MouseRepeat, 0, sizeof(DIMOUSESTATE2));
    memset(&m_aMouseRepeatCount, 0, sizeof(int) * MAX_BUTTON);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMouse::~CMouse()
{
    if(m_pDev) m_pDev->Unacquire();
    SafeRelease(m_pDev);
}

//=============================================================================
// ����
//=============================================================================
CMouse* CMouse::Create(CInputObject* pObj, HWND hWnd)
{
    CMouse* pMs = new CMouse();

    if(pMs)
    {
        INIT_CHECK(pMs->Init(pObj, hWnd));
        _PrintConsole("�}�E�X\n");
    }

    return pMs;
}

//=============================================================================
// �J��
//=============================================================================
void CMouse::Release()
{
    delete this;
}

//=============================================================================
// �X�V
//=============================================================================
void CMouse::Update()
{
    DIMOUSESTATE2 TempState;
    
    // �}�E�X�̏��擾
    if(SUCCEEDED(m_pDev->GetDeviceState(sizeof(TempState),
                                                &TempState)))
    {
        // �X�N���[�����W�擾
        GetCursorPos(&m_pos);
        // �X�N���[�����W����N���C�A���g���W�ɕϊ�
        ScreenToClient(m_hWnd, &m_pos);

        // ������ݒ�
        m_diff.x = TempState.lX;
        m_diff.y = TempState.lY;
        // �X�N���[���ʎ擾
        m_nScroll = TempState.lZ;

        for(int i = 0; i < MAX_BUTTON; i++)
        {
            // �g���K�[���̍쐬
            m_MouseTrigger.rgbButtons[i] = ((m_MouseState.rgbButtons[i] ^ TempState.rgbButtons[i]) & TempState.rgbButtons[i]);

            // �����[�X���̍쐬
            m_MouseRelease.rgbButtons[i] = ((m_MouseState.rgbButtons[i] ^ TempState.rgbButtons[i]) & ~TempState.rgbButtons[i]);
            
            // ���s�[�g���̍쐬
            // �L�[����͂��Ă���Ƃ�
            if(TempState.rgbButtons[i] & KEY_ON)
            {    
                // �J�E���g��REPEAT_TIME�����̂Ƃ�
                if(m_aMouseRepeatCount[i] < REPEAT_TIME)
                {
                    // �g���K�[���
                    m_MouseRepeat.rgbButtons[i] = m_MouseTrigger.rgbButtons[i];
                }

                // �J�E���g�����ȏ�̂Ƃ�
                else
                {
                    // �������
                    m_MouseRepeat.rgbButtons[i] = TempState.rgbButtons[i];
                    // �J�E���^��REPEAT_TIME�ɌŒ�
                    m_aMouseRepeatCount[i] = REPEAT_TIME;
                }

                // �J�E���g����
                m_aMouseRepeatCount[i]++;
            }

            // ���͂��Ă��Ȃ��Ƃ�
            else 
            {
                // �g���K�[���
                m_MouseRepeat.rgbButtons[i] = m_MouseTrigger.rgbButtons[i];
                // �J�E���g�� 0 �ɂ���
                m_aMouseRepeatCount[i] = 0;
            }

            // �L�[���͏�Ԃ̍X�V
            m_MouseState.rgbButtons[i] = TempState.rgbButtons[i];
        }
    }
    else
    {
        // �A�N�Z�X�����Ď擾
        m_pDev->Acquire();
    }
}

//=============================================================================
// ���W�擾
//=============================================================================
const POINT& CMouse::GetPosition() const
{
    return m_pos;
}

//=============================================================================
// �ړ��ʎ擾
//=============================================================================
const POINT& CMouse::GetMove() const
{
    return m_diff;
}

//=============================================================================
// �X�N���[���ʎ擾
//=============================================================================
LONG CMouse::GetScroll() const
{
    return m_nScroll;
}

//=============================================================================
// �v���X��Ԏ擾
//=============================================================================
bool CMouse::GetPress(MouseButton btn) const
{
    return m_MouseState.rgbButtons[btn] & KEY_ON ? true : false;
}

//=============================================================================
// �g���K�[��Ԏ擾
//=============================================================================
bool CMouse::GetTrigger(MouseButton btn) const
{
    return m_MouseTrigger.rgbButtons[btn] & KEY_ON ? true : false;
}

//=============================================================================
// �����[�X��Ԏ擾
//=============================================================================
bool CMouse::GetRelease(MouseButton btn) const
{
    return m_MouseRelease.rgbButtons[btn] & KEY_ON ? true : false;
}

//=============================================================================
// ���s�[�g��Ԏ擾
//=============================================================================
bool CMouse::GetRepeat(MouseButton btn) const
{
    return m_MouseRepeat.rgbButtons[btn] & KEY_ON ? true : false;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CMouse::Init(CInputObject* pObj, HWND hWnd)
{
    HRESULT hr;

    LPDIRECTINPUT8 pDInput = pObj->GetDInput();

    // �f�o�C�X�̍쐬
    hr = pDInput->CreateDevice(GUID_SysMouse,
                                &m_pDev,
                                nullptr);
    _AssertExpr(SUCCEEDED(hr), "�}�E�X�f�o�C�X�������s");

    // �f�[�^�t�H�[�}�b�g�ݒ�
    hr = m_pDev->SetDataFormat(&c_dfDIMouse);
    _AssertExpr(SUCCEEDED(hr), "�}�E�X�f�[�^�t�H�[�}�b�g���������s");

    // �������[�h�̐ݒ�(���̃A�v���P�[�V�����Ƃ̃f�o�C�X�̋��L���@)
    hr = m_pDev->SetCooperativeLevel(hWnd,
                                            (DISCL_FOREGROUND |        // �t�H�A�O���E���h
                                             DISCL_NONEXCLUSIVE));    // ��r������
    _AssertExpr(SUCCEEDED(hr), "�}�E�X�������[�h���������s");

    // �}�E�X�ւ̃A�N�Z�X�����擾
    m_pDev->Acquire();

    // �E�B���h�E�n���h���ݒ�
    m_hWnd = hWnd;

    return hr;
}

// EOF
