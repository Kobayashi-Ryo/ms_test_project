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
#include "DirectX.h"
#include "VertexDeclarationDesc.h"

//*****************************************************************************
// 頂点宣言インターフェース
//*****************************************************************************
class IVertexDeclaration
{
public:

    virtual LPDIRECT3DVERTEXDECLARATION9 GetPointer() const = 0;

protected:

    virtual ~IVertexDeclaration(){}
};

#endif  // __VERTEX_DECLARATION_INTERFACE_H__

// EOF
