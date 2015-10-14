//=============================================================================
//
// サウンドマネージャー
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <XAudio2.h>
#include <common/common.h>

#include "../ISound.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CSubMix;

//*****************************************************************************
// サウンドマネージャー
//*****************************************************************************
class CSoundManager
    : private CUncopyable
    , public ISound
{
private:

    /**
    * コンストラクタ
    */
    CSoundManager();

    /**
    * デストラクタ
    */
    ~CSoundManager();

public:

    /**
    * 生成
    * @ret サウンドマネージャー
    */
    static CSoundManager* Create();

    /**
    * 開放
    */
    void Release();


    /**
    * BGM再生
    * @param pName ファイル名
    * @param bLoop ループフラグ
    */
    void PlayBGM(cs8* pName, bool bLoop = true);

    /**
    * SE再生
    * @param pName ファイル名
    * @param bLoop ループフラグ
    */
    void PlaySE(cs8* pName, bool bLoop = false);

    /**
    * BGMを止める
    * @param pName 止めたい音
    */
    void StopBGM(cs8* pName);

    /**
    * BGMを止める
    */
    void StopBGM();

    /**
    * SEを止める
    * @param pName 止めたい音
    */
    void StopSE(cs8* pName);
    
    /**
    * SEを止める
    */
    void StopSE();

    /**
    * すべての音を止める
    */
    void Stop();

    /**
    * BGMプリロード
    * @param pName ロードしたい音
    */
    void LoadBGM(cs8* pName);

    /**
    * SEプリロード
    * @param pName ロードしたい音
    */
    void LoadSE(cs8* pName);

    /**
    * BGM音量設定
    * @param nVolume 0~100で音量指定
    */
    void SetVolumeBGM(cs32 nVolume);

    /**
    * SE音量設定
    * @param nVolume 0~100で音量指定
    */
    void SetVolumeSE(cs32 nVolume);

    /**
    * BGM音量取得
    * @ret 0~100
    */
    s32 GetVolumeBGM();

    /**
    * SE音量取得
    * @param 0~100
    */
    s32 GetVolumeSE();

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT Init();

private:

    // XAudioオブジェクト
    IXAudio2* m_pXAudio2;
    // マスターボイス
    IXAudio2MasteringVoice  *m_pMasteringVoice;

    // BGM
    CSubMix* m_pBGM;
    // SE
    CSubMix* m_pSE;
};

#endif  // __SOUND_MANAGER_H__

// EOF
