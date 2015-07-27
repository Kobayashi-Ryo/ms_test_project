//=============================================================================
//
// �T�E���h�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SOUND_INTERFACE_H__
#define __SOUND_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include "common.h"

//*****************************************************************************
// �T�E���h�C���^�[�t�F�[�X
//*****************************************************************************
class ISound
{
public:

    /**
    * BGM�Đ�
    * @param pName �t�@�C����
    * @param bLoop ���[�v�t���O
    */
    virtual void PlayBGM(cs8* pName, bool bLoop = true) = 0;

    /**
    * SE�Đ�
    * @param pName �t�@�C����
    * @param bLoop ���[�v�t���O
    */
    virtual void PlaySE(cs8* pName, bool bLoop = false) = 0;

    /**
    * BGM���~�߂�
    * @param pName �~�߂�����
    */
    virtual void StopBGM(cs8* pName) = 0;

    /**
    * BGM���~�߂�
    */
    virtual void StopBGM() = 0;

    /**
    * SE���~�߂�
    * @param pName �~�߂�����
    */
    virtual void StopSE(cs8* pName) = 0;

    /**
    * SE���~�߂�
    */
    virtual void StopSE() = 0;

    /**
    * ���ׂẲ����~�߂�
    */
    virtual void Stop() = 0;

    /**
    * BGM�v�����[�h
    * @param pName ���[�h��������
    */
    virtual void LoadBGM(cs8* pName) = 0;

    /**
    * SE�v�����[�h
    * @param pName ���[�h��������
    */
    virtual void LoadSE(cs8* pName) = 0;

    /**
    * BGM���ʐݒ�
    * @param nVolume 0~100�ŉ��ʎw��
    */
    virtual void SetVolumeBGM(cs32 nVolume) = 0;

    /**
    * SE���ʐݒ�
    * @param nVolume 0~100�ŉ��ʎw��
    */
    virtual void SetVolumeSE(cs32 nVolume) = 0;

    /**
    * BGM���ʎ擾
    * @ret 0~100
    */
    virtual s32 GetVolumeBGM() = 0;

    /**
    * SE���ʎ擾
    * @param 0~100
    */
    virtual s32 GetVolumeSE() = 0;

protected:

    virtual ~ISound(){}
};

#endif  // __SOUND_INTERFACE_H__

// EOF
