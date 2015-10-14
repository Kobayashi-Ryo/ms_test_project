//=============================================================================
//
// 頂点宣言インターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __VERTEX_DECLARATION_INTERFACE_H__
#define __VERTEX_DECLARATION_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/DirectX.h>
#include "VertexDeclarationDesc.h"

//*****************************************************************************
// 頂点宣言インターフェース
//*****************************************************************************
class IVertexDeclaration
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

    virtual LPDIRECT3DVERTEXDECLARATION9 GetPointer() const = 0;

protected:

    virtual ~IVertexDeclaration(){}
};

#endif  // __VERTEX_DECLARATION_INTERFACE_H__

// EOF
