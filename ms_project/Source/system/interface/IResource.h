//=============================================================================
//
// ���\�[�X�C���^�[�t�F�[�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __RESOURCE_INTERFACE_H__
#define __RESOURCE_INTERFACE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "common.h"

// font
#include "IFont.h"

// texture
#include "ITexture.h"

// surface

// declaration
#include "IVertexDeclaration.h"

// vertex
#include "IVertexBuffer.h"

// index
#include "IIndexBuffer.h"

//*****************************************************************************
// ���\�[�X�C���^�[�t�F�[�X
//*****************************************************************************
class IResource
{
public:

    // �t�H���g
    /**
    * �t�H���g�C���^�[�t�F�[�X�̎擾
    * @ret �t�H���g�C���^�[�t�F�[�X
    * @param desc �t�H���g���
    */
    virtual IFont* GetFont(const FontDesc& desc) = 0;
    /**
    * �t�H���g�J��
    * @param pTex �t�H���g�C���^�[�t�F�[�X
    */
    virtual void Release(IFont* pFont) = 0;

    // �e�N�X�`��
    /**
    * �e�N�X�`���̎擾
    * @ret �e�N�X�`���C���^�[�t�F�[�X
    * @param pFileName �e�N�X�`���t�@�C����
    */
    virtual ITexture* GetTexture(cs8* pFileName) = 0;
    /**
    * �e�N�X�`���̎擾
    * @ret �e�N�X�`���C���^�[�t�F�[�X
    * @param desc �e�N�X�`�����
    */
    virtual ITexture* GetTexture(const TextureDesc& desc) = 0;
    /**
    * �e�N�X�`���J��
    * @param pTex �e�N�X�`���C���^�[�t�F�[�X
    */
    virtual void Release(ITexture* pTex) = 0;

    // ���_�錾
    /**
    * ���_�錾�̎擾
    * @ret ���_�錾�C���^�[�t�F�[�X
    * @param desc ���_�錾���
    */
    virtual IVertexDeclaration* GetVertexDeclaration(u8 uNumDescs, const VertexDeclarationDesc* pDesc) = 0;
    /**
    * ���_�錾�J��
    * @param pTex ���_�錾�C���^�[�t�F�[�X
    */
    virtual void Release(IVertexDeclaration* pDecl) = 0;

    // ���_�o�b�t�@
    /**
    * ���_�o�b�t�@�̎擾
    * @ret ���_�o�b�t�@�C���^�[�t�F�[�X
    * @param desc ���_�o�b�t�@���
    */
    virtual IVertexBuffer* GetVertexBuffer(const VertexBufferDesc& desc) = 0;
    /**
    * ���_�o�b�t�@�J��
    * @param pTex ���_�o�b�t�@�C���^�[�t�F�[�X
    */
    virtual void Release(IVertexBuffer* pVtx) = 0;

    // �C���f�b�N�X�o�b�t�@
    /**
    * �C���f�b�N�X�o�b�t�@�̎擾
    * @ret �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X
    * @param desc �C���f�b�N�X�o�b�t�@���
    */
    virtual IIndexBuffer* GetIndexBuffer(const IndexBufferDesc& desc) = 0;
    /**
    * �C���f�b�N�X�J��
    * @param pTex �C���f�b�N�X�C���^�[�t�F�[�X
    */
    virtual void Release(IIndexBuffer* pIdx) = 0;

protected:

    virtual ~IResource(){}
};

#endif  // __RESOURCE_INTERFACE_H__

// EOF
