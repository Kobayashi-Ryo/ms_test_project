//=============================================================================
//
// DirectX拡張処理
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "D3DX.h"
#include "common.h"
#include "DebugUtil.h"

//=============================================================================
// ワールド行列
//=============================================================================
D3DXMATRIX* D3DXMatrixWorld(D3DXMATRIX* pOut, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scl)
{
    _Assert(pOut);
    
    // 変数宣言
    f32 CosX = cosf(rot.x);
    f32 SinX = sinf(rot.x);
    f32 CosY = cosf(rot.y);
    f32 SinY = sinf(rot.y);
    f32 CosZ = cosf(rot.z);
    f32 SinZ = sinf(rot.z);

    // 行列要素設定
    pOut->_11 = (CosY * CosZ - SinY * SinX * SinZ) * scl.x;
    pOut->_12 = (CosY * SinZ + SinY * SinX * CosZ) * scl.x;
    pOut->_13 = (-SinY * CosX) * scl.x;

    pOut->_21 = (-CosX * SinZ) * scl.y;
    pOut->_22 = (CosX * CosZ) * scl.y;
    pOut->_23 = SinX * scl.y;

    pOut->_31 = (SinY * CosZ + CosY * SinX * SinZ) * scl.z;
    pOut->_32 = (SinY * SinZ - CosY * SinX * CosZ) * scl.z;
    pOut->_33 = (CosY * CosX) * scl.z;

    pOut->_41 = pos.x;
    pOut->_42 = pos.y;
    pOut->_43 = pos.z;

    pOut->_14 = pOut->_24 = pOut->_34 = 0.0f;
    pOut->_44 = 1.0f;
    return pOut;
}

// EOF
