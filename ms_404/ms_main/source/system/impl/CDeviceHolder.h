//=============================================================================
//
// �f�o�C�X��ێ�����N���X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEVICE_HOLDER_H__
#define __DEVICE_HOLDER_H__

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <common/DirectX.h>
#include <common/CUncopyable.h>

// interface
#include "../IDeviceHolder.h"

//*****************************************************************************
// �f�o�C�X���N���X
//*****************************************************************************
struct DeviceDesc
{
    DWORD uBackBufferWidth;
    DWORD uBackBufferHeight;
    BOOL bWindowed;
    HWND hWnd;
};

//*****************************************************************************
// �f�o�C�X��ێ�����N���X
//*****************************************************************************
class CDeviceHolder
    : private CUncopyable
    , public IDeviceHolder
{
private:

    /**
    * �R���X�g���N�^
    */
    CDeviceHolder();

    /**
    * �f�X�g���N�^
    */
    ~CDeviceHolder();

public:

    /**
    * ��������
    * @ret �C���X�^���X
    * @param desc �f�o�C�X���
    */
    static CDeviceHolder* Create(const DeviceDesc& desc);

    /**
    * �J������
    */
    void Release();

    /**
    * DirectX9�f�o�C�X�擾
    * @ret Direct9�f�o�C�X
    */
    LPDIRECT3DDEVICE9 GetDevice() const;

    /**
    * �o�b�N�o�b�t�@�����擾
    * @ret �o�b�N�o�b�t�@����
    */
    DWORD GetBackBufferWidth() const;

    /**
    * �o�b�N�o�b�t�@�c���擾
    * @ret �o�b�N�o�b�t�@�c��
    */
    DWORD GetBackBufferHeight() const;

    /**
    * �f�o�C�X���擾
    * @ret �f�o�C�X���
    */
    const D3DPRESENT_PARAMETERS& GetPresentParameters() const;

    /**
    * �f�o�C�X���Z�b�g
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT Reset();

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    * @param desc �f�o�C�X���
    */
    HRESULT Init(const DeviceDesc& desc);

private:

    // �f�o�C�X
    LPDIRECT3DDEVICE9 m_pDev;

    // �o�b�N�o�b�t�@�T�C�Y
    DWORD m_uBackBufferWidth;
    DWORD m_uBackBufferHeight;

    // �f�o�C�X�p�����[�^
    D3DPRESENT_PARAMETERS m_PresentParam;
};

#endif  // __DEVICE_HOLDER_H__

// EOF
