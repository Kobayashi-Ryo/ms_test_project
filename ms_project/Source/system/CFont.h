//=============================================================================
//
// �t�H���g
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __FONT_H__
#define __FONT_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "D3DX.h"
#include "IFont.h"
#include "CLostResource.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// �t�H���g�N���X
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

    // DirectX�f�o�b�O�\���p�t�H���g
    LPD3DXFONT m_pFont;

    // �t�H���g���
    D3DXFONT_DESC m_desc;
};

#endif  // __FONT_H__

// EOF
