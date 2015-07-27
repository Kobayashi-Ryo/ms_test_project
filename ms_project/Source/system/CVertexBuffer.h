//=============================================================================
//
// 頂点バッファ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "common.h"
#include "IVertexBuffer.h"
#include "CLostResource.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// 頂点バッファ
//*****************************************************************************
class CVertexBuffer
    : public IVertexBuffer
    , public CLostResource
{
private:

    /**
    * コンストラクタ
    */
    CVertexBuffer();

    /**
    * デストラクタ
    */
    ~CVertexBuffer();

public:

    /**
    * 頂点バッファ生成
    * @ret 頂点バッファ
    * @param pHolder デバイスホルダー
    * @param desc 頂点情報
    */
    static CVertexBuffer* Create(CDeviceHolder* pHolder, const VertexBufferDesc& desc);

    /**
    * DirectX頂点バッファ取得
    * @ret DirectX頂点バッファ
    */
    LPDIRECT3DVERTEXBUFFER9 GetPointer() const;

    /**
    * 開放
    */
    void Release();

    /**
    * 頂点バッファロック
    * @ret S_OK:ロック成功 E_FAIL:ロック失敗
    * @param pBuff ロックしたメモリの先頭ポインタ
    */
    HRESULT Lock(void** pBuff);

    /**
    * 頂点バッファアンロック
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
    * @param desc 頂点情報
    */
    HRESULT Init(CDeviceHolder* pHolder, const VertexBufferDesc& desc);

private:

    // 頂点バッファ
    LPDIRECT3DVERTEXBUFFER9 m_pVtx;

    // 頂点バッファ情報
    D3DVERTEXBUFFER_DESC m_desc;
};

#endif  // __VERTEX_BUFFER_H__

// EOF
