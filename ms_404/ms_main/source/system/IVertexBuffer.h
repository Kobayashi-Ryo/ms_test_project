//=============================================================================
//
// 頂点バッファインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __VERTEXBUFFER_INTERFACE_H__
#define __VERTEXBUFFER_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/DirectX.h>
#include "VertexBufferDesc.h"

//*****************************************************************************
// 頂点バッファインターフェース
//*****************************************************************************
class IVertexBuffer
{
public:
    
    /**
    * 適用
    */
    virtual void Attach() = 0;
    /**
    * 解除
    */
    virtual void Detach() = 0;

    /**
    * DirectX頂点バッファ取得
    * @ret DirectX頂点バッファ
    */
    virtual LPDIRECT3DVERTEXBUFFER9 GetPointer() const = 0;

    /**
    * 頂点バッファロック
    * @ret S_OK:ロック成功 E_FAIL:ロック失敗
    * @param pBuff ロックしたメモリの先頭ポインタ
    */
    virtual HRESULT Lock(void** pBuff) = 0;

    /**
    * 頂点バッファアンロック
    * @ret S_OK:成功 E_FAIL:失敗
    */
    virtual HRESULT Unlock() = 0;
    
    /**
    * ストリーム番号設定
    * @param index ストリーム番号
    */
    virtual void SetStreamIndex(u32 index) = 0;
    /**
    * バッファオフセット設定(Byte)
    * @param offset オフセット値
    */
    virtual void SetOffset(u32 offset) = 0;
    /**
    * ストリームに流す頂点サイズ設定
    * @param stride バッファ要素サイズ
    */
    virtual void SetStride(u32 stride) = 0;

protected:

    virtual ~IVertexBuffer(){}
};

#endif  // __VERTEXBUFFER_INTERFACE_H__

// EOF
