//=============================================================================
//
// デバイスを保持するクラス
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "CDeviceHolder.h"

// debug
#include "DebugUtil.h"


//*****************************************************************************
// 名前空間
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
// コンストラクタ
//=============================================================================
CDeviceHolder::CDeviceHolder()
    : m_pDev(nullptr)
    , m_uBackBufferWidth(0)
    , m_uBackBufferHeight(0)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CDeviceHolder::~CDeviceHolder()
{
    SafeRelease(m_pDev);
}

//=============================================================================
// 生成処理
//=============================================================================
CDeviceHolder* CDeviceHolder::Create(const DeviceDesc& desc)
{
    CDeviceHolder* pDev = new CDeviceHolder();

    if(pDev)
    {
        INIT_CHECK(pDev->Init(desc));
        _PrintConsole("デバイスホルダー\n");
    }

    return pDev;
}

//=============================================================================
// 開放処理
//=============================================================================
void CDeviceHolder::Release()
{
    delete this;
}

//=============================================================================
// DirectX9デバイス取得
//=============================================================================
LPDIRECT3DDEVICE9 CDeviceHolder::GetDevice() const
{
    return m_pDev;
}

//=============================================================================
// バックバッファ横幅取得
//=============================================================================
DWORD CDeviceHolder::GetBackBufferWidth() const
{
    return m_uBackBufferWidth;
}

//=============================================================================
// バックバッファ縦幅取得
//=============================================================================
DWORD CDeviceHolder::GetBackBufferHeight() const
{
    return m_uBackBufferHeight;
}

//=============================================================================
// デバイス情報取得
//=============================================================================
const D3DPRESENT_PARAMETERS& CDeviceHolder::GetPresentParameters() const
{
    return m_PresentParam;
}

//=============================================================================
// デバイスリセット
//=============================================================================
HRESULT CDeviceHolder::Reset()
{
    HRESULT hr = m_pDev->Reset(&m_PresentParam);
    //_Assert(D3DERR_INVALIDCALL != hr);
    return hr;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CDeviceHolder::Init(const DeviceDesc& desc)
{
    HRESULT hr = E_FAIL;
    
    // Direct3Dオブジェクトの生成
    LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if(IS_NULL(pD3D))
    {
        return E_FAIL;
    }

    // Direct3Dパラメータ設定
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    
    d3dpp.BackBufferCount           = 1;                        // バックバッファの数
    d3dpp.BackBufferFormat          = D3DFMT_UNKNOWN;           // バックバッファのフォーマットは現在設定されているものを使う
    d3dpp.SwapEffect                = D3DSWAPEFFECT_DISCARD;    // 映像信号に同期してフリップする
    d3dpp.hDeviceWindow             = desc.hWnd;
    d3dpp.Windowed                  = desc.bWindowed;           // ウィンドウモード
    d3dpp.EnableAutoDepthStencil    = TRUE;                     // デプスバッファ（Ｚバッファ）とステンシルバッファを作成
    d3dpp.AutoDepthStencilFormat    = D3DFMT_D24S8;             // デプスバッファとしてZバッファ24bit、ステンシルバッファ8bitを使う
    
    if(desc.bWindowed)
    {// ウィンドウモード
        d3dpp.FullScreen_RefreshRateInHz    = 0;                                // リフレッシュレート
        d3dpp.PresentationInterval          = D3DPRESENT_INTERVAL_IMMEDIATE;    // インターバル
        d3dpp.BackBufferWidth               = desc.uBackBufferWidth;            // ゲーム画面サイズ(幅)
        d3dpp.BackBufferHeight              = desc.uBackBufferHeight;           // ゲーム画面サイズ(高さ)
    }
    else
    {// フルスクリーンモード
        d3dpp.FullScreen_RefreshRateInHz    = D3DPRESENT_RATE_DEFAULT;          // リフレッシュレート
        d3dpp.PresentationInterval          = D3DPRESENT_INTERVAL_DEFAULT;      // インターバル
        // 現在のディスプレイモードを取得
        D3DDISPLAYMODE d3ddm;
        if(FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
        {
            return E_FAIL;
        }
        d3dpp.BackBufferFormat              = d3ddm.Format;
        d3dpp.BackBufferWidth               = d3ddm.Width;                      // 画面横幅
        d3dpp.BackBufferHeight              = d3ddm.Height;                     // 画面縦幅
    }

    // デバイス生成
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
    
    // レンダリングステート初期化
    m_pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);            // 裏面面カリング
    m_pDev->SetRenderState(D3DRS_ZENABLE, TRUE);                    // Zバッファを有効化
    m_pDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);            // アルファブレンドの有効化
    m_pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);    // 
    m_pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// 重なった時、薄いほうをより薄く、濃いほうをより濃く見えるように表示
    
    // サンプラーステートの設定
    m_pDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    m_pDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    m_pDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    m_pDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    m_pDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);    // ミップマップフィルタ


    // デバイス情報保存
    m_PresentParam = d3dpp;
    // バックバッファサイズ設定
    m_uBackBufferWidth = d3dpp.BackBufferWidth;
    m_uBackBufferHeight = d3dpp.BackBufferHeight;


    SafeRelease(pD3D);

    return hr;
}

// EOF
