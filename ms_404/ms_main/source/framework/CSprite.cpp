//=============================================================================
//
// �X�v���C�g�N���X
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CSprite.h"
#include "CApplication.h"
#include <common/DebugUtil.h>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSprite::CSprite()
    : m_pVtxBuff(nullptr)
    , m_pTex(nullptr)
    , m_color(1,1,1,1)
    , m_size(0, 0)
    , m_texPos(0, 0)
    , m_texSize(1.0f, 1.0f)
    , m_bSpriteUpdate(true)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSprite::~CSprite()
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    res->Release(m_pVtxBuff);
    res->Release(m_pDecl);
    if(m_pTex && m_pTex->GetName().size() > 0)
    {
        res->Release(m_pTex);
    }
}

//=============================================================================
// ����
//=============================================================================
CSprite* CSprite::Create()
{
    return Create(SpriteDesc());
}

//=============================================================================
// ����
//=============================================================================
CSprite* CSprite::Create(const SpriteDesc& desc)
{
    CSprite* pSpr = new CSprite();

    if(pSpr)
    {
        INIT_CHECK(pSpr->Init(desc));
        _PrintConsole("�X�v���C�g\n");
    }

    return pSpr;
}

//=============================================================================
// ����
//=============================================================================
CSprite* CSprite::Create(const SpriteDesc& desc, cs8* pFileName)
{
    CSprite* pSpr = new CSprite();

    if(pSpr)
    {
        INIT_CHECK(pSpr->Init(desc, pFileName));
        _PrintConsole("�X�v���C�g : �e�N�X�`�� %s\n", pFileName);
    }

    return pSpr;
}

//=============================================================================
// �X�V
//=============================================================================
void CSprite::Update()
{
    SetupTransform();

    if(m_bSpriteUpdate)
    {
        UpdateBuffer();
    }

    CNode::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CSprite::Draw()
{
    m_pVtxBuff->Attach();
    m_pDecl->Attach();
    if(m_pTex) m_pTex->Attach();

    auto dev = CApplication::GetInstance()->GetSystem()->GetDeviceHolder()->GetDevice();
    HRESULT hr = dev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    m_pVtxBuff->Detach();
    m_pDecl->Detach();
    if(m_pTex) m_pTex->Detach();

    CNode::Draw();
}

// �F�ݒ�
void CSprite::SetColor(const D3DXCOLOR& color){ SetColor(color.r, color.g, color.b); }
void CSprite::SetColor(cf32 r, cf32 g, cf32 b){ m_bSpriteUpdate = true; m_color.r = r; m_color.g = g; m_color.b = b; }
// �F�擾
const D3DXCOLOR& CSprite::GetColor() const { return m_color; }

// �A���t�@�l�ݒ�
void CSprite::SetAlpha(cf32 a){ m_bSpriteUpdate = true; m_color.a = a; }
// �A���t�@�l�擾
f32 CSprite::GetAlpha() const { return m_color.a; }

// �e�N�X�`���ݒ�
void CSprite::SetTexture(cs8* pFileName, bool bUseTexSize)
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    if(!m_pTex)
    {
        m_pTex = res->GetTexture(pFileName);
        if(m_pTex && bUseTexSize)
        {
            m_size.x = (f32)m_pTex->GetWidth();
            m_size.y = (f32)m_pTex->GetHeight();
        }
        return;
    }

    ITexture* pTex = res->GetTexture(pFileName);
    if(!pTex) return;

    if(m_pTex && m_pTex->GetName().size() > 0)
    {
        res->Release(m_pTex);
    }

    m_pTex = pTex;
    if(bUseTexSize)
    {
        m_size.x = (f32)m_pTex->GetWidth();
        m_size.y = (f32)m_pTex->GetHeight();
        m_bSpriteUpdate = true;
    }
}

void CSprite::SetTexture(ITexture* pTex, bool bUseTexSize)
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    if(m_pTex && m_pTex->GetName().size() > 0)
    {
        res->Release(m_pTex);
    }

    m_pTex = pTex;
    if(m_pTex && bUseTexSize)
    {
        m_size.x = (f32)m_pTex->GetWidth();
        m_size.y = (f32)m_pTex->GetHeight();
        m_bSpriteUpdate = true;
    }
}

// �����ݒ�
void CSprite::SetWidth(cf32 fWidth)
{
    m_size.x = fWidth;
    m_bSpriteUpdate = true;
}
// �����擾
f32 CSprite::GetWidth() const
{
    return m_size.x;
}

// �c���ݒ�
void CSprite::SetHeight(cf32 fHeight)
{
    m_size.y = fHeight;
    m_bSpriteUpdate = true;
}
// �c���擾
f32 CSprite::GetHeight() const
{
    return m_size.y;
}

// �c���̕��ݒ�
void CSprite::SetSize(const vec2& size)
{
    m_size = size;
    m_bSpriteUpdate = true;
}
void CSprite::SetSize(cf32 fWidth, cf32 fHeight)
{
    m_size.x = fWidth; m_size.y = fHeight;
    m_bSpriteUpdate = true;
}
// �c���̕��擾
const vec2& CSprite::GetSize() const
{
    return m_size;
}

// �e�N�X�`���\���̈�ݒ�
void CSprite::SetTexRect(cf32 left, cf32 top, cf32 right, cf32 bottom)
{
    m_texPos.x = left;
    m_texPos.y = top;
    m_texSize.x = right - left;
    m_texSize.y = bottom - top;
    m_bSpriteUpdate = true;
}

// �e�N�X�`���\���J�n���W�ݒ�
void CSprite::SetTexPosU(cf32 u)
{
    m_texPos.x = u;
    m_bSpriteUpdate = true;
}
void CSprite::SetTexPosV(cf32 v)
{
    m_texPos.y = v;
    m_bSpriteUpdate = true;
}
void CSprite::SetTexPos(const vec2& pos)
{
    m_texPos.x = pos.x;
    m_texPos.y = pos.y;
    m_bSpriteUpdate = true;
}

// �e�N�X�`���\�����ݒ�
void CSprite::SetTexWidth(cf32 w)
{
    m_texSize.x = w;
    m_bSpriteUpdate = true;
}
void CSprite::SetTexHeight(cf32 h)
{
    m_texSize.y = h;
    m_bSpriteUpdate = true;
}
void CSprite::SetTexSize(const vec2& size)
{
    m_texSize.x = size.x;
    m_texSize.y = size.y;
    m_bSpriteUpdate = true;
}

// ������
HRESULT CSprite::Init(const SpriteDesc& desc)
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    // ���_�o�b�t�@
    VertexBufferDesc vtxDesc;
    vtxDesc.Size = sizeof(Vertex2D) * 4;
    vtxDesc.Usage = VTXUSAGE_WRITEONLY;
    vtxDesc.Pool = VTXPOOL_MANAGED;
    m_pVtxBuff = res->GetVertexBuffer(vtxDesc);
    _Assert(m_pVtxBuff);
    // �p�����[�^�ݒ�
    m_pVtxBuff->SetStreamIndex(0);
    m_pVtxBuff->SetOffset(0);
    m_pVtxBuff->SetStride(sizeof(Vertex2D));

    // �e�p�����[�^�ݒ�
    SetPosition(desc.pos);
    m_color = desc.color;
    m_size.x = desc.width;
    m_size.y = desc.height;
    
    VertexDeclarationDesc decl[] =
    {
        {0, 0, VDDECLTYPE_FLOAT3, VDDECLUSAGE_POSITION, 0},
        {0, 12, VDDECLTYPE_COLOR, VDDECLUSAGE_COLOR, 0},
        {0, 16, VDDECLTYPE_FLOAT2, VDDECLUSAGE_TEXCOORD, 0},
    };
    u8 declSize = sizeof(decl) / sizeof(decl[0]);
    m_pDecl = res->GetVertexDeclaration(declSize, decl);

    // �o�b�t�@�X�V
    UpdateBuffer();

    return S_OK;
}

HRESULT CSprite::Init(const SpriteDesc& desc, cs8* pFileName)
{
    INIT_CHECK(Init(desc));
    SetTexture(pFileName, desc.useTexSize);
    
    return S_OK;
}

// �o�b�t�@�X�V
void CSprite::UpdateBuffer()
{
    Vertex2D* pVtx = nullptr;
    m_pVtxBuff->Lock((void**)&pVtx);
    // ���_
    cf32 hw = m_size.x * 0.5f;  // Half Width
    cf32 hh = m_size.y * 0.5f;  // Half Height
    pVtx[0].pos = vec3(-hw, -hh, 0);
    pVtx[1].pos = vec3( hw, -hh, 0);
    pVtx[2].pos = vec3(-hw,  hh, 0);
    pVtx[3].pos = vec3( hw,  hh, 0);
    // �F
    for(int i = 0; i < 4; i++)
    {
        pVtx[i].color = m_color;
    }
    // �e�N�X�`��
    pVtx[0].texcoord.x = m_texPos.x;
    pVtx[0].texcoord.y = m_texPos.y;
    pVtx[1].texcoord.x = m_texPos.x + m_texSize.x;
    pVtx[1].texcoord.y = m_texPos.y;
    pVtx[2].texcoord.x = m_texPos.x;
    pVtx[2].texcoord.y = m_texPos.y + m_texSize.y;
    pVtx[3].texcoord.x = m_texPos.x + m_texSize.x;
    pVtx[3].texcoord.y = m_texPos.y + m_texSize.y;
    m_pVtxBuff->Unlock();

    m_bSpriteUpdate = false;
}

// EOF
