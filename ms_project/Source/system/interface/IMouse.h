//=============================================================================
//
// �}�E�X�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __MOUSE_INTERFACE_H__
#define __MOUSE_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include "common.h"

//*****************************************************************************
// �}�E�X�{�^����`
//*****************************************************************************
enum MouseButton
{
    BTN_LEFT = 0,
    BTN_RIGHT,
    BTN_CENTER
};

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
class IMouse
{
public:

    /**
    * ���W�擾
    * @ret ���W
    */
    virtual const POINT& GetPosition() const = 0;

    /**
    * �ړ��ʎ擾
    * @ret �ړ���
    */
    virtual const POINT& GetMove() const = 0;
    
    /**
    * �X�N���[���ʎ擾
    * @ret �X�N���[����
    */
    virtual LONG GetScroll(void) const = 0;
    
    /**
    * �v���X��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    virtual bool GetPress(MouseButton btn) const = 0;

    /**
    * �g���K�[��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    virtual bool GetTrigger(MouseButton btn) const = 0;

    /**
    * �����[�X��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    virtual bool GetRelease(MouseButton btn) const = 0;

    /**
    * ���s�[�g��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    virtual bool GetRepeat(MouseButton btn) const = 0;

protected:

    virtual ~IMouse(){}
};


#endif  // __MOUSE_INTERFACE_H__

// EOF
