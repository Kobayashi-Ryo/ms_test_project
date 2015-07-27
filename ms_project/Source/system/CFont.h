//=============================================================================
//
// フォント
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __FONT_H__
#define __FONT_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "D3DX.h"
#include "IFont.h"
#include "CLostResource.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// フォントクラス
//*****************************************************************************
class CFont
    : public CLostResource
    , public IFont
{
private:

    CFont();

    ~CFont();

public:

    static CFont* Create(CDeviceHolder* pHolder, const FontDesc& desc);

    void Draw(RECT& rect, cs8* pString);

    void Release();

    void CleanUp();

    void Restore();

    void Reload(CDeviceHolder* pHolder);

private:

    HRESULT Init(CDeviceHolder* pHolder, const FontDesc& desc);

private:

    // DirectXデバッグ表示用フォント
    LPD3DXFONT m_pFont;

    // フォント情報
    D3DXFONT_DESC m_desc;
};

#endif  // __FONT_H__

// EOF
