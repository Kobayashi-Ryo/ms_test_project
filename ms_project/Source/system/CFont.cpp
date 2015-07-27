//=============================================================================
//
// �t�H���g
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CFont.h"
#include "CDeviceHolder.h"
#include "DebugUtil.h"

CFont::CFont()
    : m_pFont(nullptr)
{
}

CFont::~CFont()
{
    SafeRelease(m_pFont);
}

CFont* CFont::Create(CDeviceHolder* pHolder, const FontDesc& desc)
{
    CFont* pFont = new CFont();

    if(pFont)
    {
        INIT_CHECK(pFont->Init(pHolder, desc));
        _PrintConsole("�t�H���g");
    }

    return pFont;
}

void CFont::Draw(RECT& rect, cs8* pString)
{
    // �f�o�b�O�`��
    HR(m_pFont->DrawText(0, pString, -1, &rect, DT_NOCLIP, D3DCOLOR_RGBA(255, 255, 255, 255)));
}

void CFont::Release()
{
    CRef::Decrement();
}

void CFont::CleanUp()
{
    delete this;
}

void CFont::Restore()
{
    if(m_pFont) m_pFont->GetDesc(&m_desc);
    SafeRelease(m_pFont);
}

void CFont::Reload(CDeviceHolder* pHolder)
{
    // Font�쐬
    INIT_CHECK(D3DXCreateFontIndirect(pHolder->GetDevice(), &m_desc, &m_pFont));
}

HRESULT CFont::Init(CDeviceHolder* pHolder, const FontDesc& desc)
{
    // �f�o�C�X
    LPDIRECT3DDEVICE9 pDev = pHolder->GetDevice();

    // Font��񏉊���
    m_desc.Height          = desc.Height;      // �����̍���
    m_desc.Width           = desc.Width;       // �����̉���
    m_desc.Weight          = 0;                // �t�H���g�̃E�F�C�g
    m_desc.MipLevels       = 1;                // �~�b�v�}�b�v���x��
    m_desc.Italic          = desc.Italic;      // �C�^���b�N����
    m_desc.CharSet         = DEFAULT_CHARSET;    // �����Z�b�g
    m_desc.OutputPrecision = OUT_DEFAULT_PRECIS;// �o�͐��x
    m_desc.Quality         = DEFAULT_QUALITY;    // �o�͕i��
    m_desc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;// �t�H���g�̃s�b�`�ƃt�@�~��
    strcpy_s(m_desc.FaceName, sizeof(m_desc.FaceName), "Times New Roman");// �t�H���g�̃^�C�v�t�F�[�X��

    // Font�쐬
    INIT_CHECK(D3DXCreateFontIndirect(pDev, &m_desc, &m_pFont));
    
    // ����������
    return S_OK;
}

// EOF
