//=============================================================================
//
// デバッグ処理
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEBUG_H__
#define __DEBUG_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/DirectX.h>
#include <common/d3dx.h>
#include <system/IResource.h>
#include <system/IDebug.h>

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// デバッグ処理
//*****************************************************************************
class CDebug
    : private CUncopyable
    , public IDebug
{
private:

    /**
    * コンストラクタ
    */
    CDebug();

    /**
    * デストラクタ
    */
    ~CDebug();

public:

    /**
    * デバッグ処理生成
    * @ret デバッグ処理
    * @param pHolder デバイスホルダー
    * @param pRes リソースインターフェース
    */
    static CDebug* Create(CDeviceHolder *pHolder, IResource* pRes);

    /**
    * 開放
    */
    void Release();

    /**
    * 描画
    */
    void Draw();

    /**
    * デバッグ情報クリア
    */
    void Clear();

    /**
    * デバッグ文字列送出
    * @param str 文字列フォーマット
    * @param ... フォーマット引数
    */
    void Print(cs8* str, ...);

    /**
    * デバッグ表示
    */
    void Show();

    /**
    * デバッグ非表示
    */
    void Hide();

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    * @param pHolder デバイスホルダー
    */
    HRESULT Init(CDeviceHolder *pHolder, IResource* pRes);

private:

    // 最大文字数
    static cs16 MAX_DEBUG_BUF = 2048;

    // デバッグ表示用フォント
    IFont* m_pFont;

    // デバッグ表示用バッファ
    s8 m_aStrDebugProc[MAX_DEBUG_BUF];

    // デバッグ表示用バッファの現在の使用量
    s32 m_nNumDebugProcLength;

    // デバッグを表示するかどうかのフラグ
    bool m_bUseDebugFlag;
};

#endif  // __DEBUG_H__

// EOF
