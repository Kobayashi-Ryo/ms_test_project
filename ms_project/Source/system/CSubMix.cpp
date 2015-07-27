//=============================================================================
//
// �T�E���h�J�e�S���[���Ƃ̐ݒ�
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CSubMix.h"
#include "SoundDef.h"
#include "CSound.h"
#include "DebugUtil.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSubMix::CSubMix(const std::string& strPath)
    : m_pSubMix(nullptr)
    , m_pXAudio2(nullptr)
    , m_strFilePath(strPath)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSubMix::~CSubMix()
{
    ReleaseVoice(m_pSubMix);

    // �T�E���h�f�[�^�J��
    for(auto it = m_mapSound.begin(); it != m_mapSound.end(); )
    {
        it->second->Release();
        m_mapSound.erase(it++);
    }
}

//=============================================================================
// ����
//=============================================================================
CSubMix* CSubMix::Create(const std::string& strPath, IXAudio2* pXAudio2)
{
    CSubMix* pSub = new CSubMix(strPath);

    if(pSub)
    {
        INIT_CHECK(pSub->Init(pXAudio2));
        _PrintConsole("�T�u�~�b�N�X\n");
    }

    return pSub;
}

//=============================================================================
// �J��
//=============================================================================
void CSubMix::Release()
{
    delete this;
}

//=============================================================================
// �Đ�
//=============================================================================
void CSubMix::Play(cs8* pName, bool bLoop)
{
    auto it = m_mapSound.find(pName);
    if(it == m_mapSound.end())
    {
        // �ǂݍ��ݏ���
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
// �~�߂�
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
// ���ׂẲ����~�߂�
//=============================================================================
void CSubMix::Stop()
{
    for(auto it = m_mapSound.begin(); it != m_mapSound.end(); ++it)
    {
        it->second->Stop();
    }
}

//=============================================================================
// ���ʐݒ�
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
// ���ʎ擾
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
// ���ʎ擾
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
// �v�����[�h
//=============================================================================
void CSubMix::Load(cs8* pName)
{
    auto it = m_mapSound.find(pName);
    if(it == m_mapSound.end())
    {
        // �ǂݍ��ݏ���
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
// ������
//=============================================================================
HRESULT CSubMix::Init(IXAudio2* pXAudio2)
{
    m_pXAudio2 = pXAudio2;

    HRESULT hr;
    hr = m_pXAudio2->CreateSubmixVoice(&m_pSubMix, 1, 44100);

    return hr;
}

// EOF
