//=============================================================================
//
// �A�v���P�[�V�����̓Ǝ��ݒ�
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <common/common.h>
#include <string>
#include <framework.h>

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class AppDelegate
    : public CApplication
{
public:

    AppDelegate();
    virtual ~AppDelegate();

    virtual bool Init();

    virtual void Release();

private:

};

#endif  // __APP_DELEGATE_H__

// EOF
