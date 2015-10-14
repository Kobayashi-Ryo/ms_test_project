//=============================================================================
//
// �J���[�o�b�t�@
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __COLOR_BUFFER_INTERFACE_H__
#define __COLOR_BUFFER_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "ColorBufferDesc.h"
#include "ITexture.h"

//*****************************************************************************
// �N���X
//*****************************************************************************
class IColorBuffer
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
    * �����_�[�^�[�Q�b�g�ɐݒ肷��Ƃ��̔ԍ���ݒ�
    */
    virtual void SetRenderTargetIndex(cu32 uIndex) = 0;
    
    /**
    * �o�b�t�@�����擾
    */
    virtual u32 GetWidth() const = 0;
    
    /**
    * �o�b�t�@�c���擾
    */
    virtual u32 GetHeight() const = 0;
    
    /**
    * �e�N�X�`���擾
    */
    virtual ITexture* GetTexture() const = 0;
};

#endif  // __COLOR_BUFFER_INTERFACE_H__

// EOF
