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
#include "DirectX.h"
#include "VertexBufferDesc.h"

//*****************************************************************************
// 頂点バッファインターフェース
//*****************************************************************************
class IVertexBuffer
{
public:

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

protected:

    virtual ~IVertexBuffer(){}
};

#endif  // __VERTEXBUFFER_INTERFACE_H__

// EOF
