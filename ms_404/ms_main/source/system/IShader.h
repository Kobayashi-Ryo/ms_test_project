//=============================================================================
//
// �V�F�[�_�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SHADER_INTERFACE_H__
#define __SHADER_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <common/D3DX.h>

//*****************************************************************************
// �N���X
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
    * �K�p
    */
    virtual void Attach() = 0;
    /**
    * ����
    */
    virtual void Detach() = 0;

    /**
    * �V�F�[�_�ɒl�𑗂鏈��
    */
    virtual void SetBool(ShaderType type, D3DXHANDLE handle, bool data) = 0;
    virtual void SetInt(ShaderType type, D3DXHANDLE handle, int data) = 0;
    virtual void SetFloat(ShaderType type, D3DXHANDLE handle, float data) = 0;
    virtual void SetVector(ShaderType type, D3DXHANDLE handle, const D3DXVECTOR4* data) = 0;
    virtual void SetMatrix(ShaderType type, D3DXHANDLE handle, const D3DXMATRIX* data, bool transpose = false) = 0;
    virtual void SetValue(ShaderType type, D3DXHANDLE handle, void* data, int size) = 0;

    /**
    * uniform�̃n���h���擾
    */
    virtual D3DXHANDLE GetUniformHandle(ShaderType type, char* pName) = 0;

    /**
    * �e�N�X�`���C���f�b�N�X�擾
    */
    virtual unsigned GetTextureIndex(char* pName) = 0;
};

#endif  // __SHADER_H__

// EOF
