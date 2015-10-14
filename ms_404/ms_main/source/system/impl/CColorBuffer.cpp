//=============================================================================
//
// �J���[�o�b�t�@ [CColorBuffer.cpp]
// Author : Ryo Kobayashi
// Data : 2015/5/3
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CColorBuffer.h"
#include "CTexture.h"
#include <common/DebugUtil.h>

//=============================================================================
// ����
//=============================================================================
CColorBuffer* CColorBuffer::Create(CDeviceHolder* pHolder, const ColorBufferDesc& desc)
{
    CColorBuffer* pColorBuffer = new CColorBuffer();
    
    if(pColorBuffer)
    {
        INIT_CHECK(pColorBuffer->Initialize(pHolder, desc));
        _PrintConsole("�J���[�o�b�t�@");
    }

    return pColorBuffer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CColorBuffer::Initialize(CDeviceHolder* pHolder, const ColorBufferDesc& desc)
{
    m_desc = desc;

    Uninitialize();
    
    if(!pHolder) return E_FAIL;
    m_pDev = pHolder->GetDevice();;

    // ��e�N�X�`������
    TextureDesc t_desc;
    t_desc.Width = m_desc.width;
    t_desc.Height = m_desc.height;
    t_desc.Usage = TEXUSAGE_RENDERTARGET;
    t_desc.Format = m_desc.format;
    m_pTexture = CTexture::Create(pHolder, t_desc);

    // �e�N�X�`���ւ̃T�[�t�F�X���擾
    m_pTexture->GetTexture()->GetSurfaceLevel(0, &m_pSurface);

    return S_OK;
}

//=============================================================================
// �J��
//=============================================================================
void CColorBuffer::Release()
{
    CRef::Decrement();
}

//=============================================================================
// �K�p
//=============================================================================
void CColorBuffer::Attach()
{
    m_pDev->GetRenderTarget(m_desc.index, &m_pPrevSurface);
    m_pDev->SetRenderTarget(m_desc.index, m_pSurface);
}

//=============================================================================
// ����
//=============================================================================
void CColorBuffer::Detach()
{
    _Assert(m_pPrevSurface);

    m_pDev->SetRenderTarget(m_desc.index, m_pPrevSurface);
    SafeRelease(m_pPrevSurface);
}

//=============================================================================
// �f�o�C�X�ݒ�
//=============================================================================
void CColorBuffer::SetDevice(LPDIRECT3DDEVICE9 pDev)
{
    m_pDev = pDev;
}

//=============================================================================
// �����_�[�^�[�Q�b�g�C���f�b�N�X�ݒ�
//=============================================================================
void CColorBuffer::SetRenderTargetIndex(cu32 uIndex)
{
    m_desc.index = uIndex;
}

//=============================================================================
// �����擾
//=============================================================================
u32 CColorBuffer::GetWidth() const
{
    return m_desc.width;
}

//=============================================================================
// �c���擾
//=============================================================================
u32 CColorBuffer::GetHeight() const
{
    return m_desc.height;
}

//=============================================================================
// �e�N�X�`���擾
//=============================================================================
ITexture* CColorBuffer::GetTexture() const
{
    return m_pTexture;
}

//=============================================================================
// ���\�[�X�̋����I�ȍ폜
//=============================================================================
void CColorBuffer::CleanUp()
{
    delete this;
}

//=============================================================================
// ���\�[�X���̕ۑ�
//=============================================================================
void CColorBuffer::Restore()
{
    m_pTexture->Restore();
}

//=============================================================================
// ���\�[�X���̍ēǂݍ���
//=============================================================================
void CColorBuffer::Reload(CDeviceHolder* pHolder)
{
    m_pTexture->Reload(pHolder);
    m_pTexture->GetTexture()->GetSurfaceLevel(0, &m_pSurface);
}

//=============================================================================
// �J��
//=============================================================================
void CColorBuffer::Uninitialize()
{
    SafeRelease(m_pSurface);
    SafeRelease(m_pTexture);

    // �J���Y��̎��̂���
    SafeRelease(m_pPrevSurface);

    m_pDev = nullptr;
}
























CColorBuffer::CColorBuffer()
    : m_pSurface(nullptr)
    , m_pTexture(nullptr)
    , m_pPrevSurface(nullptr)
    , m_desc()
    , m_pDev(nullptr)
{
}

CColorBuffer::~CColorBuffer()
{
    Uninitialize();
}

// EOF