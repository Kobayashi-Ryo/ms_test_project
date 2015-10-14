//=============================================================================
//
// �T�E���h
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CSound.h"
#include <common/DebugUtil.h>
#include "SoundDef.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSound::CSound()
    : m_pSourceVoice(nullptr)
    , m_pDataAudio(nullptr)
    , m_uSizeAudio(0)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSound::~CSound()
{
    if(m_pSourceVoice)
    {
        m_pSourceVoice->Stop(0);
        // �\�[�X�{�C�X�j��
        m_pSourceVoice->DestroyVoice();
        m_pSourceVoice = nullptr;
    }

    // �I�[�f�B�I�f�[�^�J��
    SafeDelete(m_pDataAudio);
}

//=============================================================================
// ����
//=============================================================================
CSound* CSound::Create(cs8* pName, IXAudio2SubmixVoice* pSubMix, IXAudio2* pXAudio2)
{
    CSound* pSound = new CSound();

    if(pSound)
    {
        INIT_CHECK(pSound->Init(pName, pSubMix, pXAudio2));
        _PrintConsole("�T�E���h : %s\n", pName);
    }

    return pSound;
}

//=============================================================================
// �J��
//=============================================================================
void CSound::Release()
{
    delete this;
}

//=============================================================================
// �Đ�
//=============================================================================
void CSound::Play(bool bLoop)
{
    if(IS_NULL(m_pSourceVoice))
    {
        return;
    }

    // ��Ԏ擾
    // �{�C�X�̌��݂̏�Ԃƈʒu(�J�[�\��)�̍\����
    XAUDIO2_VOICE_STATE xa2state;
    m_pSourceVoice->GetState(&xa2state);
    // �Đ���
    if(xa2state.BuffersQueued != 0)
    {
        // �ꎞ��~
        m_pSourceVoice->Stop(0);

        // �I�[�f�B�I�o�b�t�@�̍폜
        m_pSourceVoice->FlushSourceBuffers();
    }

    // ���[�v�ݒ�
    m_Buffer.LoopCount    = bLoop ? XAUDIO2_LOOP_INFINITE : 0;
    // �I�[�f�B�I�o�b�t�@�̓o�^
    m_pSourceVoice->SubmitSourceBuffer(&m_Buffer);

    // �Đ�
    m_pSourceVoice->Start(0);
}

//=============================================================================
// �~�߂�
//=============================================================================
void CSound::Stop()
{
    if(IS_NULL(m_pSourceVoice))
    {
        return;
    }

    // �{�C�X�̌��݂̏�Ԃƈʒu(�J�[�\��)�̍\����
    XAUDIO2_VOICE_STATE xa2state;
    
    // ��Ԏ擾
    m_pSourceVoice->GetState(&xa2state);
    // �Đ���
    if(xa2state.BuffersQueued != 0)
    {
        // �ꎞ��~
        m_pSourceVoice->Stop(0);

        // �I�[�f�B�I�o�b�t�@�̍폜
        m_pSourceVoice->FlushSourceBuffers();
    }
}

//=============================================================================
// ���ʐݒ�
//=============================================================================
void CSound::SetVolume(s32 nVolume)
{
    if(IS_NULL(m_pSourceVoice))
    {
        return;
    }

    if(nVolume < 0) nVolume = 0;
    else if(nVolume > 100) nVolume = 100;
    m_pSourceVoice->SetVolume(nVolume / VOLUME_SCALE);
}

//=============================================================================
// ���ʎ擾
//=============================================================================
s32 CSound::GetVolumei() const
{
    if(IS_NULL(m_pSourceVoice))
    {
        return 0;
    }

    f32 fVol = 0.0f;
    m_pSourceVoice->GetVolume(&fVol);
    return (s32)(fVol * VOLUME_SCALE);
}

//=============================================================================
// ���ʎ擾
//=============================================================================
f32 CSound::GetVolumef() const
{
    if(IS_NULL(m_pSourceVoice))
    {
        return 0;
    }

    f32 fVol = 0.0f;
    m_pSourceVoice->GetVolume(&fVol);
    return fVol;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CSound::Init(cs8* pName, IXAudio2SubmixVoice* pSubMix, IXAudio2* pXAudio2)
{
    if(IS_NULL(pSubMix) || IS_NULL(pXAudio2))
    {
        return E_FAIL;
    }

    HRESULT hr = S_OK;

    HANDLE   hFile;             // �t�@�C���n���h��
    DWORD    uChunkSize = 0;    // �f�[�^�`�����N�T�C�Y
    DWORD    uChunkPosition = 0;// �`�����N�̊J�n�ꏊ
    DWORD    uFileType;         // �t�@�C���^�C�v
    WAVEFORMATEXTENSIBLE wfx;   // WAVE�t�@�C���t�H�[�}�b�g

    // �o�b�t�@�N���A
    memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));

    // �T�E���h�f�[�^�t�@�C���̐���
    hFile = CreateFile(
        pName,
        GENERIC_READ,        // �ǂݍ���
        FILE_SHARE_READ,    // ���L�ǂݍ���
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
    // �n���h���̒l���s��
    _AssertExpr(hFile != INVALID_HANDLE_VALUE, "�T�E���h�f�[�^�t�@�C�����J���܂���");
    if(hFile == INVALID_HANDLE_VALUE)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    // �t�@�C���|�C���^��擪�Ɉړ�
    DWORD uSeekOK = SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
    _AssertExpr(uSeekOK != INVALID_SET_FILE_POINTER, "�t�@�C���|�C���^���쎸�s");
    if(uSeekOK == INVALID_SET_FILE_POINTER)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    // WAVE�t�@�C���̃`�F�b�N
    // 'RIFF'��ASCII�R�[�h�񂪃r�b�O�G���f�B�A���œ����Ă���͂��Ȃ̂�
    hr = CheckChunk(hFile, 'FFIR', &uChunkSize, &uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "WAVE�t�@�C���ǂݍ��ݎ��s");
        return S_FALSE;
    }
    hr = ReadChunkData(hFile, &uFileType, sizeof(DWORD), uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "�`�����N�f�[�^�ǂݍ��ݎ��s");
        return S_FALSE;
    }
    // 'WAVE'ASCII�R�[�h�񂪃r�b�O�G���f�B�A���œ����Ă���͂��Ȃ̂�
    if(uFileType != 'EVAW')
    {
        _AssertExpr(uFileType == 'EVAW', "WAVE�t�@�C���^�C�v���T�|�[�g����Ă��܂���");
        return S_FALSE;
    }

    // �t�H�[�}�b�g�`�F�b�N
    hr = CheckChunk(hFile, ' tmf', &uChunkSize, &uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "�t�@�C���t�H�[�}�b�g�`�F�b�N���s(1)");
        return S_FALSE;
    }
    hr = ReadChunkData(hFile, &wfx, uChunkSize, uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "�t�@�C���t�H�[�}�b�g�`�F�b�N���s(2)");
        return S_FALSE;
    }
        
    // �I�[�f�B�I�f�[�^�ǂݍ���
    hr = CheckChunk(hFile, 'atad', &m_uSizeAudio, &uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "�I�[�f�B�I�f�[�^�ǂݍ��ݎ��s(1)");
        return S_FALSE;
    }
    // �I�[�f�B�I�f�[�^�m��
    m_pDataAudio = new BYTE[m_uSizeAudio];
    hr = ReadChunkData(hFile, m_pDataAudio, m_uSizeAudio, uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "�I�[�f�B�I�f�[�^�ǂݍ��ݎ��s(2)");
        return S_FALSE;
    }

    // �o�͐�ݒ�
    XAUDIO2_SEND_DESCRIPTOR send;
    send.Flags = 0;
    send.pOutputVoice = pSubMix;

    XAUDIO2_VOICE_SENDS sendlist;
    sendlist.SendCount = 1;
    sendlist.pSends = &send;

    // �\�[�X�{�C�X�쐬
    hr = pXAudio2->CreateSourceVoice(
        &m_pSourceVoice,            // �\�[�X�f�[�^
        &(wfx.Format),              // WAVE�t�@�C���t�H�[�}�b�g
        0,
        XAUDIO2_DEFAULT_FREQ_RATIO,
        NULL,
        &sendlist);                 // BGM�T�u�~�b�N�X�ɑ��o
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "BGM�\�[�X�{�C�X�������s");
        return S_FALSE;
    }

    // �o�b�t�@�N���A
    memset(&m_Buffer, 0, sizeof(XAUDIO2_BUFFER));
    m_Buffer.AudioBytes   = m_uSizeAudio;
    m_Buffer.pAudioData   = m_pDataAudio;
    m_Buffer.Flags        = XAUDIO2_END_OF_STREAM;
    m_Buffer.LoopCount    = XAUDIO2_LOOP_INFINITE;    // �Ƃ肠�����������[�v

    // �I�[�f�B�I�o�b�t�@�̓o�^
    m_pSourceVoice->SubmitSourceBuffer(&m_Buffer);

    return hr;
}

//=============================================================================
// �`�����N�f�[�^�`�F�b�N
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD uFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
    HRESULT hr = S_OK;
    DWORD uRead;
    DWORD uChunkType;        // �`�����N�f�[�^�^�C�v
    DWORD uChunkDataSize;    // �`�����N�f�[�^�T�C�Y
    DWORD uRIFFDataSize = 0;// RIFF�f�[�^�T�C�Y
    DWORD uFileType;        // �t�@�C���^�C�v
    DWORD uBytesRead = 0;    //
    DWORD uOffset = 0;        //

    // �t�@�C���|�C���^��擪�Ɉړ�
    if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    while(hr == S_OK)
    {
        // �`�����N�ǂݍ���
        if(ReadFile(hFile, &uChunkType, sizeof(DWORD), &uRead, NULL) == 0)
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

        // �`�����N�f�[�^�ǂݍ���
        if(ReadFile(hFile, &uChunkDataSize, sizeof(DWORD), &uRead, NULL) == 0)
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

        // �`�����N�^�C�v�ɂ���ĕ���
        switch(uChunkType)
        {
        case 'FFIR':
            {
                uRIFFDataSize = uChunkDataSize;
                uChunkDataSize = 4;
                // �t�@�C���^�C�v�ǂݍ���
                if(ReadFile(hFile, &uFileType, sizeof(DWORD), &uRead, NULL) == 0)
                {
                    hr = HRESULT_FROM_WIN32(GetLastError());
                }
            }
            break;

        default:
            {
                // �t�@�C���f�[�^���`�����N���ړ�
                if(SetFilePointer(hFile, uChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
                {
                    return HRESULT_FROM_WIN32(GetLastError());
                }
            }
            break;
        }

        // ���ʎq(RIFF)�`�����N�f�[�^�T�C�Y�̃o�C�g���ړ�
        uOffset += sizeof(DWORD) * 2;
        if(uChunkType == uFormat)
        {
            *pChunkSize            = uChunkDataSize;
            *pChunkDataPosition    = uOffset;

            return S_OK;
        }

        // �`�����N�f�[�^(fmt,data,etc.)�T�C�Y���ړ�
        uOffset += uChunkDataSize;
        if(uBytesRead >= uRIFFDataSize)
        {
            return S_FALSE;
        }
    }

    return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�ǂݍ���
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD uBufferSize, DWORD uBufferOffset)
{
    DWORD uRead;

    // �t�@�C���|�C���^��(�擪����)�w��ʒu�܂ňړ�
    if(SetFilePointer(hFile, uBufferOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    // �f�[�^�̓ǂݍ���
    if(ReadFile(hFile, pBuffer, uBufferSize, &uRead, NULL) == 0)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}

// EOF
