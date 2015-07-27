//=============================================================================
//
// インデックスバッファ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INDEX_BUFFER_H__
#define __INDEX_BUFFER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "common.h"
#include "IIndexBuffer.h"
#include "CLostResource.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// インデックスバッファ
//*****************************************************************************
class CIndexBuffer
    : public IIndexBuffer
    , public CLostResource
{
private:

    /**
    * コンストラクタ
    */
    CIndexBuffer();

    /**
    * デストラクタ
    */
    ~CIndexBuffer();

public:

    /**
    * インデックスバッファ生成
    * @ret インデックスバッファ
    * @param pHolder デバイスホルダー
    * @param desc インデックス情報
    */
    static CIndexBuffer* Create(CDeviceHolder* pHolder, const IndexBufferDesc& desc);

    /**
    * DirectXインデックスバッファ取得
    * @ret DirectXインデックスバッファ
    */
    LPDIRECT3DINDEXBUFFER9 GetPointer() const;

    /**
    * 開放
    */
    void Release();

    /**
    * インデックスバッファロック
    * @ret S_OK:ロック成功 E_FAIL:ロック失敗
    * @param pBuff ロックしたメモリの先頭ポインタ
    */
    HRESULT Lock(void** pBuff);

    /**
    * インデックスバッファアンロック
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT Unlock();

    /**
    * リソースの強制的な削除
    */
    void CleanUp();

    /**
    * リソース情報の保存
    */
    void Restore();

    /**
    * リソース情報の再読み込み
    */
    void Reload(CDeviceHolder* pHolder);

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    * @param pHolder デバイスホルダー
    * @param desc インデックス情報
    */
    HRESULT Init(CDeviceHolder* pHolder, const IndexBufferDesc& desc);

private:

    // インデックスバッファ
    LPDIRECT3DINDEXBUFFER9 m_pIdx;

    // インデックスバッファ情報
    D3DINDEXBUFFER_DESC m_desc;
};

#endif  // __INDEX_BUFFER_H__

// EOF
