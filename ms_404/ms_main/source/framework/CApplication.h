//=============================================================================
//
// �A�v���P�[�V����
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __MS_APPLICATION_H__
#define __MS_APPLICATION_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <common/common.h>

// system interface
#include <system/ISystem.h>

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CSystem;
class CScene;
class CHardwareTimer;

//*****************************************************************************
// �A�v���P�[�V�����N���X
//*****************************************************************************
class CApplication
    : private CUncopyable
{
protected:

    CApplication();

    virtual ~CApplication();

public:

    virtual bool Init() = 0;

    virtual void Release() = 0;

    /**
    * �A�v���P�[�V�������I��������
    */
    void Finish();

    /**
    * �V�X�e���̎擾
    * @ret �V�X�e���C���^�[�t�F�[�X
    */
    ISystem* GetSystem();

    /**
    * ���݂̃V�[���擾
    * @ret �V�X�e���C���^�[�t�F�[�X
    */
    CScene* GetCurrentScene();
    
    /**
    * �A�v���P�[�V�����J�n
    * @ret ���^�[���R�[�h
    */
    s32 Run();

    /**
    * �V�[����ʂ̃V�[���Œu������
    * @param pScene �u�����������V�[��
    */
    void ReplaceScene(CScene* pScene);

    /**
    * �A�v���P�[�V�����C���X�^���X�擾
    * @ret �A�v���P�[�V�����C���X�^���X
    */
    static CApplication* GetInstance();
    
private:

    // �V�X�e���C���^�[�t�F�[�X
    CSystem* m_pSystem;

    // �A�v���P�[�V�����N���t���O
    bool m_bIsRunning;

    // ���݂̃V�[��
    CScene* m_pCurrentScene;
    
    // �n�[�h�E�F�A�^�C�}�[
    CHardwareTimer* m_pHardwareTimer;

    // �A�v���P�[�V����
    static CApplication* m_spApp;
};

#endif  // __MS_APPLICATION_H__

// EOF
