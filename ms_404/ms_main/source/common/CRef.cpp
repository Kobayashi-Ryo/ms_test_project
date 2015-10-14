//=============================================================================
//
// ���t�@�����X�J�E���^
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CRef.h"
#include "DebugUtil.h"

CRef::~CRef()
{
}

void CRef::Decrement()
{
    m_nCounter--;
    if(m_nCounter <= 0)
    {
        delete this;
    }
}

// �J�E���g�A�b�v
void CRef::Increment()
{
    _Assert((unsigned)m_nCounter != (unsigned)-1);
    m_nCounter++;
}

int CRef::GetReferenceCount()
{
    return m_nCounter;
}

CRef::CRef()
    : m_nCounter(0)
{
}

// EOF
