//=============================================================================
//
// ���_�o�b�t�@
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CVertexBuffer.h"
#include "CDeviceHolder.h"
#include "DebugUtil.h"

//*****************************************************************************
// ���O���
//*****************************************************************************
namespace
{
    // �Ǝ���`��DirectX�萔�̑Ή�
    static const DWORD VTX_USAGE[] =
    {
        D3DUSAGE_DYNAMIC,
        D3DUSAGE_SOFTWAREPROCESSING,
        D3DUSAGE_WRITEONLY
    };
    static const D3DPOOL VTX_POOL[] =
    {
        D3DPOOL_DEFAULT,
        D3DPOOL_MANAGED,
        D3DPOOL_SYSTEMMEM
    };
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CVertexBuffer::CVertexBuffer()
    : m_pVtx(nullptr)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CVertexBuffer::~CVertexBuffer()
{
    SafeRelease(m_pVtx);
}

//=============================================================================
// ���_�o�b�t�@����
//=============================================================================
CVertexBuffer* CVertexBuffer::Create(CDeviceHolder* pHolder, const VertexBufferDesc& desc)
{
    CVertexBuffer* pVtx = new CVertexBuffer();

    if(pVtx)
    {
        INIT_CHECK(pVtx->Init(pHolder, desc));
        _PrintConsole("���_�o�b�t�@\n");
    }

    return pVtx;
}

//=============================================================================
// DirectX���_�o�b�t�@�擾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CVertexBuffer::GetPointer() const
{
    return m_pVtx;
}

//=============================================================================
// �J��
//=============================================================================
void CVertexBuffer::Release()
{
    CRef::Decrement();
}

//=============================================================================
// ���_�o�b�t�@���b�N
//=============================================================================
HRESULT CVertexBuffer::Lock(void** pBuff)
{
    return m_pVtx->Lock(0, 0, pBuff, 0);
}

//=============================================================================
// ���_�o�b�t�@�A�����b�N
//=============================================================================
HRESULT CVertexBuffer::Unlock()
{
    return m_pVtx->Unlock();
}

//=============================================================================
// ���\�[�X�̋����I�ȍ폜
//=============================================================================
void CVertexBuffer::CleanUp()
{
    delete this;
}

//=============================================================================
// ���\�[�X���̕ۑ�
//=============================================================================
void CVertexBuffer::Restore()
{
    m_pVtx->GetDesc(&m_desc);
    SafeRelease(m_pVtx);
}

//=============================================================================
// ���\�[�X���̍ēǂݍ���
//=============================================================================
void CVertexBuffer::Reload(CDeviceHolder* pHolder)
{
    auto pDev = pHolder->GetDevice();

    pDev->CreateVertexBuffer(
        m_desc.Size,
        m_desc.Usage,
        0,
        m_desc.Pool,
        &m_pVtx,
        nullptr);
    _Assert(m_pVtx);
}

//=============================================================================
// ������
//=============================================================================
HRESULT CVertexBuffer::Init(CDeviceHolder* pHolder, const VertexBufferDesc& desc)
{
    auto pDev = pHolder->GetDevice();

    pDev->CreateVertexBuffer(
        desc.Size,
        VTX_USAGE[desc.Usage],
        0,
        VTX_POOL[desc.Pool],
        &m_pVtx,
        nullptr);
    _Assert(m_pVtx);

    m_pVtx->GetDesc(&m_desc);

    return S_OK;
}

// EOF
