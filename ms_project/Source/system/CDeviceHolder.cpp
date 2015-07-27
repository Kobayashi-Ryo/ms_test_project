//=============================================================================
//
// �f�o�C�X��ێ�����N���X
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "CDeviceHolder.h"

// debug
#include "DebugUtil.h"


//*****************************************************************************
// ���O���
//*****************************************************************************
namespace
{
    struct DeviceParameters
    {
        int nAdapter;
        D3DDEVTYPE d3dDevType;
        int nVertexProcessing;
    };

    static const DeviceParameters DEV_PARAMS[] =
    {
        {
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            D3DCREATE_HARDWARE_VERTEXPROCESSING
        },
        {
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING
        },
        {
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_REF,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING
        },
    };
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDeviceHolder::CDeviceHolder()
    : m_pDev(nullptr)
    , m_uBackBufferWidth(0)
    , m_uBackBufferHeight(0)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDeviceHolder::~CDeviceHolder()
{
    SafeRelease(m_pDev);
}

//=============================================================================
// ��������
//=============================================================================
CDeviceHolder* CDeviceHolder::Create(const DeviceDesc& desc)
{
    CDeviceHolder* pDev = new CDeviceHolder();

    if(pDev)
    {
        INIT_CHECK(pDev->Init(desc));
        _PrintConsole("�f�o�C�X�z���_�[\n");
    }

    return pDev;
}

//=============================================================================
// �J������
//=============================================================================
void CDeviceHolder::Release()
{
    delete this;
}

//=============================================================================
// DirectX9�f�o�C�X�擾
//=============================================================================
LPDIRECT3DDEVICE9 CDeviceHolder::GetDevice() const
{
    return m_pDev;
}

//=============================================================================
// �o�b�N�o�b�t�@�����擾
//=============================================================================
DWORD CDeviceHolder::GetBackBufferWidth() const
{
    return m_uBackBufferWidth;
}

//=============================================================================
// �o�b�N�o�b�t�@�c���擾
//=============================================================================
DWORD CDeviceHolder::GetBackBufferHeight() const
{
    return m_uBackBufferHeight;
}

//=============================================================================
// �f�o�C�X���擾
//=============================================================================
const D3DPRESENT_PARAMETERS& CDeviceHolder::GetPresentParameters() const
{
    return m_PresentParam;
}

//=============================================================================
// �f�o�C�X���Z�b�g
//=============================================================================
HRESULT CDeviceHolder::Reset()
{
    HRESULT hr = m_pDev->Reset(&m_PresentParam);
    //_Assert(D3DERR_INVALIDCALL != hr);
    return hr;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CDeviceHolder::Init(const DeviceDesc& desc)
{
    HRESULT hr = E_FAIL;
    
    // Direct3D�I�u�W�F�N�g�̐���
    LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if(IS_NULL(pD3D))
    {
        return E_FAIL;
    }

    // Direct3D�p�����[�^�ݒ�
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    
    d3dpp.BackBufferCount           = 1;                        // �o�b�N�o�b�t�@�̐�
    d3dpp.BackBufferFormat          = D3DFMT_UNKNOWN;           // �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
    d3dpp.SwapEffect                = D3DSWAPEFFECT_DISCARD;    // �f���M���ɓ������ăt���b�v����
    d3dpp.hDeviceWindow             = desc.hWnd;
    d3dpp.Windowed                  = desc.bWindowed;           // �E�B���h�E���[�h
    d3dpp.EnableAutoDepthStencil    = TRUE;                     // �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
    d3dpp.AutoDepthStencilFormat    = D3DFMT_D24S8;             // �f�v�X�o�b�t�@�Ƃ���Z�o�b�t�@24bit�A�X�e���V���o�b�t�@8bit���g��
    
    if(desc.bWindowed)
    {// �E�B���h�E���[�h
        d3dpp.FullScreen_RefreshRateInHz    = 0;                                // ���t���b�V�����[�g
        d3dpp.PresentationInterval          = D3DPRESENT_INTERVAL_IMMEDIATE;    // �C���^�[�o��
        d3dpp.BackBufferWidth               = desc.uBackBufferWidth;            // �Q�[����ʃT�C�Y(��)
        d3dpp.BackBufferHeight              = desc.uBackBufferHeight;           // �Q�[����ʃT�C�Y(����)
    }
    else
    {// �t���X�N���[�����[�h
        d3dpp.FullScreen_RefreshRateInHz    = D3DPRESENT_RATE_DEFAULT;          // ���t���b�V�����[�g
        d3dpp.PresentationInterval          = D3DPRESENT_INTERVAL_DEFAULT;      // �C���^�[�o��
        // ���݂̃f�B�X�v���C���[�h���擾
        D3DDISPLAYMODE d3ddm;
        if(FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
        {
            return E_FAIL;
        }
        d3dpp.BackBufferFormat              = d3ddm.Format;
        d3dpp.BackBufferWidth               = d3ddm.Width;                      // ��ʉ���
        d3dpp.BackBufferHeight              = d3ddm.Height;                     // ��ʏc��
    }

    // �f�o�C�X����
    for(int i = 0; i < sizeof(DEV_PARAMS) / sizeof(DEV_PARAMS[0]); i++)
    {
        hr = pD3D->CreateDevice(
            DEV_PARAMS[i].nAdapter,
            DEV_PARAMS[i].d3dDevType,
            desc.hWnd,
            DEV_PARAMS[i].nVertexProcessing,
            &d3dpp,
            &m_pDev);
        if(SUCCEEDED(hr))
        {
            break;
        }
    }
    _CriticalAssert(m_pDev);
    
    // �����_�����O�X�e�[�g������
    m_pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);            // ���ʖʃJ�����O
    m_pDev->SetRenderState(D3DRS_ZENABLE, TRUE);                    // Z�o�b�t�@��L����
    m_pDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);            // �A���t�@�u�����h�̗L����
    m_pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);    // 
    m_pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// �d�Ȃ������A�����ق�����蔖���A�Z���ق������Z��������悤�ɕ\��
    
    // �T���v���[�X�e�[�g�̐ݒ�
    m_pDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    m_pDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    m_pDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    m_pDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    m_pDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);    // �~�b�v�}�b�v�t�B���^


    // �f�o�C�X���ۑ�
    m_PresentParam = d3dpp;
    // �o�b�N�o�b�t�@�T�C�Y�ݒ�
    m_uBackBufferWidth = d3dpp.BackBufferWidth;
    m_uBackBufferHeight = d3dpp.BackBufferHeight;


    SafeRelease(pD3D);

    return hr;
}

// EOF
