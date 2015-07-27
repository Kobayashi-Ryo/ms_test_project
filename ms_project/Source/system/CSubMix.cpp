//=============================================================================
//
// サウンドカテゴリーごとの設定
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CSubMix.h"
#include "SoundDef.h"
#include "CSound.h"
#include "DebugUtil.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSubMix::CSubMix(const std::string& strPath)
    : m_pSubMix(nullptr)
    , m_pXAudio2(nullptr)
    , m_strFilePath(strPath)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSubMix::~CSubMix()
{
    ReleaseVoice(m_pSubMix);

    // サウンドデータ開放
    for(auto it = m_mapSound.begin(); it != m_mapSound.end(); )
    {
        it->second->Release();
        m_mapSound.erase(it++);
    }
}

//=============================================================================
// 生成
//=============================================================================
CSubMix* CSubMix::Create(const std::string& strPath, IXAudio2* pXAudio2)
{
    CSubMix* pSub = new CSubMix(strPath);

    if(pSub)
    {
        INIT_CHECK(pSub->Init(pXAudio2));
        _PrintConsole("サブミックス\n");
    }

    return pSub;
}

//=============================================================================
// 開放
//=============================================================================
void CSubMix::Release()
{
    delete this;
}

//=============================================================================
// 再生
//=============================================================================
void CSubMix::Play(cs8* pName, bool bLoop)
{
    auto it = m_mapSound.find(pName);
    if(it == m_mapSound.end())
    {
        // 読み込み処理
        Load(pName);
        it = m_mapSound.find(pName);
        if(it == m_mapSound.end())
        {
            return;
        }
    }

    it->second->Play(bLoop);
}

//=============================================================================
// 止める
//=============================================================================
void CSubMix::Stop(cs8* pName)
{
    auto it = m_mapSound.find(pName);
    if(it == m_mapSound.end())
    {
        return;
    }

    it->second->Stop();
}

//=============================================================================
// すべての音を止める
//=============================================================================
void CSubMix::Stop()
{
    for(auto it = m_mapSound.begin(); it != m_mapSound.end(); ++it)
    {
        it->second->Stop();
    }
}

//=============================================================================
// 音量設定
//=============================================================================
void CSubMix::SetVolume(s32 nVolume)
{
    if(IS_NULL(m_pSubMix))
    {
        return;
    }

    if(nVolume < 0) nVolume = 0;
    else if(nVolume > 100) nVolume = 100;
    m_pSubMix->SetVolume(nVolume / VOLUME_SCALE);
}

//=============================================================================
// 音量取得
//=============================================================================
s32 CSubMix::GetVolumei() const
{
    if(IS_NULL(m_pSubMix))
    {
        return 0;
    }

    f32 fVol = 0.0f;
    m_pSubMix->GetVolume(&fVol);
    return (s32)(fVol * VOLUME_SCALE);
}

//=============================================================================
// 音量取得
//=============================================================================
f32 CSubMix::GetVolumef() const
{
    if(IS_NULL(m_pSubMix))
    {
        return 0;
    }

    f32 fVol = 0.0f;
    m_pSubMix->GetVolume(&fVol);
    return fVol;
}

//=============================================================================
// プリロード
//=============================================================================
void CSubMix::Load(cs8* pName)
{
    auto it = m_mapSound.find(pName);
    if(it == m_mapSound.end())
    {
        // 読み込み処理
        std::string path(m_strFilePath);
        path += pName;
        CSound* pSound = CSound::Create(path.c_str(), m_pSubMix, m_pXAudio2);
        if(pSound)
        {
            m_mapSound[pName] = pSound;
        }
    }
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CSubMix::Init(IXAudio2* pXAudio2)
{
    m_pXAudio2 = pXAudio2;

    HRESULT hr;
    hr = m_pXAudio2->CreateSubmixVoice(&m_pSubMix, 1, 44100);

    return hr;
}

// EOF
