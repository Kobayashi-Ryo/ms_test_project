//=============================================================================
//
// DirectX入力オブジェクトクラス
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INPUT_OBJECT_H__
#define __INPUT_OBJECT_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <common/common.h>

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "dinput8.lib")// DirectX8の入力ライブラリ
#pragma comment (lib, "dxguid.lib")    // DirectXのコンポーネント使用に必要

//*****************************************************************************
// 入力オブジェクトクラス
//*****************************************************************************
class CInputObject
    : private CUncopyable
{
private:

    /**
    * コンストラクタ
    */
    CInputObject();

    /**
    * デストラクタ
    */
    ~CInputObject();

public:

    /**
    * 入力オブジェクト生成
    * @ret 入力オブジェクト
    */
    static CInputObject* Create();

    /**
    * 開放
    */
    void Release(void);

    /**
    * DirectInput取得
    * @ret DirectInput
    */
    LPDIRECTINPUT8 GetDInput() const;

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT Init();

private:

    // 入力オブジェクト
    LPDIRECTINPUT8 m_pDInput;
};

#endif  // __INPUT_OBJECT_H__

// EOF
