//=============================================================================
//
// シェーダインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SHADER_INTERFACE_H__
#define __SHADER_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/D3DX.h>

//*****************************************************************************
// クラス
//*****************************************************************************
class IShader
{
public:

    enum ShaderType
    {
        VERTEX = 0,
        PIXEL,
        MAX
    };
    
    /**
    * 適用
    */
    virtual void Attach() = 0;
    /**
    * 解除
    */
    virtual void Detach() = 0;

    /**
    * シェーダに値を送る処理
    */
    virtual void SetBool(ShaderType type, D3DXHANDLE handle, bool data) = 0;
    virtual void SetInt(ShaderType type, D3DXHANDLE handle, int data) = 0;
    virtual void SetFloat(ShaderType type, D3DXHANDLE handle, float data) = 0;
    virtual void SetVector(ShaderType type, D3DXHANDLE handle, const D3DXVECTOR4* data) = 0;
    virtual void SetMatrix(ShaderType type, D3DXHANDLE handle, const D3DXMATRIX* data, bool transpose = false) = 0;
    virtual void SetValue(ShaderType type, D3DXHANDLE handle, void* data, int size) = 0;

    /**
    * uniformのハンドル取得
    */
    virtual D3DXHANDLE GetUniformHandle(ShaderType type, char* pName) = 0;

    /**
    * テクスチャインデックス取得
    */
    virtual unsigned GetTextureIndex(char* pName) = 0;
};

#endif  // __SHADER_H__

// EOF
