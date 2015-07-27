//=============================================================================
//
// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INDEXBUFFER_INTERFACE_H__
#define __INDEXBUFFER_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "DirectX.h"
#include "IndexBufferDesc.h"

//*****************************************************************************
// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X
//*****************************************************************************
class IIndexBuffer
{
public:

    /**
    * DirectX�C���f�b�N�X�o�b�t�@�擾
    * @ret DirectX�C���f�b�N�X�o�b�t�@
    */
    virtual LPDIRECT3DINDEXBUFFER9 GetPointer() const = 0;

    /**
    * �C���f�b�N�X�o�b�t�@���b�N
    * @ret S_OK:���b�N���� E_FAIL:���b�N���s
    * @param pBuff ���b�N�����������̐擪�|�C���^
    */
    virtual HRESULT Lock(void** pBuff) = 0;

    /**
    * �C���f�b�N�X�o�b�t�@�A�����b�N
    * @ret S_OK:���� E_FAIL:���s
    */
    virtual HRESULT Unlock() = 0;

protected:

    virtual ~IIndexBuffer(){}
};

#endif  // __INDEXBUFFER_INTERFACE_H__

// EOF
