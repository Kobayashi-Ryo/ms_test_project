//=============================================================================
//
// �t���[���o�b�t�@
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __FRAME_BUFFER_INTERFACE_H__
#define __FRAME_BUFFER_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "IColorBuffer.h"
#include "IDepthStencilBuffer.h"

//*****************************************************************************
// �N���X
//*****************************************************************************
class IFrameBuffer
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
    * �J���[�o�b�t�@�ݒ�
    */
    void SetColorBuffer(unsigned uIndex, IColorBuffer* pBuffer);
    
    /**
    * �[�x�o�b�t�@�ݒ�
    */
    void SetDepthStencilBuffer(IDepthStencilBuffer* pBuffer);
};

#endif  // __FRAME_BUFFER_INTERFACE_H__

// EOF
