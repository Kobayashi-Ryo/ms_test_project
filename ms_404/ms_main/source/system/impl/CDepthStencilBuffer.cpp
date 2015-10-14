//=============================================================================
//
// �[�x�X�e���V���o�b�t�@ [CDepthStencilBuffer.h]
// Author : Ryo Kobayashi
// Data : 2015/5/3
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CDepthStencilBuffer.h"
#include "CDeviceHolder.h"
#include <common/DebugUtil.h>

//*****************************************************************************
// ���O���
//*****************************************************************************
namespace
{
    // �Ǝ���`��DirectX�萔�̑Ή�
    const D3DFORMAT DS_FORMAT[] =
    {
        D3DFMT_D16,
        D3DFMT_D32,
        D3DFMT_D24S8
    };
}

//=============================================================================
// ����
//=============================================================================
CDepthStencilBuffer* CDepthStencilBuffer::Create(CDeviceHolder* pHolder, const DepthStencilBufferDesc& desc)
{
    CDepthStencilBuffer* pDSBuffer = new CDepthStencilBuffer();
    
    if(pDSBuffer)
    {
        INIT_CHECK(pDSBuffer->Initialize(pHolder, desc));
        _PrintConsole("�[�x�X�e���V���o�b�t�@");
    }

    return pDSBuffer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CDepthStencilBuffer::Initialize(CDeviceHolder* pHolder, const DepthStencilBufferDesc& desc)
{
    if(!pHolder) return E_FAIL;
    m_pDev = pHolder->GetDevice();
    
    HRESULT hr;
    // �[�x�o�b�t�@�T�[�t�F�C�X�쐬
    hr = m_pDev->CreateDepthStencilSurface(
        desc.width,
        desc.height,
        DS_FORMAT[desc.format],        // �[�x�o�b�t�@�t�H�[�}�b�g
        D3DMULTISAMPLE_NONE,    // �}���`�T���v���^�C�v
        0,                    // �i��
        TRUE,            // �o�b�t�@�j��ON
        &m_pDepthSurface,
        nullptr);
    _Assert(SUCCEEDED(hr));

    m_pDepthSurface->GetDesc(&m_desc);

    return hr;
}

//=============================================================================
// �J��
//=============================================================================
void CDepthStencilBuffer::Release()
{
    CRef::Decrement();
}

//=============================================================================
// �K�p
//=============================================================================
void CDepthStencilBuffer::Attach()
{
    if(m_pDev)
    {
        // �[�x�o�b�t�@�擾
        m_pDev->GetDepthStencilSurface(&m_pPrevSurface);
        // ���������e�N�X�`���p�ɍ쐬����Z�o�b�t�@��ݒ�
        m_pDev->SetDepthStencilSurface(m_pDepthSurface);
    }
}

//=============================================================================
// ����
//=============================================================================
void CDepthStencilBuffer::Detach()
{
    if(m_pDev)
    {
        m_pDev->SetDepthStencilSurface(m_pPrevSurface);
        SafeRelease(m_pPrevSurface);
    }
}

//=============================================================================
// �f�o�C�X�ݒ�
//=============================================================================
void CDepthStencilBuffer::SetDevice(LPDIRECT3DDEVICE9 pDev)
{
    m_pDev = pDev;
}

//=============================================================================
// �����擾
//=============================================================================
u32 CDepthStencilBuffer::GetWidth() const
{
    return m_desc.Width;
}

//=============================================================================
// �c���擾
//=============================================================================
u32 CDepthStencilBuffer::GetHeight() const
{
    return m_desc.Height;
}

//=============================================================================
// ���\�[�X�̋����I�ȍ폜
//=============================================================================
void CDepthStencilBuffer::CleanUp()
{
    delete this;
}

//=============================================================================
// ���\�[�X���̕ۑ�
//=============================================================================
void CDepthStencilBuffer::Restore()
{
    m_pDepthSurface->GetDesc(&m_desc);
    SafeRelease(m_pDepthSurface);
}

//=============================================================================
// ���\�[�X���̍ēǂݍ���
//=============================================================================
void CDepthStencilBuffer::Reload(CDeviceHolder* pHolder)
{
    m_pDev = pHolder->GetDevice();
    HRESULT hr;
    // �[�x�o�b�t�@�T�[�t�F�C�X�쐬
    hr = m_pDev->CreateDepthStencilSurface(
        m_desc.Width,
        m_desc.Height,
        m_desc.Format,        // �[�x�o�b�t�@�t�H�[�}�b�g
        D3DMULTISAMPLE_NONE,    // �}���`�T���v���^�C�v
        0,                    // �i��
        TRUE,            // �o�b�t�@�j��ON
        &m_pDepthSurface,
        nullptr);
    _Assert(SUCCEEDED(hr));
}
























CDepthStencilBuffer::CDepthStencilBuffer()
    : m_pDepthSurface(nullptr)
    , m_pPrevSurface(nullptr)
    , m_desc()
    , m_pDev(nullptr)
{
}

CDepthStencilBuffer::~CDepthStencilBuffer()
{
    SafeRelease(m_pDepthSurface);
    SafeRelease(m_pPrevSurface);

    m_pDev = nullptr;
}

// EOF