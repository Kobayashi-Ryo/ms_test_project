//=============================================================================
//
// サウンドカテゴリーごとの設定
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SUB_MIX_H__
#define __SUB_MIX_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <XAudio2.h>
#include <map>
#include <string>
#include "common.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CSound;

//*****************************************************************************
// サブミックスクラス
//*****************************************************************************
class CSubMix
    : private CUncopyable
{
private:

    /**
    * コンストラクタ
    * @param strPath ファイルパス
    */
    CSubMix(const std::string& strPath);

    /**
    * デストラクタ
    */
    ~CSubMix();

public:

    /**
    * 生成
    * @ret サブミックス
    * @param pXAudio2 XAudio2オブジェクト
    */
    static CSubMix* Create(const std::string& strPath, IXAudio2* pXAudio2);

    /**
    * 開放
    */
    void Release();

    /**
    * 再生
    * @param ループフラグ
    */
    void Play(cs8* pName, bool bLoop);

    /**
    * 止める
    * @param pName 止めたい音
    */
    void Stop(cs8* pName);

    /**
    * すべての音を止める
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

    /**
    * プリロード
    * @param pName ロードしたい音
    */
    void Load(cs8* pName);

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    * @param XAudio2オブジェクト
    */
    HRESULT Init(IXAudio2* pXAudio2);

private:

    // XAudio2オブジェクト
    IXAudio2*               m_pXAudio2;
    // サブミックスボイス
    IXAudio2SubmixVoice     *m_pSubMix;

    // サウンドリソース
    std::map<std::string, CSound*> m_mapSound;

    // ファイルパス
    const std::string m_strFilePath;
};

#endif  // __SUB_MIX_H__

// EOF
