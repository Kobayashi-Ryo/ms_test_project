//=============================================================================
//
// ���̓}�l�[�W���[�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INPUT_MANAGER_INTERFACE_H__
#define __INPUT_MANAGER_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "IKeyboard.h"
#include "IMouse.h"

//*****************************************************************************
// ���̓}�l�[�W���[�C���^�[�t�F�[�X
//*****************************************************************************
class IInputManager
{
public:

    /**
    * �L�[�{�[�h�擾
    * @ret �L�[�{�[�h
    */
    virtual IKeyboard* GetKeyboard() const = 0;

    /**
    * �}�E�X�擾
    * @ret �}�E�X
    */
    virtual IMouse* GetMouse() const = 0;

protected:

    virtual ~IInputManager(){}
};

#endif  // __INPUT_MANAGER_INTERFACE_H__

// EOF
