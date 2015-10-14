//=============================================================================
//
// �V�F�[�_�N���X [CShader.h]
// Author : Ryo Kobayashi
// Date : 2015/5/2
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CShader.h"
#include <string>
#include <common/DebugUtil.h>
#include "CDeviceHolder.h"

//*****************************************************************************
// ���O���
//*****************************************************************************
namespace
{
    const char* PATH = "resource/shader/";

    const char* VS_VERSION = "vs_3_0";
    const char* PS_VERSION = "ps_3_0";

    const char* VS_ENTRY_POINT = "VS";
    const char* PS_ENTRY_POINT = "PS";
}

//*****************************************************************************
// �V�F�[�_�^�C�v
//*****************************************************************************
struct ShaderType
{
    CShader::ShaderType type;
    const char* type_name;
};

//*****************************************************************************
// �V�F�[�_�^�C�v�萔
//*****************************************************************************
static const ShaderType SHADER_TYPE[] =
{
    {CShader::VERTEX, "vs"},
    {CShader::PIXEL, "ps"}
};

//=============================================================================
// ��������
//=============================================================================
CShader* CShader::Create(
        CDeviceHolder* pHolder,
        const s8* pVertexShader,
        const s8* pPixelShader)
{
    CShader* pShader = new CShader();

    pShader->SetDevice(pHolder->GetDevice());
    pShader->CompileVS(pVertexShader);
    pShader->CompilePS(pPixelShader);

    return pShader;
}

//=============================================================================
// �J��
//=============================================================================
void CShader::Release()
{
    SafeRelease(m_pVtxShader);
    SafeRelease(m_pPixShader);

    for(int i = 0; i < CShader::MAX; i++)
    {
        SafeRelease(m_apConst[i]);
    }

    delete this;
}

//=============================================================================
// �f�o�C�X�ݒ�
//=============================================================================
void CShader::SetDevice(LPDIRECT3DDEVICE9 pDev)
{
    m_pDev = pDev;
}

//=============================================================================
// �g�p�J�n
//=============================================================================
void CShader::Attach()
{
    if(m_pDev)
    {
        m_pDev->GetVertexShader(&m_pPrevVtxShader);
        m_pDev->GetPixelShader(&m_pPrevPixShader);

        m_pDev->SetVertexShader(m_pVtxShader);
        m_pDev->SetPixelShader(m_pPixShader);
    }
}

//=============================================================================
// �g�p�I��
//=============================================================================
void CShader::Detach()
{
    if(m_pDev)
    {
        m_pDev->SetVertexShader(m_pPrevVtxShader);
        m_pDev->SetPixelShader(m_pPrevPixShader);

        SafeRelease(m_pPrevVtxShader);
        SafeRelease(m_pPrevPixShader);
    }
}

//=============================================================================
// �u�[���l�ݒ�
//=============================================================================
void CShader::SetBool(CShader::ShaderType type, D3DXHANDLE handle, bool data)
{
    m_apConst[type]->SetBool(m_pDev, handle, data);

}
//=============================================================================
// �����l�ݒ�
//=============================================================================
void CShader::SetInt(CShader::ShaderType type, D3DXHANDLE handle, int data)
{
    m_apConst[type]->SetInt(m_pDev, handle, data);
}
//=============================================================================
// ���������l�ݒ�
//=============================================================================
void CShader::SetFloat(CShader::ShaderType type, D3DXHANDLE handle, float data)
{
    HRESULT hr;
    hr = m_apConst[type]->SetFloat(m_pDev, handle, data);
    if(FAILED(hr))
    {
        _asm int 3
    }
}
//=============================================================================
// �x�N�g���l�ݒ�
//=============================================================================
void CShader::SetVector(CShader::ShaderType type, D3DXHANDLE handle, const D3DXVECTOR4* data)
{
    m_apConst[type]->SetVector(m_pDev, handle, data);
}
//=============================================================================
// �s��l�ݒ�
//=============================================================================
void CShader::SetMatrix(CShader::ShaderType type, D3DXHANDLE handle, const D3DXMATRIX* data, bool transpose)
{
    HRESULT hr = E_FAIL;
    if(!transpose)
    {
        hr = m_apConst[type]->SetMatrix(m_pDev, handle, data);
    }
    else
    {
        hr = m_apConst[type]->SetMatrixTranspose(m_pDev, handle, data);
    }

    if(FAILED(hr))
    {
        __asm int 3;
    }
}
//=============================================================================
// �l�ݒ�
//=============================================================================
void CShader::SetValue(CShader::ShaderType type, D3DXHANDLE handle, void* data, int size)
{
    HRESULT hr = m_apConst[type]->SetValue(m_pDev, handle, data, size);
    if(FAILED(hr))
    {
        __asm int 3;
    }
}

//=============================================================================
// �^�C�v����
//=============================================================================
CShader::ShaderType CShader::DetectType(const char* pFileName)
{
    for(int i = 0; i < sizeof(SHADER_TYPE) / sizeof(SHADER_TYPE[0]); i++)
    {
        if(pFileName[0] == SHADER_TYPE[i].type_name[0] &&
           pFileName[1] == SHADER_TYPE[i].type_name[1])
        {
            return SHADER_TYPE[i].type;
        }
    }

    return MAX;
}

//=============================================================================
// ���_�V�F�[�_�R���p�C��
//=============================================================================
void CShader::CompileVS(const char* pFileName)
{
    std::string strPath(PATH);
    strPath += pFileName;
    HRESULT hr = E_FAIL;
    LPD3DXBUFFER err = nullptr;
    LPD3DXBUFFER code = nullptr;

#ifdef _DEBUG
    while(E_FAIL == hr)
    {
#endif
    // �V�F�[�_�R���p�C��
    hr = D3DXCompileShaderFromFile(
        strPath.c_str(),
        nullptr,
        nullptr,
        VS_ENTRY_POINT,
        VS_VERSION,
        0,
        &code,
        &err,
        &m_apConst[VERTEX]);
    if(FAILED(hr))
    {
        MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
        err->Release();
        err = (LPD3DXBUFFER)-1;
    }
#ifdef _DEBUG
    }
#endif

    if((LPD3DXBUFFER)-1 == err)
    {
        return;
    }

    // ���_�V�F�[�_����
    hr = m_pDev->CreateVertexShader(
        (DWORD*)code->GetBufferPointer(),
        &m_pVtxShader);
    if(FAILED(hr))
    {
        MessageBox(NULL, "VertexShaderFailed", "CreateVertexShader", MB_OK);
        return;
    }
    code->Release();
}

//=============================================================================
// �s�N�Z���V�F�[�_�R���p�C��
//=============================================================================
void CShader::CompilePS(const char* pFileName)
{
    std::string strPath(PATH);
    strPath += pFileName;
    HRESULT hr = E_FAIL;
    LPD3DXBUFFER err = nullptr;
    LPD3DXBUFFER code = nullptr;

#ifdef _DEBUG
    while(E_FAIL == hr)
    {
#endif
    // �s�N�Z���V�F�[�_�R���p�C��
    hr = D3DXCompileShaderFromFile(
        strPath.c_str(),
        nullptr,
        nullptr,
        PS_ENTRY_POINT,
        PS_VERSION,
        0,
        &code,
        &err,
        &m_apConst[PIXEL]);
    if(FAILED(hr))
    {
        MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
        err->Release();
        err = (LPD3DXBUFFER)-1;
    }
#ifdef _DEBUG
    }
#endif
    
    if((LPD3DXBUFFER)-1 == err)
    {
        return;
    }

    // �s�N�Z���V�F�[�_����
    hr = m_pDev->CreatePixelShader(
        (DWORD*)code->GetBufferPointer(),
        &m_pPixShader);
    if(FAILED(hr))
    {
        MessageBox(NULL, "PixelShaderFailed", "CreatePixelShader", MB_OK);
        return;
    }
    code->Release();
}

//=============================================================================
// �萔�n���h���擾
//=============================================================================
D3DXHANDLE CShader::GetUniformHandle(ShaderType type, char* pName)
{
    return m_apConst[type]->GetConstantByName(nullptr, pName);
}

//=============================================================================
// �e�N�X�`���C���f�b�N�X�擾
//=============================================================================
unsigned CShader::GetTextureIndex(char* pName)
{
    return m_apConst[PIXEL]->GetSamplerIndex(pName);
}
























CShader::CShader()
    : m_pVtxShader(nullptr)
    , m_pPrevVtxShader(nullptr)
    , m_pPixShader(nullptr)
    , m_pPrevPixShader(nullptr)
    , m_apConst()
    , m_pDev(nullptr)
{
}

// EOF