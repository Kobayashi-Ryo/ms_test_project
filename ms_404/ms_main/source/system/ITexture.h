//=============================================================================
//
// �e�N�X�`���C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __TEXTURE_INTERFACE_H__
#define __TEXTURE_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <common/DirectX.h>
#include <string>
#include "TextureDesc.h"

//*****************************************************************************
// �e�N�X�`���C���^�[�t�F�[�X
//*****************************************************************************
class ITexture
{
public:
    
    /**
    * �K�p
    */
    virtual void Attach() = 0;
    /**
    * ����
    */
    virtual void Detach() = 0;

    /**
    * �e�N�X�`���X�e�[�W�C���f�b�N�X�ݒ�
    * @param index �C���f�b�N�X
    */
    virtual void SetIndex(u32 index) = 0;

    /**
    * �e�N�X�`���擾
    * @ret DirectX�e�N�X�`���C���^�[�t�F�[�X
    */
    virtual LPDIRECT3DTEXTURE9 GetTexture() const = 0;

    /**
    * �T�[�t�F�X�擾
    * @ret DirectX�T�[�t�F�X�C���^�[�t�F�[�X
    */
    virtual LPDIRECT3DSURFACE9 GetSurface() const = 0;

    /**
    * �����擾
    * @ret ����
    */
    virtual u32 GetWidth() const = 0;

    /**
    * �c���擾
    * @ret �c��
    */
    virtual u32 GetHeight() const = 0;

    /**
    * ���O�擾
    * @ret ���O
    */
    virtual const std::string& GetName() const = 0;

protected:

    virtual ~ITexture(){}
};

#endif  // __TEXTURE_INTERFACE_H__

// EOF
