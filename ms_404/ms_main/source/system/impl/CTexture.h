//=============================================================================
//
// テクスチャ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/DirectX.h>
#include "CDeviceHolder.h"
#include "CLostResource.h"
#include "../ITexture.h"
#include "../TextureDesc.h"

//*****************************************************************************
// テクスチャクラス
//*****************************************************************************
class CTexture
    : public CLostResource
    , public ITexture
{
private:

    /**
    * コンストラクタ
    */
    CTexture();

    /**
    * デストラクタ
    */
    ~CTexture();

public:

    /**
    * 生成
    * @ret テクスチャ
    * @param pHolder デバイスホルダー
    * @param pFileName ファイル名
    */
    static CTexture* Create(CDeviceHolder* pHolder, cs8* pFileName);

    /**
    * 生成
    * @ret テクスチャ
    * @param pHolder デバイスホルダー
    * @param desc テクスチャ情報
    */
    static CTexture* Create(CDeviceHolder* pHolder, const TextureDesc& desc);

    /**
    * 開放
    */
    void Release();

    // LostResource
    /**
    * リソースの強制的な削除
    */
    void CleanUp();

    /**
    * リソース情報の保存
    */
    void Restore();

    /**
    * リソース情報の再読み込み
    */
    void Reload(CDeviceHolder* pHolder);

    // ITexture
    /**
    * テクスチャ取得
    * @ret DirectXテクスチャインターフェース
    */
    LPDIRECT3DTEXTURE9 GetTexture() const;

    /**
    * サーフェス取得
    * @ret DirectXサーフェスインターフェース
    */
    LPDIRECT3DSURFACE9 GetSurface() const;

    /**
    * 横幅取得
    * @ret 横幅
    */
    u32 GetWidth() const;

    /**
    * 縦幅取得
    * @ret 縦幅
    */
    u32 GetHeight() const;

    /**
    * 名前取得
    * @ret 名前
    */
    const std::string& GetName() const;

    /**
    * 適用
    */
    void Attach();
    /**
    * 解除
    */
    void Detach();

    /**
    * テクスチャステージインデックス設定
    * @param index インデックス
    */
    void SetIndex(u32 index);

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    * @param pHolder デバイスホルダー
    * @param pFileName ファイル名
    */
    HRESULT Init(CDeviceHolder* pHolder, cs8* pFileName);

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    * @param pHolder デバイスホルダー
    * @param desc テクスチャ情報
    */
    HRESULT Init(CDeviceHolder* pHolder, const TextureDesc& desc);

private:

    // テクスチャ
    LPDIRECT3DTEXTURE9 m_pTex;

    // サーフェス
    LPDIRECT3DSURFACE9 m_pSurface;

    // テクスチャ情報
    D3DSURFACE_DESC m_desc;

    // 名前
    std::string m_strName;

    LPDIRECT3DDEVICE9 m_pDev;

    u32 m_index;
};

#endif  // __TEXTURE_H__

// EOF
