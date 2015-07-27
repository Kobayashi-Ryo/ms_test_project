//=============================================================================
//
// ���_�o�b�t�@�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __VERTEXBUFFER_INTERFACE_H__
#define __VERTEXBUFFER_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "DirectX.h"
#include "VertexBufferDesc.h"

//*****************************************************************************
// ���_�o�b�t�@�C���^�[�t�F�[�X
//*****************************************************************************
class IVertexBuffer
{
public:

    /**
    * DirectX���_�o�b�t�@�擾
    * @ret DirectX���_�o�b�t�@
    */
    virtual LPDIRECT3DVERTEXBUFFER9 GetPointer() const = 0;

    /**
    * ���_�o�b�t�@���b�N
    * @ret S_OK:���b�N���� E_FAIL:���b�N���s
    * @param pBuff ���b�N�����������̐擪�|�C���^
    */
    virtual HRESULT Lock(void** pBuff) = 0;

    /**
    * ���_�o�b�t�@�A�����b�N
    * @ret S_OK:���� E_FAIL:���s
    */
    virtual HRESULT Unlock() = 0;

protected:

    virtual ~IVertexBuffer(){}
};

#endif  // __VERTEXBUFFER_INTERFACE_H__

// EOF
