//=============================================================================
//
// メッシュフィールド
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __MESHFIELD_H__
#define __MESHFIELD_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CNode.h"
#include "Vertex3D.h"
#include <functional>

//*****************************************************************************
// 前方参照
//*****************************************************************************
class IVertexBuffer;
class IVertexDeclaration;
class IIndexBuffer;
class ITexture;

//*****************************************************************************
// メッシュフィールド情報構造体
//*****************************************************************************
struct MeshFieldDesc
{
    vec3 center;
    u16 numXGrid;
    u16 numZGrid;
    f32 widthGrid;
    f32 depthGrid;
    s8* textureName;

    MeshFieldDesc()
        : center(0, 0, 0)
        , numXGrid(1)
        , numZGrid(1)
        , widthGrid(1.0f)
        , depthGrid(1.0f)
        , textureName(nullptr)
    {}
};

//*****************************************************************************
// クラス
//*****************************************************************************
class CMeshField
    : public CNode
{
public:

    CMeshField();
    ~CMeshField();

    // 生成
    static CMeshField* Create(const MeshFieldDesc& desc);

    // 描画
    virtual void Draw();

    // X方向頂点数
    u32 GetNumVertexX() const;
    // Z方向頂点数
    u32 GetNumVertexZ() const;

    // 頂点バッファ操作
    void ControlVertex(std::function<void(Vertex3D*, u32, u32)> func);

    // 横幅取得
    f32 GetWidth() const;

    // 奥行取得
    f32 GetDepth() const;

private:

    // 初期化
    bool Init(const MeshFieldDesc& desc);

private:

    // 頂点バッファ
    IVertexBuffer* m_pVtxBuff;
    // 頂点宣言
    IVertexDeclaration* m_pDecl;

    // インデックスバッファ
    IIndexBuffer* m_pIdxBuff;

    // テクスチャ
    ITexture* m_pTex;

    // 頂点数
    u32 m_uNumVtxX;
    u32 m_uNumVtxZ;

    // プリミティブ数
    u32 m_uNumPrimitive;

    // 横幅
    f32 m_fWidth;
    // 縦幅
    f32 m_fDepth;

};

#endif  // __MESHFIELD_H__

// EOF
