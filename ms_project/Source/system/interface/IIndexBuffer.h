//=============================================================================
//
// インデックスバッファインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INDEXBUFFER_INTERFACE_H__
#define __INDEXBUFFER_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "DirectX.h"
#include "IndexBufferDesc.h"

//*****************************************************************************
// インデックスバッファインターフェース
//*****************************************************************************
class IIndexBuffer
{
public:

    /**
    * DirectXインデックスバッファ取得
    * @ret DirectXインデックスバッファ
    */
    virtual LPDIRECT3DINDEXBUFFER9 GetPointer() const = 0;

    /**
    * インデックスバッファロック
    * @ret S_OK:ロック成功 E_FAIL:ロック失敗
    * @param pBuff ロックしたメモリの先頭ポインタ
    */
    virtual HRESULT Lock(void** pBuff) = 0;

    /**
    * インデックスバッファアンロック
    * @ret S_OK:成功 E_FAIL:失敗
    */
    virtual HRESULT Unlock() = 0;

protected:

    virtual ~IIndexBuffer(){}
};

#endif  // __INDEXBUFFER_INTERFACE_H__

// EOF
