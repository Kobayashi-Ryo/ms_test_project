//=============================================================================
//
// シェーダクラス [CShader.h]
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/DirectX.h>
#include <common/D3DX.h>
#include "../IShader.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// クラス
//*****************************************************************************
class CShader
    : public IShader
{
public:

    static CShader* Create(
        CDeviceHolder* pHolder,
        const s8* pVertexShader,
        const s8* pPixelShader);

    void Release();
    
    void Attach();
    void Detach();

    void SetDevice(LPDIRECT3DDEVICE9 pDev);

    void SetBool(ShaderType type, D3DXHANDLE handle, bool data);
    void SetInt(ShaderType type, D3DXHANDLE handle, int data);
    void SetFloat(ShaderType type, D3DXHANDLE handle, float data);
    void SetVector(ShaderType type, D3DXHANDLE handle, const D3DXVECTOR4* data);
    void SetMatrix(ShaderType type, D3DXHANDLE handle, const D3DXMATRIX* data, bool transpose = false);
    void SetValue(ShaderType type, D3DXHANDLE handle, void* data, int size);

    D3DXHANDLE GetUniformHandle(ShaderType type, char* pName);

    unsigned GetTextureIndex(char* pName);

private:

    ShaderType DetectType(const char* pFileName);

    void CompileVS(const char* pFileName);
    void CompilePS(const char* pFileName);

    CShader();
    CShader(const CShader&){}
    CShader& operator=(const CShader&){}

private:

    LPDIRECT3DVERTEXSHADER9 m_pVtxShader;
    LPDIRECT3DPIXELSHADER9 m_pPixShader;
    
    LPDIRECT3DVERTEXSHADER9 m_pPrevVtxShader;
    LPDIRECT3DPIXELSHADER9 m_pPrevPixShader;

    LPD3DXCONSTANTTABLE m_apConst[MAX];

    LPDIRECT3DDEVICE9 m_pDev;
};

#endif  // __SHADER_H__

// EOF