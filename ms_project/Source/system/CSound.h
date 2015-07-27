//=============================================================================
//
// サウンド
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SOUND_H__
#define __SOUND_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <XAudio2.h>
#include "common.h"

//*****************************************************************************
// サウンド
//*****************************************************************************
class CSound
    : private CUncopyable
{
private:

    /**
    * コンストラクタ
    */
    CSound();

    /**
    * デストラクタ
    */
    ~CSound();

public:

    /**
    * 生成
    * @ret サウンド
    * @param 読み込む音
    * @param 登録先サブミックスボイス
    * @param XAudio2オブジェクト
    */
    static CSound* Create(cs8* pName, IXAudio2SubmixVoice* pSubMix, IXAudio2* pXAudio2);

    /**
    * 開放
    */
    void Release();

    /**
    * 再生
    * @param ループフラグ
    */
    void Play(bool bLoop);

    /**
    * 止める
    */
    void Stop();

    /**
    * 音量設定
    * @param nVolume 0~100のボリューム
    */
    void SetVolume(s32 nVolume);

    /**
    * 音量取得
    * @ret 音量 0~100
    */
    s32 GetVolumei() const;

    /**
    * 音量取得
    * @ret 音量 0~1
    */
    f32 GetVolumef() const;

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    * @param 読み込む音
    * @param 登録先サブミックスボイス
    * @param XAudio2オブジェクト
    */
    HRESULT Init(cs8* pName, IXAudio2SubmixVoice* pSubMix, IXAudio2* pXAudio2);

    /**
    * チャンクデータチェック
    * @ret S_OK:問題なし E_FAIL:異常
    */
    HRESULT CheckChunk(HANDLE hFile, DWORD uFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);

    /**
    * チャンクデータ読み込み
    * @ret S_OK:問題なし E_FAIL:異常
    */
    HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD uBufferSize, DWORD uBufferOffset);

private:

    IXAudio2SourceVoice*    m_pSourceVoice; // ソースボイス
    BYTE*                   m_pDataAudio;   // オーディオデータ
    DWORD                   m_uSizeAudio;   // オーディオデータサイズ

    XAUDIO2_BUFFER          m_Buffer;       // オーディオバッファ情報
};

#endif  // __SOUND_H__

// EOF
