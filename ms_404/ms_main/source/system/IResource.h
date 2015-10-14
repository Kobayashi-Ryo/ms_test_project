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
#include <common/common.h>

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

// shader
#include "IShader.h"

// render buffer
#include "IFrameBuffer.h"
#include "IColorBuffer.h"
#include "IDepthStencilBuffer.h"

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
    * @param pDecl ���_�錾�C���^�[�t�F�[�X
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
    * @param pVtx ���_�o�b�t�@�C���^�[�t�F�[�X
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
    * @param pIdx �C���f�b�N�X�C���^�[�t�F�[�X
    */
    virtual void Release(IIndexBuffer* pIdx) = 0;

    // �V�F�[�_
    /**
    * �V�F�[�_�̎擾
    * @ret �V�F�[�_�C���^�[�t�F�[�X
    * @param pVertexShader ���_�V�F�[�_
    * @param pPixelShader �s�N�Z���V�F�[�_
    */
    virtual IShader* GetShader(
        const s8* pVertexShader,
        const s8* pPixelShader) = 0;
    /**
    * �V�F�[�_�J��
    * @param pSh �V�F�[�_�C���^�[�t�F�[�X
    */
    virtual void Release(IShader* pSh) = 0;

    // �t���[���o�b�t�@
    /**
    * �t���[���o�b�t�@�̎擾
    * @ret �t���[���o�b�t�@�C���^�[�t�F�[�X
    */
    virtual IFrameBuffer* GetFrameBuffer() = 0;
    /**
    * �t���[���o�b�t�@�J��
    * @param pSh �t���[���o�b�t�@�C���^�[�t�F�[�X
    */
    virtual void Release(IFrameBuffer* pFB) = 0;

    // �J���[�o�b�t�@
    /**
    * �J���[�o�b�t�@�̎擾
    * @ret �J���[�o�b�t�@�C���^�[�t�F�[�X
    */
    virtual IColorBuffer* GetColorBuffer(const ColorBufferDesc& desc) = 0;
    /**
    * �J���[�o�b�t�@�J��
    * @param pSh �J���[�o�b�t�@�C���^�[�t�F�[�X
    */
    virtual void Release(IColorBuffer* pCB) = 0;

    // �[�x�o�b�t�@
    /**
    * �[�x�o�b�t�@�̎擾
    * @ret �[�x�o�b�t�@�C���^�[�t�F�[�X
    */
    virtual IDepthStencilBuffer* GetDepthStencilBuffer(const DepthStencilBufferDesc& desc) = 0;
    /**
    * �[�x�o�b�t�@�J��
    * @param pDS �[�x�o�b�t�@�C���^�[�t�F�[�X
    */
    virtual void Release(IDepthStencilBuffer* pDS) = 0;

protected:

    virtual ~IResource(){}
};

#endif  // __RESOURCE_INTERFACE_H__

// EOF
