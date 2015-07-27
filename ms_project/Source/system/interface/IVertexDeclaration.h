//=============================================================================
//
// ���_�錾�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __VERTEX_DECLARATION_INTERFACE_H__
#define __VERTEX_DECLARATION_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "DirectX.h"
#include "VertexDeclarationDesc.h"

//*****************************************************************************
// ���_�錾�C���^�[�t�F�[�X
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
