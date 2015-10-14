//=============================================================================
//
// リファレンスカウンタ
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
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

// カウントアップ
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
