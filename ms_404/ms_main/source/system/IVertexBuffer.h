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
#include <common/DirectX.h>
#include "VertexBufferDesc.h"

//*****************************************************************************
// ���_�o�b�t�@�C���^�[�t�F�[�X
//*****************************************************************************
class IVertexBuffer
{
public:
    
    /**
    * �K�p
    */
    virtual void Attach() = 0;
    /**
    * ����
    */
    virtual void Detach() = 0;

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
    
    /**
    * �X�g���[���ԍ��ݒ�
    * @param index �X�g���[���ԍ�
    */
    virtual void SetStreamIndex(u32 index) = 0;
    /**
    * �o�b�t�@�I�t�Z�b�g�ݒ�(Byte)
    * @param offset �I�t�Z�b�g�l
    */
    virtual void SetOffset(u32 offset) = 0;
    /**
    * �X�g���[���ɗ������_�T�C�Y�ݒ�
    * @param stride �o�b�t�@�v�f�T�C�Y
    */
    virtual void SetStride(u32 stride) = 0;

protected:

    virtual ~IVertexBuffer(){}
};

#endif  // __VERTEXBUFFER_INTERFACE_H__

// EOF
