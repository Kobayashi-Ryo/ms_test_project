//=============================================================================
//
// �T�E���h�}�l�[�W���[
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <XAudio2.h>
#include <common/common.h>

#include "../ISound.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CSubMix;

//*****************************************************************************
// �T�E���h�}�l�[�W���[
//*****************************************************************************
class CSoundManager
    : private CUncopyable
    , public ISound
{
private:

    /**
    * �R���X�g���N�^
    */
    CSoundManager();

    /**
    * �f�X�g���N�^
    */
    ~CSoundManager();

public:

    /**
    * ����
    * @ret �T�E���h�}�l�[�W���[
    */
    static CSoundManager* Create();

    /**
    * �J��
    */
    void Release();


    /**
    * BGM�Đ�
    * @param pName �t�@�C����
    * @param bLoop ���[�v�t���O
    */
    void PlayBGM(cs8* pName, bool bLoop = true);

    /**
    * SE�Đ�
    * @param pName �t�@�C����
    * @param bLoop ���[�v�t���O
    */
    void PlaySE(cs8* pName, bool bLoop = false);

    /**
    * BGM���~�߂�
    * @param pName �~�߂�����
    */
    void StopBGM(cs8* pName);

    /**
    * BGM���~�߂�
    */
    void StopBGM();

    /**
    * SE���~�߂�
    * @param pName �~�߂�����
    */
    void StopSE(cs8* pName);
    
    /**
    * SE���~�߂�
    */
    void StopSE();

    /**
    * ���ׂẲ����~�߂�
    */
    void Stop();

    /**
    * BGM�v�����[�h
    * @param pName ���[�h��������
    */
    void LoadBGM(cs8* pName);

    /**
    * SE�v�����[�h
    * @param pName ���[�h��������
    */
    void LoadSE(cs8* pName);

    /**
    * BGM���ʐݒ�
    * @param nVolume 0~100�ŉ��ʎw��
    */
    void SetVolumeBGM(cs32 nVolume);

    /**
    * SE���ʐݒ�
    * @param nVolume 0~100�ŉ��ʎw��
    */
    void SetVolumeSE(cs32 nVolume);

    /**
    * BGM���ʎ擾
    * @ret 0~100
    */
    s32 GetVolumeBGM();

    /**
    * SE���ʎ擾
    * @param 0~100
    */
    s32 GetVolumeSE();

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT Init();

private:

    // XAudio�I�u�W�F�N�g
    IXAudio2* m_pXAudio2;
    // �}�X�^�[�{�C�X
    IXAudio2MasteringVoice  *m_pMasteringVoice;

    // BGM
    CSubMix* m_pBGM;
    // SE
    CSubMix* m_pSE;
};

#endif  // __SOUND_MANAGER_H__

// EOF
