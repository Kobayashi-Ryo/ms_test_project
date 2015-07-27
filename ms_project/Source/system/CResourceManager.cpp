//=============================================================================
//
// ���\�[�X�Ǘ��N���X
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CResourceManager.h"
#include <algorithm>
#include <memory>

#include "CDeviceHolder.h"

#include "CLostResource.h"
#include "CFont.h"
#include "CTexture.h"
#include "CVertexDeclaration.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

#include "DebugUtil.h"

//*****************************************************************************
// ���O���
//*****************************************************************************
namespace
{
    static cs8* PATH_TEXTURE = "Resource/Texture/";
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResourceManager::CResourceManager()
    : m_pHolder(nullptr)
{
    int* i = new int;
    *i = 5;
    std::tr1::shared_ptr<int> d(i);
    std::tr1::shared_ptr<int> x = std::move(d);
    int a = d.use_count();
    int b = sizeof(std::tr1::shared_ptr<CTexture>);

    std::list< std::tr1::shared_ptr<int> > splist;
    splist.push_back(x);
    for(auto it = splist.begin(); it != splist.end(); ++it)
    {
        if((*it) == x)
        {
            (*(*it).get()) = 10;
        }
    }
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResourceManager::~CResourceManager()
{
    // ���X�g���\�[�X�J��
    auto itDel = std::remove_if(m_listLostRes.begin(), m_listLostRes.end(),
    []
    (CLostResource*)
    ->bool
    {
        return true;
    }
    );
    m_listLostRes.erase(itDel, m_listLostRes.end());
    
    // �t�H���g�J��
    for(auto it = m_setFont.begin(); it != m_setFont.end();)
    {
        (*it)->CleanUp();
        m_setFont.erase(it++);
    }

    // �e�N�X�`���J��
    for(auto it = m_setTextures.begin(); it != m_setTextures.end();)
    {
        (*it)->CleanUp();
        m_setTextures.erase(it++);
    }
    for(auto it = m_mapTextures.begin(); it != m_mapTextures.end();)
    {
        it->second->CleanUp();
        m_mapTextures.erase(it++);
    }
    
    // ���_�錾�J��
    for(auto it = m_setVertexDecl.begin(); it != m_setVertexDecl.end();)
    {
        (*it)->Release();
        m_setVertexDecl.erase(it++);
    }

    // ���_�o�b�t�@�J��
    for(auto it = m_setVertexBuffer.begin(); it != m_setVertexBuffer.end();)
    {
        (*it)->CleanUp();
        m_setVertexBuffer.erase(it++);
    }

    // �C���f�b�N�X�o�b�t�@�J��
    for(auto it = m_setIndexBuffer.begin(); it != m_setIndexBuffer.end();)
    {
        (*it)->CleanUp();
        m_setIndexBuffer.erase(it++);
    }
}

//=============================================================================
// ������
//=============================================================================
CResourceManager* CResourceManager::Create(CDeviceHolder* pHolder)
{
    CResourceManager* pMgr = new CResourceManager();

    if(pMgr)
    {
        INIT_CHECK(pMgr->Init(pHolder));
        _PrintConsole("���\�[�X�}�l�[�W���[\n");
    }

    return pMgr;
}

//=============================================================================
// �J��
//=============================================================================
void CResourceManager::Release()
{
    delete this;
}

//=============================================================================
// ���\�[�X�ď�����
//=============================================================================
void CResourceManager::Reset()
{
    if(IsLost()) return;

    for(auto it = m_listLostRes.begin(); it != m_listLostRes.end(); ++it)
    {
        (*it)->Restore();
    }

    HRESULT hr = m_pHolder->Reset();
    if(SUCCEEDED(hr)) { _PrintConsole("�f�o�C�X���A\n"); }
    else { _PrintConsole("�f�o�C�X���A���s\n"); return; }
    
    for(auto it = m_listLostRes.begin(); it != m_listLostRes.end(); ++it)
    {
        (*it)->Reload(m_pHolder);
    }
}

//=============================================================================
// �t�H���g�C���^�[�t�F�[�X�̎擾
//=============================================================================
IFont* CResourceManager::GetFont(const FontDesc& desc)
{
    CFont* pFont = CFont::Create(m_pHolder, desc);

    if(pFont)
    {
        pFont->Increment();

        m_listLostRes.push_back(pFont);
        m_setFont.insert(pFont);
    }

    return pFont;
}

//=============================================================================
// �t�H���g�J��
//=============================================================================
void CResourceManager::Release(IFont* pFont)
{
    auto it = m_setFont.find((CFont*)pFont);
    if(it != m_setFont.end())
    {
        CFont *pDelFont = nullptr;
        pDelFont = (*it);
        if(pDelFont->GetReferenceCount() <= 1)
        {// ���t�@�����X���s����
            // ���X�g����폜
            m_setFont.erase(it);
            // ���X�g���\�[�X����폜
            auto itDel = std::remove_if(m_listLostRes.begin(), m_listLostRes.end(),
            [pDelFont] (CLostResource* pRes) ->bool
            {
                if(pRes == (CLostResource*)pDelFont)
                {
                    return true;
                }
                return false;
            });
            if(itDel != m_listLostRes.end())
            {
                m_listLostRes.erase(itDel);
            }
        }
        // �J�E���^�f�N�������g
        pDelFont->Decrement();
    }
}

//=============================================================================
// �e�N�X�`���̎擾
//=============================================================================
ITexture* CResourceManager::GetTexture(cs8* pFileName)
{
    auto it = m_mapTextures.find(pFileName);
    if(it != m_mapTextures.end())
    {
        it->second->Increment();
        return it->second;
    }

    std::string strPath(PATH_TEXTURE);
    strPath += pFileName;
    CTexture* pTex = CTexture::Create(m_pHolder, strPath.c_str());

    if(pTex)
    {
        m_mapTextures[pFileName] = pTex;
    }

    pTex->Increment();
    return pTex;
}

//=============================================================================
// �e�N�X�`���̎擾
//=============================================================================
ITexture* CResourceManager::GetTexture(const TextureDesc& desc)
{
    CTexture* pTex = CTexture::Create(m_pHolder, desc);

    if(pTex)
    {
        pTex->Increment();
        m_listLostRes.push_back(pTex);
        m_setTextures.insert(pTex);
    }

    return pTex;
}

//=============================================================================
// �e�N�X�`���J��
//=============================================================================
void CResourceManager::Release(ITexture* pTex)
{
    if(0 == pTex->GetName().compare(""))
    {
        ReleaseUnnamedTexture(pTex);
    }
    else
    {
        ReleaseNamedTexture(pTex);
    }
}

//=============================================================================
// ���_�錾�̎擾
//=============================================================================
IVertexDeclaration* CResourceManager::GetVertexDeclaration(u8 uNumElems, const VertexDeclarationDesc* pDesc)
{
    CVertexDeclaration* pDecl = CVertexDeclaration::Create(m_pHolder, uNumElems, pDesc);

    if(pDecl)
    {
        m_setVertexDecl.insert(pDecl);
    }

    return pDecl;
}

//=============================================================================
// ���_�錾�J��
//=============================================================================
void CResourceManager::Release(IVertexDeclaration* pDecl)
{
    auto itDel = m_setVertexDecl.find((CVertexDeclaration*)pDecl);
    if(itDel != m_setVertexDecl.end())
    {
        (*itDel)->Release();
        m_setVertexDecl.erase(itDel);
    }
}

//=============================================================================
// ���_�o�b�t�@�̎擾
//=============================================================================
IVertexBuffer* CResourceManager::GetVertexBuffer(const VertexBufferDesc& desc)
{
    CVertexBuffer* pVtx = CVertexBuffer::Create(m_pHolder, desc);

    if(pVtx)
    {
        pVtx->Increment();

        // �������z�u�`�F�b�N
        if(desc.Pool == VTXPOOL_DEFAULT)
        {
            m_listLostRes.push_back(pVtx);
        }
        m_setVertexBuffer.insert(pVtx);
    }

    return pVtx;
}

//=============================================================================
// ���_�o�b�t�@�J��
//=============================================================================
void CResourceManager::Release(IVertexBuffer* pVtx)
{
    auto it = m_setVertexBuffer.find((CVertexBuffer*)pVtx);
    if(it != m_setVertexBuffer.end())
    {
        CVertexBuffer *pDelVtx = nullptr;
        pDelVtx = (*it);
        if(pDelVtx->GetReferenceCount() <= 1)
        {// ���t�@�����X���s����
            // ���X�g����폜
            m_setVertexBuffer.erase(it);
            // ���X�g���\�[�X����폜
            auto itDel = std::remove_if(m_listLostRes.begin(), m_listLostRes.end(),
            [pDelVtx] (CLostResource* pRes) ->bool
            {
                if(pRes == (CLostResource*)pDelVtx)
                {
                    return true;
                }
                return false;
            });
            if(itDel != m_listLostRes.end())
            {
                m_listLostRes.erase(itDel);
            }
        }
        // �J�E���^�f�N�������g
        pDelVtx->Decrement();
    }
}

//=============================================================================
// �C���f�b�N�X�o�b�t�@�̎擾
//=============================================================================
IIndexBuffer* CResourceManager::GetIndexBuffer(const IndexBufferDesc& desc)
{
    CIndexBuffer* pIdx = CIndexBuffer::Create(m_pHolder, desc);

    if(pIdx)
    {
        pIdx->Increment();

        // �������z�u�`�F�b�N
        if(desc.Pool == IDXPOOL_DEFAULT)
        {
            m_listLostRes.push_back(pIdx);
        }
        m_setIndexBuffer.insert(pIdx);
    }

    return pIdx;
}

//=============================================================================
// �C���f�b�N�X�J��
//=============================================================================
void CResourceManager::Release(IIndexBuffer* pIdx)
{
    auto it = m_setIndexBuffer.find((CIndexBuffer*)pIdx);
    if(it != m_setIndexBuffer.end())
    {
        CIndexBuffer *pDelIdx = nullptr;
        pDelIdx = (*it);
        if(pDelIdx->GetReferenceCount() <= 1)
        {// ���t�@�����X���s����
            // ���X�g����폜
            m_setIndexBuffer.erase(it);
            // ���X�g���\�[�X����폜
            auto itDel = std::remove_if(m_listLostRes.begin(), m_listLostRes.end(),
            [pDelIdx] (CLostResource* pRes) ->bool
            {
                if(pRes == (CLostResource*)pDelIdx)
                {
                    return true;
                }
                return false;
            });
            if(itDel != m_listLostRes.end())
            {
                m_listLostRes.erase(itDel);
            }
        }
        // �J�E���^�f�N�������g
        pDelIdx->Decrement();
    }
}

//=============================================================================
// ������
//=============================================================================
HRESULT CResourceManager::Init(CDeviceHolder* pHolder)
{
    m_pHolder = pHolder;

    return S_OK;
}

//=============================================================================
// ���X�g��Ԃ̃`�F�b�N
//=============================================================================
bool CResourceManager::IsLost()
{
    HRESULT hr = m_pHolder->GetDevice()->TestCooperativeLevel();

    if(D3DERR_DEVICELOST == hr)
    {
        _PrintConsole("�f�o�C�X���X�g\n");
        return true;
    }
    else if(D3DERR_DRIVERINTERNALERROR == hr)
    {
        _CriticalAssertExpr(SUCCEEDED(hr), "�h���C�o�[���ɃG���[����");
    }
    else if(D3DERR_DEVICENOTRESET == hr)
    {
        _PrintConsole("�f�o�C�X���A�\\n");
        return false;
    }

    return false;
}

//=============================================================================
// ���O�t���e�N�X�`���̊J��
//=============================================================================
void CResourceManager::ReleaseNamedTexture(ITexture* pTex)
{
    auto it = m_mapTextures.find(pTex->GetName());
    if(it != m_mapTextures.end())
    {
        CTexture *pDelTex = nullptr;
        pDelTex = it->second;
        if(pDelTex->GetReferenceCount() <= 1)
        {// ���t�@�����X���s����
            // ���X�g����폜
            m_mapTextures.erase(it);
        }
        // �J�E���^�f�N�������g
        pDelTex->Decrement();
    }
}

//=============================================================================
// ���O�Ȃ��e�N�X�`���J��
//=============================================================================
void CResourceManager::ReleaseUnnamedTexture(ITexture* pTex)
{
    auto it = m_setTextures.find((CTexture*)pTex);
    if(it != m_setTextures.end())
    {
        CTexture *pDelTex = nullptr;
        pDelTex = (*it);
        if(pDelTex->GetReferenceCount() <= 1)
        {// ���t�@�����X���s����
            // ���X�g����폜
            m_setTextures.erase(it);
            // ���X�g���\�[�X����폜
            auto itDel = std::remove_if(m_listLostRes.begin(), m_listLostRes.end(),
            [pDelTex]
            (CLostResource* pRes)
            ->bool
            {
                if(pRes == (CLostResource*)pDelTex)
                {
                    return true;
                }
                return false;
            }
            );
            m_listLostRes.erase(itDel);
        }
        // �J�E���^�f�N�������g
        pDelTex->Decrement();
    }
}

// EOF
