//=============================================================================
//
// �V�[���N���X���
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CScene.h"
#include <algorithm>
#include "CApplication.h"
#include <common/DebugUtil.h>

// �J�����擾
const  std::vector<CCamera*>& CScene::GetCameras() const
{
    return m_Cameras;
}

// �J���������擾
u32 CScene::GetNumCameras() const
{
    return m_Cameras.size();
}

// �V�F�[�_�[�擾
IShader* CScene::GetShader2D() const
{
    return m_pShader2D;
}
IShader* CScene::GetShader3D() const
{
    return m_pShader3D;
}

bool CScene::Init()
{
    return true;
}

CScene::CScene()
    : m_pShader2D(nullptr)
    , m_pShader3D(nullptr)
{
    for(int i = 0; i < DEFAULT_CAMERA_NUM; i++)
    {
        m_Cameras.push_back(new CCamera());
    }

    InitShader();
}

CScene::~CScene()
{
    auto itDel = std::remove_if(m_Cameras.begin(), m_Cameras.end(),
        [](CCamera* pCam)
    {
        return true;
    });

    for(auto it = itDel; it != m_Cameras.end(); ++it)
    {
        SafeDelete(*it);
    }
    
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    res->Release(m_pShader2D);
    res->Release(m_pShader3D);
}

void CScene::InitShader()
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    if(m_pShader2D) res->Release(m_pShader2D);
    if(m_pShader3D) res->Release(m_pShader3D);
    m_pShader2D = res->GetShader(DEFAULT_VERTEX_SHADER_2D, DEFAULT_PIXEL_SHADER_2D);
    _Assert(m_pShader2D);
    m_pShader3D = res->GetShader(DEFAULT_VERTEX_SHADER_3D, DEFAULT_PIXEL_SHADER_3D);
    _Assert(m_pShader3D);
}

// EOF
