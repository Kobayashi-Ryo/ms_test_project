//=============================================================================
//
// �T�E���h�J�e�S���[���Ƃ̐ݒ�
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SUB_MIX_H__
#define __SUB_MIX_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <XAudio2.h>
#include <map>
#include <string>
#include "common.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CSound;

//*****************************************************************************
// �T�u�~�b�N�X�N���X
//*****************************************************************************
class CSubMix
    : private CUncopyable
{
private:

    /**
    * �R���X�g���N�^
    * @param strPath �t�@�C���p�X
    */
    CSubMix(const std::string& strPath);

    /**
    * �f�X�g���N�^
    */
    ~CSubMix();

public:

    /**
    * ����
    * @ret �T�u�~�b�N�X
    * @param pXAudio2 XAudio2�I�u�W�F�N�g
    */
    static CSubMix* Create(const std::string& strPath, IXAudio2* pXAudio2);

    /**
    * �J��
    */
    void Release();

    /**
    * �Đ�
    * @param ���[�v�t���O
    */
    void Play(cs8* pName, bool bLoop);

    /**
    * �~�߂�
    * @param pName �~�߂�����
    */
    void Stop(cs8* pName);

    /**
    * ���ׂẲ����~�߂�
    */
    void Stop();

    /**
    * ���ʐݒ�
    * @param nVolume 0~100�̃{�����[��
    */
    void SetVolume(s32 nVolume);

    /**
    * ���ʎ擾
    * @ret ���� 0~100
    */
    s32 GetVolumei() const;

    /**
    * ���ʎ擾
    * @ret ���� 0~1
    */
    f32 GetVolumef() const;

    /**
    * �v�����[�h
    * @param pName ���[�h��������
    */
    void Load(cs8* pName);

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    * @param XAudio2�I�u�W�F�N�g
    */
    HRESULT Init(IXAudio2* pXAudio2);

private:

    // XAudio2�I�u�W�F�N�g
    IXAudio2*               m_pXAudio2;
    // �T�u�~�b�N�X�{�C�X
    IXAudio2SubmixVoice     *m_pSubMix;

    // �T�E���h���\�[�X
    std::map<std::string, CSound*> m_mapSound;

    // �t�@�C���p�X
    const std::string m_strFilePath;
};

#endif  // __SUB_MIX_H__

// EOF
