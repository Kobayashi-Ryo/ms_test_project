//=============================================================================
//
// デバッグ処理
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CDebug.h"
#include "CDeviceHolder.h"
#include <common/DebugUtil.h>

//=============================================================================
// コンストラクタ
//=============================================================================
CDebug::CDebug()
    : m_pFont(nullptr)
    , m_nNumDebugProcLength(0)
    , m_bUseDebugFlag(false)
{
#ifdef _DEBUG    // デバッグ時デフォルトでデバッグON
    m_bUseDebugFlag = true;
#else            // リリース時デフォルトでデバッグOFF
    m_bUseDebugFlag = false;
#endif

    memset(m_aStrDebugProc, 0, sizeof(m_aStrDebugProc));
}

//=============================================================================
// デストラクタ
//=============================================================================
CDebug::~CDebug()
{
}

//=============================================================================
// デバッグ処理生成
//=============================================================================
CDebug* CDebug::Create(CDeviceHolder *pHolder, IResource* pRes)
{
    CDebug* pDbg = new CDebug();

    if(pDbg)
    {
        INIT_CHECK(pDbg->Init(pHolder, pRes));
        _PrintConsole("デバッグ\n");
    }

    return pDbg;
}

//=============================================================================
// 開放
//=============================================================================
void CDebug::Release()
{
    delete this;
}

#ifndef _RELEASE
//=============================================================================
// 描画
//=============================================================================
void CDebug::Draw()
{
    // デバッグフラグが立っていたとき描画する
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
// デバッグ情報クリア
//=============================================================================
void CDebug::Clear()
{
    // 表示用文字列バッファのクリア
    memset(m_aStrDebugProc, 0, sizeof(m_aStrDebugProc));
    // デバッグ表示用バッファ使用量を0にする
    m_nNumDebugProcLength = 0;
}

//=============================================================================
// デバッグ文字列送出
//=============================================================================
void CDebug::Print(cs8* str, ...)
{
    // 変数宣言
    va_list vaList;    // 可変個引数を格納するための変数(可変引数リスト)
    
    // 可変引数にアクセスするための初期化処理
    // 第2引数に指定するargcは、引数"..."の直前(左側)でなければならない
    va_start(vaList, str);
    
    // 変数宣言
    // バッファへ書き込み、かつ書き込まれた文字列を取得(nullptr文字は含まない)
    int nLength = vsprintf_s(&m_aStrDebugProc[m_nNumDebugProcLength], MAX_DEBUG_BUF - m_nNumDebugProcLength - 1, str, vaList);
    // デバッグ表示用文字列の長さに書き込んだ文字列の長さを足す
    m_nNumDebugProcLength += nLength;

    // あふれたらそれ以上表示しない
    if(m_nNumDebugProcLength >= MAX_DEBUG_BUF)
    {
        m_nNumDebugProcLength = MAX_DEBUG_BUF - 1;
        m_aStrDebugProc[m_nNumDebugProcLength] = '\0';
    }

    // 可変引数アクセス終了処理
    va_end(vaList);
}

//=============================================================================
// デバッグ表示
//=============================================================================
void CDebug::Show()
{
    m_bUseDebugFlag = true;
}

//=============================================================================
// デバッグ非表示
//=============================================================================
void CDebug::Hide()
{
    m_bUseDebugFlag = false;
}

//=============================================================================
// 初期化
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

    // 初期化成功
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
