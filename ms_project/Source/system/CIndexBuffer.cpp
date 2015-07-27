//=============================================================================
//
// �C���f�b�N�X�o�b�t�@
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CIndexBuffer.h"
#include "CDeviceHolder.h"
#include "DebugUtil.h"

//*****************************************************************************
// ���O���
//*****************************************************************************
namespace
{
    // �Ǝ���`��DirectX�萔�̑Ή�
    static const D3DFORMAT IDX_FORMAT[] =
    {
        D3DFMT_INDEX16,
        D3DFMT_INDEX32
    };
    static const DWORD IDX_USAGE[] =
    {
        D3DUSAGE_DYNAMIC,
        D3DUSAGE_WRITEONLY
    };
    static const D3DPOOL IDX_POOL[] =
    {
        D3DPOOL_DEFAULT,
        D3DPOOL_MANAGED,
        D3DPOOL_SYSTEMMEM
    };
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CIndexBuffer::CIndexBuffer()
    : m_pIdx(nullptr)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CIndexBuffer::~CIndexBuffer()
{
    SafeRelease(m_pIdx);
}

//=============================================================================
// �C���f�b�N�X�o�b�t�@����
//=============================================================================
CIndexBuffer* CIndexBuffer::Create(CDeviceHolder* pHolder, const IndexBufferDesc& desc)
{
    CIndexBuffer* pIdx = new CIndexBuffer();

    if(pIdx)
    {
        INIT_CHECK(pIdx->Init(pHolder, desc));
        _PrintConsole("�C���f�b�N�X�o�b�t�@\n");
    }

    return pIdx;
}

//=============================================================================
// DirectX�C���f�b�N�X�o�b�t�@�擾
//=============================================================================
LPDIRECT3DINDEXBUFFER9 CIndexBuffer::GetPointer() const
{
    return m_pIdx;
}

//=============================================================================
// �J��
//=============================================================================
void CIndexBuffer::Release()
{
    CRef::Decrement();
}

//=============================================================================
// �C���f�b�N�X�o�b�t�@���b�N
//=============================================================================
HRESULT CIndexBuffer::Lock(void** pBuff)
{
    return m_pIdx->Lock(0, 0, pBuff, 0);
}

//=============================================================================
// �C���f�b�N�X�o�b�t�@�A�����b�N
//=============================================================================
HRESULT CIndexBuffer::Unlock()
{
    return m_pIdx->Unlock();
}

//=============================================================================
// ���\�[�X�̋����I�ȍ폜
//=============================================================================
void CIndexBuffer::CleanUp()
{
    delete this;
}

//=============================================================================
// ���\�[�X���̕ۑ�
//=============================================================================
void CIndexBuffer::Restore()
{
    m_pIdx->GetDesc(&m_desc);
    SafeRelease(m_pIdx);
}

//=============================================================================
// ���\�[�X���̍ēǂݍ���
//=============================================================================
void CIndexBuffer::Reload(CDeviceHolder* pHolder)
{
    auto pDev = pHolder->GetDevice();

    pDev->CreateIndexBuffer(
        m_desc.Size,
        m_desc.Usage,
        m_desc.Format,
        m_desc.Pool,
        &m_pIdx,
        nullptr);
    _Assert(m_pIdx);
}

//=============================================================================
// ������
//=============================================================================
HRESULT CIndexBuffer::Init(CDeviceHolder* pHolder, const IndexBufferDesc& desc)
{
    auto pDev = pHolder->GetDevice();

    pDev->CreateIndexBuffer(
        desc.Size,
        IDX_USAGE[desc.Usage],
        IDX_FORMAT[desc.Format],
        IDX_POOL[desc.Pool],
        &m_pIdx,
        nullptr);
    _Assert(m_pIdx);

    m_pIdx->GetDesc(&m_desc);

    return S_OK;
}

// EOF
