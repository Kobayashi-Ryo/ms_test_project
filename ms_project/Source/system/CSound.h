//=============================================================================
//
// �T�E���h
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SOUND_H__
#define __SOUND_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <XAudio2.h>
#include "common.h"

//*****************************************************************************
// �T�E���h
//*****************************************************************************
class CSound
    : private CUncopyable
{
private:

    /**
    * �R���X�g���N�^
    */
    CSound();

    /**
    * �f�X�g���N�^
    */
    ~CSound();

public:

    /**
    * ����
    * @ret �T�E���h
    * @param �ǂݍ��މ�
    * @param �o�^��T�u�~�b�N�X�{�C�X
    * @param XAudio2�I�u�W�F�N�g
    */
    static CSound* Create(cs8* pName, IXAudio2SubmixVoice* pSubMix, IXAudio2* pXAudio2);

    /**
    * �J��
    */
    void Release();

    /**
    * �Đ�
    * @param ���[�v�t���O
    */
    void Play(bool bLoop);

    /**
    * �~�߂�
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

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    * @param �ǂݍ��މ�
    * @param �o�^��T�u�~�b�N�X�{�C�X
    * @param XAudio2�I�u�W�F�N�g
    */
    HRESULT Init(cs8* pName, IXAudio2SubmixVoice* pSubMix, IXAudio2* pXAudio2);

    /**
    * �`�����N�f�[�^�`�F�b�N
    * @ret S_OK:���Ȃ� E_FAIL:�ُ�
    */
    HRESULT CheckChunk(HANDLE hFile, DWORD uFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);

    /**
    * �`�����N�f�[�^�ǂݍ���
    * @ret S_OK:���Ȃ� E_FAIL:�ُ�
    */
    HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD uBufferSize, DWORD uBufferOffset);

private:

    IXAudio2SourceVoice*    m_pSourceVoice; // �\�[�X�{�C�X
    BYTE*                   m_pDataAudio;   // �I�[�f�B�I�f�[�^
    DWORD                   m_uSizeAudio;   // �I�[�f�B�I�f�[�^�T�C�Y

    XAUDIO2_BUFFER          m_Buffer;       // �I�[�f�B�I�o�b�t�@���
};

#endif  // __SOUND_H__

// EOF
