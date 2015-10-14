//=============================================================================
//
// �f�o�C�X�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INTERFACE_DEVICE_H__
#define __INTERFACE_DEVICE_H__

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <common/common.h>
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"

//*****************************************************************************
// �N���X
//*****************************************************************************
class IDevice
{
public:

    /**
    * ��ʃN���A�ϐ��\��
    */
    virtual void ClearColor(cf32 r, cf32 b, cf32 b) = 0;
    virtual void ClearDepth(cf32 d) = 0;
    virtual void ClearStencil(cu32 s) = 0;
    /**
    * ��ʂ��N���A
    */
    virtual void Clear() = 0;

    /**
    * ���_�o�b�t�@�ݒ�
    */
    virtual void SetVertexBuffer(cu32 index, IVertexBuffer* pBuff) = 0;
    /**
    * �C���f�b�N�X�o�b�t�@�ݒ�
    */
    virtual void SetIndexBuffer(IIndexBuffer* pBuff) = 0;
    /**
    * �V�F�[�_�[�ݒ�
    */

    /**
    * �r���[�|�[�g�ݒ�
    */
    virtual void SetViewport(s32 left, s32 top, s32 right, s32 bottom);

    /**
    * �`��
    */
    /**
    * �C���f�b�N�X�t�`��
    */
};

#endif  // __INTERFACE_DEVICE_H__

// EOF
