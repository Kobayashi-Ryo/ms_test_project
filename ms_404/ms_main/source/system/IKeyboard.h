//=============================================================================
//
// �L�[�{�[�h�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __KEYBOARD_INTERFACE_H__
#define __KEYBOARD_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <Windows.h>
#include <common/common.h>

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
class IKeyboard
{
public:

    /**
    * �v���X��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    virtual bool GetPress(u8 key) const = 0;

    /**
    * �g���K�[��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    virtual bool GetTrigger(u8 key) const = 0;

    /**
    * �����[�X��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    virtual bool GetRelease(u8 key) const = 0;

    /**
    * ���s�[�g��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    virtual bool GetRepeat(u8 key) const = 0;

protected:

    virtual ~IKeyboard(){}
};


#endif  // __KEYBOARD_INTERFACE_H__

// EOF
