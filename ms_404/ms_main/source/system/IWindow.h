//=============================================================================
//
// �E�B���h�E�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INTERFACE_WINDOW_H__
#define __INTERFACE_WINDOW_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <string>

//*****************************************************************************
// �E�B���h�E�C���^�[�t�F�[�X
//*****************************************************************************
class IWindow
{
public:

    /**
    * �E�B���h�E�����擾
    * @ret �E�B���h�E����
    */
    virtual DWORD GetWidth() const = 0;
    
    /**
    * �E�B���h�E�c���擾
    * @ret �E�B���h�E�c��
    */
    virtual DWORD GetHeight() const = 0;
    
    /**
    * �E�B���h�E�n���h���擾
    * @ret �E�B���h�E�n���h��
    */
    virtual HWND GetHandle() const = 0;
    
    /**
    * �L���v�V�����ݒ�
    * @param strCaption �ݒ肷��L���v�V����
    */
    virtual void SetCaption(const std::string& strCaption) = 0;

protected:

    /**
    * �f�X�g���N�^
    */
    virtual ~IWindow(){}
};

#endif  // __INTERFACE_WINDOW_H__

// EOF
