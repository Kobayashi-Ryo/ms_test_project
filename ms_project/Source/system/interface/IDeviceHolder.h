//=============================================================================
//
// �f�o�C�X�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEVICE_HOLDER_INTERFACE_H__
#define __DEVICE_HOLDER_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "DirectX.h"

//*****************************************************************************
// �f�o�C�X�C���^�[�t�F�[�X
//*****************************************************************************
class IDeviceHolder
{
public:

    /**
    * DirectX9�f�o�C�X�擾
    * @ret Direct9�f�o�C�X
    */
    virtual LPDIRECT3DDEVICE9 GetDevice() const = 0;

    /**
    * �o�b�N�o�b�t�@�����擾
    * @ret �o�b�N�o�b�t�@����
    */
    virtual DWORD GetBackBufferWidth() const = 0;

    /**
    * �o�b�N�o�b�t�@�c���擾
    * @ret �o�b�N�o�b�t�@�c��
    */
    virtual DWORD GetBackBufferHeight() const = 0;

protected:

    virtual ~IDeviceHolder(){}
};

#endif  // __DEVICE_HOLDER_INTERFACE_H__

// EOF
