//=============================================================================
//
// 頂点宣言
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __VERTEX_DECLARATION_H__
#define __VERTEX_DECLARATION_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../IVertexDeclaration.h"
#include "../VertexDeclarationDesc.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// 頂点宣言
//*****************************************************************************
class CVertexDeclaration
    : private CUncopyable
    , public IVertexDeclaration
{
private:

    /**
    * コンストラクタ
    */
    CVertexDeclaration();

    /**
    * デストラクタ
    */
    ~CVertexDeclaration();

public:

    /**
    * 生成
    * @ret 頂点宣言
    * @param pHolder デバイスホルダー
    * @param uNumDescs 頂点宣言のエレメント数
    * @param pDesc 頂点宣言情報
    */
    static CVertexDeclaration* Create(
        CDeviceHolder* pHolder,
        u8 uNumElems,
        const VertexDeclarationDesc* pDesc);

    /**
    * 開放
    */
    void Release();

    /**
    * DirectXインターフェース取得
    * @ret DirectX頂点宣言インターフェース
    */
    LPDIRECT3DVERTEXDECLARATION9 GetPointer() const;

    void SetDevice(LPDIRECT3DDEVICE9 pDev);
    
    void Attach();
    void Detach();

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    * @param pHolder デバイスホルダー
    * @param uNumDescs 頂点宣言エレメント数
    * @param pDesc 頂点宣言情報
    */
    HRESULT Init(CDeviceHolder* pHolder, u8 uNumDescs, const VertexDeclarationDesc* pDesc);

private:

    LPDIRECT3DVERTEXDECLARATION9 m_pDecl;

    LPDIRECT3DDEVICE9 m_pDev;
};

#endif  // __VERTEX_DECLARATION_H__

// EOF
