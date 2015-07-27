//=============================================================================
//
// スプライトクラス
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CNode.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class IVertexBuffer;
class ITexture;

//*****************************************************************************
// スプライト情報
//*****************************************************************************
struct SpriteDesc
{
    u8 vertexSize; // 頂点一つ当たりのバイトサイズ
    vec3 pos;
    f32 width;
    f32 height;
    D3DXCOLOR color;
    bool useTexSize;

    SpriteDesc()
        : vertexSize(0)
        , pos(0, 0, 0)
        , width(0)
        , height(0)
        , color(1,1,1,1)
        , useTexSize(false)
    {}
};

//*****************************************************************************
// スプライトクラス
//*****************************************************************************
class CSprite
    : public CNode
{
private:

    /**
    * コンストラクタ
    */
    CSprite();

    /**
    * デストラクタ
    */
    ~CSprite();

public:

    // 生成
    static CSprite* Create(const SpriteDesc& desc);
    static CSprite* Create(const SpriteDesc& desc, cs8* pFileName);

    // 更新
    void Update();
    // 描画
    void Draw();

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
    // 設定したときにテクスチャのサイズを設定したものに
    // 自動的に設定するフラグがあるよ
    void SetTexture(cs8* pFileName, bool bUseTexSize = false);
    void SetTexture(ITexture* pTex, bool bUseTexSize = false);

    // 横幅設定
    void SetWidth(cf32 fWidth);
    // 横幅取得
    f32 GetWidth() const;

    // 縦幅設定
    void SetHeight(cf32 fHeight);
    // 縦幅取得
    f32 GetHeight() const;

    // 縦横の幅設定
    void SetSize(const vec2& size);
    void SetSize(cf32 fWidth, cf32 fHeight);
    // 縦横の幅取得
    const vec2& GetSize() const;

private:

    // 初期化
    HRESULT Init(const SpriteDesc& desc);
    HRESULT Init(const SpriteDesc& desc, cs8* pFileName);

    // バッファ更新
    void UpdateBuffer();

private:

    // 頂点バッファ
    IVertexBuffer* m_pVtxBuff;

    // テクスチャ
    ITexture* m_pTex;

    // 色情報
    D3DXCOLOR m_color;

    // 幅
    vec2 m_size;
};

#endif  // __SPRITE_H__

// EOF
