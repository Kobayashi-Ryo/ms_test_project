//=============================================================================
//
// 球体
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SPHERE_H__
#define __SPHERE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CNode.h"
#include "Vertex3D.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class IVertexBuffer;
class IVertexDeclaration;
class IIndexBuffer;
class ITexture;

//*****************************************************************************
// 球体情報
//*****************************************************************************
struct SphereDesc
{
    vec3 center;    // 座標
    f32 radius;     // 半径
    bool outside;  // 外向きかどうか
    u16 div;        // 分割数
    D3DXCOLOR color; // 色

    SphereDesc()
        : center(0,0,0)
        , radius(1.0f)
        , outside(true)
        , div(8)
        , color(1,1,1,1)
    {}
};

//*****************************************************************************
// 球体
//*****************************************************************************
class CSphere
    : public CNode
{
public:

    CSphere();
    ~CSphere();

    static CSphere* Create();
    static CSphere* Create(const SphereDesc& desc, cs8* pFileName);

    // 描画
    virtual void Draw();
    
    // 色設定
    void SetColor(const D3DXCOLOR& color);
    void SetColor(cf32 r, cf32 g, cf32 b);
    // 色取得
    const D3DXCOLOR& GetColor() const;

    // アルファ値設定
    void SetAlpha(cf32 a);
    // アルファ値取得
    f32 GetAlpha() const;

    // テクスチャ設定
    void SetTexture(cs8* pFileName);
    void SetTexture(ITexture* pTex);

    // 半径設定
    void SetRadius(cf32 radius);
    // 半径取得
    f32 GetRadius() const;

private:

    // 初期化
    bool Init(const SphereDesc& desc, cs8* pFileName);

    // 半球生成
    void SetSphere(bool bOutside);

private:

    // 頂点バッファ
    IVertexBuffer* m_pVtxBuff;
    // 頂点宣言
    IVertexDeclaration* m_pDecl;

    // インデックスバッファ
    IIndexBuffer* m_pIdxBuff;

    // テクスチャ
    ITexture* m_pTex;

    // 色情報
    D3DXCOLOR m_color;

    // 半径
    f32 m_fRadius;

    // 分割数
    u16 m_uDiv;
    
    // 頂点数
    u32 m_uNumVertex;
    // プリミティブ数
    u32 m_uNumPrimitive;

    bool m_bSphereUpdate;
};

#endif  // __SPHERE_H__

// EOF
