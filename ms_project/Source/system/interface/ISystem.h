//=============================================================================
//
// �V�X�e���C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INTERFACE_SYSTEM_H__
#define __INTERFACE_SYSTEM_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
// interface
#include "IWindow.h"
#include "IDeviceHolder.h"
#include "ISound.h"
#include "IInputManager.h"
#include "IDebug.h"
#include "IResource.h"

//*****************************************************************************
// �V�X�e���C���^�[�t�F�[�X
//*****************************************************************************
class ISystem
{
protected:

    typedef LRESULT WND_PROC_HOOK(HWND, UINT, WPARAM, LPARAM);

public:

    /**
    * �E�B���h�E�擾
    * @ret �E�B���h�E�C���^�[�t�F�[�X
    */
    virtual IWindow* GetWindow() const = 0;

    /**
    * �f�o�C�X�z���_�[�擾
    * @ret �f�o�C�X�z���_�[�C���^�[�t�F�[�X
    */
    virtual IDeviceHolder* GetDeviceHolder() const = 0;

    /**
    * �T�E���h�擾
    * @ret �T�E���h�C���^�[�t�F�[�X
    */
    virtual ISound* GetSound() const = 0;

    /**
    * ���̓}�l�[�W���擾
    * @ret ���̓}�l�[�W���C���^�[�t�F�[�X
    */
    virtual IInputManager* GetInputManager() const = 0;

    /**
    * �f�o�b�O�擾
    * @ret �f�o�b�O�C���^�[�t�F�[�X
    */
    virtual IDebug* GetDebug() const = 0;

    /**
    * ���\�[�X�擾
    * @ret ���\�[�X�C���^�[�t�F�[�X
    */
    virtual IResource* GetResource() const = 0;

    /**
    * �擾
    * @ret �C���^�[�t�F�[�X
    */

    /**
    * �����I��
    */
    virtual void Abort() = 0;
    
    /**
    * �E�B���h�E�v���V�[�W���t�b�N�ݒ�
    * @param hook �t�b�N�֐�
    */
    virtual void SetWndProcHook(WND_PROC_HOOK hook) = 0;

protected:

    /**
    * �f�X�g���N�^
    */
    virtual ~ISystem(){}
};

#endif  // __INTERFACE_SYSTEM_H__

// EOF
