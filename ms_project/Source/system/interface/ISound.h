//=============================================================================
//
// サウンドインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SOUND_INTERFACE_H__
#define __SOUND_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include "common.h"

//*****************************************************************************
// サウンドインターフェース
//*****************************************************************************
class ISound
{
public:

    /**
    * BGM再生
    * @param pName ファイル名
    * @param bLoop ループフラグ
    */
    virtual void PlayBGM(cs8* pName, bool bLoop = true) = 0;

    /**
    * SE再生
    * @param pName ファイル名
    * @param bLoop ループフラグ
    */
    virtual void PlaySE(cs8* pName, bool bLoop = false) = 0;

    /**
    * BGMを止める
    * @param pName 止めたい音
    */
    virtual void StopBGM(cs8* pName) = 0;

    /**
    * BGMを止める
    */
    virtual void StopBGM() = 0;

    /**
    * SEを止める
    * @param pName 止めたい音
    */
    virtual void StopSE(cs8* pName) = 0;

    /**
    * SEを止める
    */
    virtual void StopSE() = 0;

    /**
    * すべての音を止める
    */
    virtual void Stop() = 0;

    /**
    * BGMプリロード
    * @param pName ロードしたい音
    */
    virtual void LoadBGM(cs8* pName) = 0;

    /**
    * SEプリロード
    * @param pName ロードしたい音
    */
    virtual void LoadSE(cs8* pName) = 0;

    /**
    * BGM音量設定
    * @param nVolume 0~100で音量指定
    */
    virtual void SetVolumeBGM(cs32 nVolume) = 0;

    /**
    * SE音量設定
    * @param nVolume 0~100で音量指定
    */
    virtual void SetVolumeSE(cs32 nVolume) = 0;

    /**
    * BGM音量取得
    * @ret 0~100
    */
    virtual s32 GetVolumeBGM() = 0;

    /**
    * SE音量取得
    * @param 0~100
    */
    virtual s32 GetVolumeSE() = 0;

protected:

    virtual ~ISound(){}
};

#endif  // __SOUND_INTERFACE_H__

// EOF
