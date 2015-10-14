//=============================================================================
//
// �f�o�b�O����
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CDebug.h"
#include "CDeviceHolder.h"
#include <common/DebugUtil.h>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDebug::CDebug()
    : m_pFont(nullptr)
    , m_nNumDebugProcLength(0)
    , m_bUseDebugFlag(false)
{
#ifdef _DEBUG    // �f�o�b�O���f�t�H���g�Ńf�o�b�OON
    m_bUseDebugFlag = true;
#else            // �����[�X���f�t�H���g�Ńf�o�b�OOFF
    m_bUseDebugFlag = false;
#endif

    memset(m_aStrDebugProc, 0, sizeof(m_aStrDebugProc));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDebug::~CDebug()
{
}

//=============================================================================
// �f�o�b�O��������
//=============================================================================
CDebug* CDebug::Create(CDeviceHolder *pHolder, IResource* pRes)
{
    CDebug* pDbg = new CDebug();

    if(pDbg)
    {
        INIT_CHECK(pDbg->Init(pHolder, pRes));
        _PrintConsole("�f�o�b�O\n");
    }

    return pDbg;
}

//=============================================================================
// �J��
//=============================================================================
void CDebug::Release()
{
    delete this;
}

#ifndef _RELEASE
//=============================================================================
// �`��
//=============================================================================
void CDebug::Draw()
{
    // �f�o�b�O�t���O�������Ă����Ƃ��`�悷��
    if(m_bUseDebugFlag)
    {
        RECT rect = {5, 5, 0, 0};
        if(m_pFont)
        {
            m_pFont->Draw(rect, m_aStrDebugProc);
        }
    }

    this->Clear();
}

//=============================================================================
// �f�o�b�O���N���A
//=============================================================================
void CDebug::Clear()
{
    // �\���p������o�b�t�@�̃N���A
    memset(m_aStrDebugProc, 0, sizeof(m_aStrDebugProc));
    // �f�o�b�O�\���p�o�b�t�@�g�p�ʂ�0�ɂ���
    m_nNumDebugProcLength = 0;
}

//=============================================================================
// �f�o�b�O�����񑗏o
//=============================================================================
void CDebug::Print(cs8* str, ...)
{
    // �ϐ��錾
    va_list vaList;    // �ό������i�[���邽�߂̕ϐ�(�ψ������X�g)
    
    // �ψ����ɃA�N�Z�X���邽�߂̏���������
    // ��2�����Ɏw�肷��argc�́A����"..."�̒��O(����)�łȂ���΂Ȃ�Ȃ�
    va_start(vaList, str);
    
    // �ϐ��錾
    // �o�b�t�@�֏������݁A���������܂ꂽ��������擾(nullptr�����͊܂܂Ȃ�)
    int nLength = vsprintf_s(&m_aStrDebugProc[m_nNumDebugProcLength], MAX_DEBUG_BUF - m_nNumDebugProcLength - 1, str, vaList);
    // �f�o�b�O�\���p������̒����ɏ������񂾕�����̒����𑫂�
    m_nNumDebugProcLength += nLength;

    // ���ӂꂽ�炻��ȏ�\�����Ȃ�
    if(m_nNumDebugProcLength >= MAX_DEBUG_BUF)
    {
        m_nNumDebugProcLength = MAX_DEBUG_BUF - 1;
        m_aStrDebugProc[m_nNumDebugProcLength] = '\0';
    }

    // �ψ����A�N�Z�X�I������
    va_end(vaList);
}

//=============================================================================
// �f�o�b�O�\��
//=============================================================================
void CDebug::Show()
{
    m_bUseDebugFlag = true;
}

//=============================================================================
// �f�o�b�O��\��
//=============================================================================
void CDebug::Hide()
{
    m_bUseDebugFlag = false;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CDebug::Init(CDeviceHolder *pHolder, IResource* pRes)
{
    const DWORD Height = pHolder->GetBackBufferHeight();
    cf32 RATIO = 0.04f;
    cf32 FONT_HEIGHT = Height * RATIO;
    FontDesc desc;
    desc.Height = (s32)FONT_HEIGHT;
    desc.Width = 0;
    desc.Italic = false;

    m_pFont = pRes->GetFont(desc);
    _Assert(m_pFont);

    // ����������
    return S_OK;
}

#else
void CDebug::Draw(){}
void CDebug::Clear(){}
void CDebug::Print(cs8*, ...){}
void CDebug::Show(){}
void CDebug::Hide(){}
HRESULT CDebug::Init(CDeviceHolder*, IResource*){return S_OK;}
#endif

// EOF
