//=============================================================================
//
// �A�v���P�[�V����
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __MS_APP_H__
#define __MS_APP_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "common.h"

// system interface
#include "ISystem.h"

//*****************************************************************************
// �A�v���P�[�V�����N���X
//*****************************************************************************
class CApp
    : private CUncopyable
{
private:

    CApp(ISystem* pSystem);

    virtual ~CApp(){};

public:

    virtual void Release() = 0;

    virtual void Update() = 0;

    virtual void Draw() = 0;

    /**
    * �A�v���P�[�V�������I��������
    */
    void Finish();
    
    /**
    * �V�X�e���̎擾
    * @ret �V�X�e���C���^�[�t�F�[�X
    */
    ISystem* GetSystem();

private:

    // �V�X�e���C���^�[�t�F�[�X
    ISystem* m_pSystem;

    // �A�v���P�[�V�����N���t���O
    bool m_bIsRunning;
};

#endif  // __MS_APP_H__

// EOF
