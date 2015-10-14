//=============================================================================
//
// サウンド
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CSound.h"
#include <common/DebugUtil.h>
#include "SoundDef.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSound::CSound()
    : m_pSourceVoice(nullptr)
    , m_pDataAudio(nullptr)
    , m_uSizeAudio(0)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSound::~CSound()
{
    if(m_pSourceVoice)
    {
        m_pSourceVoice->Stop(0);
        // ソースボイス破棄
        m_pSourceVoice->DestroyVoice();
        m_pSourceVoice = nullptr;
    }

    // オーディオデータ開放
    SafeDelete(m_pDataAudio);
}

//=============================================================================
// 生成
//=============================================================================
CSound* CSound::Create(cs8* pName, IXAudio2SubmixVoice* pSubMix, IXAudio2* pXAudio2)
{
    CSound* pSound = new CSound();

    if(pSound)
    {
        INIT_CHECK(pSound->Init(pName, pSubMix, pXAudio2));
        _PrintConsole("サウンド : %s\n", pName);
    }

    return pSound;
}

//=============================================================================
// 開放
//=============================================================================
void CSound::Release()
{
    delete this;
}

//=============================================================================
// 再生
//=============================================================================
void CSound::Play(bool bLoop)
{
    if(IS_NULL(m_pSourceVoice))
    {
        return;
    }

    // 状態取得
    // ボイスの現在の状態と位置(カーソル)の構造体
    XAUDIO2_VOICE_STATE xa2state;
    m_pSourceVoice->GetState(&xa2state);
    // 再生中
    if(xa2state.BuffersQueued != 0)
    {
        // 一時停止
        m_pSourceVoice->Stop(0);

        // オーディオバッファの削除
        m_pSourceVoice->FlushSourceBuffers();
    }

    // ループ設定
    m_Buffer.LoopCount    = bLoop ? XAUDIO2_LOOP_INFINITE : 0;
    // オーディオバッファの登録
    m_pSourceVoice->SubmitSourceBuffer(&m_Buffer);

    // 再生
    m_pSourceVoice->Start(0);
}

//=============================================================================
// 止める
//=============================================================================
void CSound::Stop()
{
    if(IS_NULL(m_pSourceVoice))
    {
        return;
    }

    // ボイスの現在の状態と位置(カーソル)の構造体
    XAUDIO2_VOICE_STATE xa2state;
    
    // 状態取得
    m_pSourceVoice->GetState(&xa2state);
    // 再生中
    if(xa2state.BuffersQueued != 0)
    {
        // 一時停止
        m_pSourceVoice->Stop(0);

        // オーディオバッファの削除
        m_pSourceVoice->FlushSourceBuffers();
    }
}

//=============================================================================
// 音量設定
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
// 音量取得
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
// 音量取得
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
// 初期化
//=============================================================================
HRESULT CSound::Init(cs8* pName, IXAudio2SubmixVoice* pSubMix, IXAudio2* pXAudio2)
{
    if(IS_NULL(pSubMix) || IS_NULL(pXAudio2))
    {
        return E_FAIL;
    }

    HRESULT hr = S_OK;

    HANDLE   hFile;             // ファイルハンドル
    DWORD    uChunkSize = 0;    // データチャンクサイズ
    DWORD    uChunkPosition = 0;// チャンクの開始場所
    DWORD    uFileType;         // ファイルタイプ
    WAVEFORMATEXTENSIBLE wfx;   // WAVEファイルフォーマット

    // バッファクリア
    memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));

    // サウンドデータファイルの生成
    hFile = CreateFile(
        pName,
        GENERIC_READ,        // 読み込み
        FILE_SHARE_READ,    // 共有読み込み
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
    // ハンドルの値が不正
    _AssertExpr(hFile != INVALID_HANDLE_VALUE, "サウンドデータファイルを開けません");
    if(hFile == INVALID_HANDLE_VALUE)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    // ファイルポインタを先頭に移動
    DWORD uSeekOK = SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
    _AssertExpr(uSeekOK != INVALID_SET_FILE_POINTER, "ファイルポインタ操作失敗");
    if(uSeekOK == INVALID_SET_FILE_POINTER)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    // WAVEファイルのチェック
    // 'RIFF'のASCIIコード列がビッグエンディアンで入っているはずなので
    hr = CheckChunk(hFile, 'FFIR', &uChunkSize, &uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "WAVEファイル読み込み失敗");
        return S_FALSE;
    }
    hr = ReadChunkData(hFile, &uFileType, sizeof(DWORD), uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "チャンクデータ読み込み失敗");
        return S_FALSE;
    }
    // 'WAVE'ASCIIコード列がビッグエンディアンで入っているはずなので
    if(uFileType != 'EVAW')
    {
        _AssertExpr(uFileType == 'EVAW', "WAVEファイルタイプがサポートされていません");
        return S_FALSE;
    }

    // フォーマットチェック
    hr = CheckChunk(hFile, ' tmf', &uChunkSize, &uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "ファイルフォーマットチェック失敗(1)");
        return S_FALSE;
    }
    hr = ReadChunkData(hFile, &wfx, uChunkSize, uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "ファイルフォーマットチェック失敗(2)");
        return S_FALSE;
    }
        
    // オーディオデータ読み込み
    hr = CheckChunk(hFile, 'atad', &m_uSizeAudio, &uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "オーディオデータ読み込み失敗(1)");
        return S_FALSE;
    }
    // オーディオデータ確保
    m_pDataAudio = new BYTE[m_uSizeAudio];
    hr = ReadChunkData(hFile, m_pDataAudio, m_uSizeAudio, uChunkPosition);
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "オーディオデータ読み込み失敗(2)");
        return S_FALSE;
    }

    // 出力先設定
    XAUDIO2_SEND_DESCRIPTOR send;
    send.Flags = 0;
    send.pOutputVoice = pSubMix;

    XAUDIO2_VOICE_SENDS sendlist;
    sendlist.SendCount = 1;
    sendlist.pSends = &send;

    // ソースボイス作成
    hr = pXAudio2->CreateSourceVoice(
        &m_pSourceVoice,            // ソースデータ
        &(wfx.Format),              // WAVEファイルフォーマット
        0,
        XAUDIO2_DEFAULT_FREQ_RATIO,
        NULL,
        &sendlist);                 // BGMサブミックスに送出
    if(FAILED(hr))
    {
        _AssertExpr(SUCCEEDED(hr), "BGMソースボイス生成失敗");
        return S_FALSE;
    }

    // バッファクリア
    memset(&m_Buffer, 0, sizeof(XAUDIO2_BUFFER));
    m_Buffer.AudioBytes   = m_uSizeAudio;
    m_Buffer.pAudioData   = m_pDataAudio;
    m_Buffer.Flags        = XAUDIO2_END_OF_STREAM;
    m_Buffer.LoopCount    = XAUDIO2_LOOP_INFINITE;    // とりあえず無限ループ

    // オーディオバッファの登録
    m_pSourceVoice->SubmitSourceBuffer(&m_Buffer);

    return hr;
}

//=============================================================================
// チャンクデータチェック
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD uFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
    HRESULT hr = S_OK;
    DWORD uRead;
    DWORD uChunkType;        // チャンクデータタイプ
    DWORD uChunkDataSize;    // チャンクデータサイズ
    DWORD uRIFFDataSize = 0;// RIFFデータサイズ
    DWORD uFileType;        // ファイルタイプ
    DWORD uBytesRead = 0;    //
    DWORD uOffset = 0;        //

    // ファイルポインタを先頭に移動
    if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    while(hr == S_OK)
    {
        // チャンク読み込み
        if(ReadFile(hFile, &uChunkType, sizeof(DWORD), &uRead, NULL) == 0)
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

        // チャンクデータ読み込み
        if(ReadFile(hFile, &uChunkDataSize, sizeof(DWORD), &uRead, NULL) == 0)
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

        // チャンクタイプによって分岐
        switch(uChunkType)
        {
        case 'FFIR':
            {
                uRIFFDataSize = uChunkDataSize;
                uChunkDataSize = 4;
                // ファイルタイプ読み込み
                if(ReadFile(hFile, &uFileType, sizeof(DWORD), &uRead, NULL) == 0)
                {
                    hr = HRESULT_FROM_WIN32(GetLastError());
                }
            }
            break;

        default:
            {
                // ファイルデータをチャンク分移動
                if(SetFilePointer(hFile, uChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
                {
                    return HRESULT_FROM_WIN32(GetLastError());
                }
            }
            break;
        }

        // 識別子(RIFF)チャンクデータサイズのバイト分移動
        uOffset += sizeof(DWORD) * 2;
        if(uChunkType == uFormat)
        {
            *pChunkSize            = uChunkDataSize;
            *pChunkDataPosition    = uOffset;

            return S_OK;
        }

        // チャンクデータ(fmt,data,etc.)サイズ分移動
        uOffset += uChunkDataSize;
        if(uBytesRead >= uRIFFDataSize)
        {
            return S_FALSE;
        }
    }

    return S_OK;
}

//=============================================================================
// チャンクデータ読み込み
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD uBufferSize, DWORD uBufferOffset)
{
    DWORD uRead;

    // ファイルポインタを(先頭から)指定位置まで移動
    if(SetFilePointer(hFile, uBufferOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    // データの読み込み
    if(ReadFile(hFile, pBuffer, uBufferSize, &uRead, NULL) == 0)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}

// EOF
