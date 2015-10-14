//=============================================================================
//
// ���\�[�X�Ǘ��N���X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <common/common.h>

#include <string>
#include <list>
#include <map>
#include <set>
#include <memory>

#include "../IResource.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CDeviceHolder;
class CLostResource;
class CFont;
class CTexture;
class CVertexDeclaration;
class CVertexBuffer;
class CIndexBuffer;
class CShader;
class CFrameBuffer;
class CColorBuffer;
class CDepthStencilBuffer;

//*****************************************************************************
// ���\�[�X�Ǘ��N���X
//*****************************************************************************
class CResourceManager
    : private CUncopyable
    , public IResource
{
private:

    /**
    * �R���X�g���N�^
    */
    CResourceManager();

    /**
    * �f�X�g���N�^
    */
    ~CResourceManager();

public:

    /**
    * ������
    * @ret ���\�[�X�}�l�[�W���[
    * @param pHolder �f�o�C�X�z���_�[
    */
    static CResourceManager* Create(CDeviceHolder* pHolder);

    /**
    * �J��
    */
    void Release();

    /**
    * ���\�[�X�ď�����
    */
    void Reset();

    /**
    * �t�H���g�C���^�[�t�F�[�X�̎擾
    * @ret �t�H���g�C���^�[�t�F�[�X
    * @param desc �t�H���g���
    */
    IFont* GetFont(const FontDesc& desc);
    /**
    * �t�H���g�J��
    * @param pTex �t�H���g�C���^�[�t�F�[�X
    */
    void Release(IFont* pFont);

    /**
    * �e�N�X�`���̎擾
    */
    ITexture* GetTexture(cs8* pFileName);
    /**
    * �e�N�X�`���̎擾
    */
    ITexture* GetTexture(const TextureDesc& desc);
    /**
    * �e�N�X�`���J��
    * @param pTex �e�N�X�`���C���^�[�t�F�[�X
    */
    void Release(ITexture* pTex);

    /**
    * ���_�錾�̎擾
    * @ret ���_�錾�C���^�[�t�F�[�X
    * @param desc ���_�錾���
    */
    IVertexDeclaration* GetVertexDeclaration(u8 uNumElems, const VertexDeclarationDesc* pDesc);
    /**
    * ���_�錾�J��
    * @param pTex ���_�錾�C���^�[�t�F�[�X
    */
    void Release(IVertexDeclaration* pDecl);

    /**
    * ���_�o�b�t�@�̎擾
    * @ret ���_�o�b�t�@�C���^�[�t�F�[�X
    * @param desc ���_�o�b�t�@���
    */
    IVertexBuffer* GetVertexBuffer(const VertexBufferDesc& desc);
    /**
    * �e�N�X�`���J��
    * @param pTex �e�N�X�`���C���^�[�t�F�[�X
    */
    void Release(IVertexBuffer* pVtx);

    /**
    * �C���f�b�N�X�o�b�t�@�̎擾
    * @ret �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X
    * @param desc �C���f�b�N�X�o�b�t�@���
    */
    IIndexBuffer* GetIndexBuffer(const IndexBufferDesc& desc);
    /**
    * �C���f�b�N�X�J��
    * @param pTex �C���f�b�N�X�C���^�[�t�F�[�X
    */
    void Release(IIndexBuffer* pIdx);
    
    /**
    * �V�F�[�_�̎擾
    * @ret �V�F�[�_�C���^�[�t�F�[�X
    * @param pVertexShader ���_�V�F�[�_
    * @param pPixelShader �s�N�Z���V�F�[�_
    */
    IShader* GetShader(
        const s8* pVertexShader,
        const s8* pPixelShader);
    /**
    * �V�F�[�_�J��
    * @param pSh �V�F�[�_�C���^�[�t�F�[�X
    */
    void Release(IShader* pSh);
    
    /**
    * �t���[���o�b�t�@�̎擾
    * @ret �t���[���o�b�t�@�C���^�[�t�F�[�X
    */
    IFrameBuffer* GetFrameBuffer();
    /**
    * �t���[���o�b�t�@�J��
    * @param pSh �t���[���o�b�t�@�C���^�[�t�F�[�X
    */
    void Release(IFrameBuffer* pFB);

    /**
    * �J���[�o�b�t�@�̎擾
    * @ret �J���[�o�b�t�@�C���^�[�t�F�[�X
    */
    IColorBuffer* GetColorBuffer(const ColorBufferDesc& desc);
    /**
    * �J���[�o�b�t�@�J��
    * @param pSh �J���[�o�b�t�@�C���^�[�t�F�[�X
    */
    void Release(IColorBuffer* pCB);

    /**
    * �[�x�o�b�t�@�̎擾
    * @ret �[�x�o�b�t�@�C���^�[�t�F�[�X
    */
    IDepthStencilBuffer* GetDepthStencilBuffer(const DepthStencilBufferDesc& desc);
    /**
    * �[�x�o�b�t�@�J��
    * @param pDS �[�x�o�b�t�@�C���^�[�t�F�[�X
    */
    void Release(IDepthStencilBuffer* pDS);

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT Init(CDeviceHolder* pHolder);

    /**
    * ���X�g��Ԃ̃`�F�b�N
    * @ret true:���X�g�� false:���A
    */
    bool IsLost();
    
    /**
    * ���O�t���e�N�X�`���̊J��
    * @param pTex �e�N�X�`��
    */
    void ReleaseNamedTexture(ITexture* pTex);

    /**
    * ���O�Ȃ��e�N�X�`���J��
    * @param pTex �e�N�X�`��
    */
    void ReleaseUnnamedTexture(ITexture* pTex);

private:

    // �f�o�C�X�z���_�[
    CDeviceHolder* m_pHolder;

    // ���X�g���\�[�X���X�g
    std::list<CLostResource*> m_listLostRes;

    // �t�H���g
    std::set<CFont*> m_setFont;

    // �e�N�X�`�����X�g
    std::set<CTexture*> m_setTextures;
    std::map<std::string, CTexture*> m_mapTextures;

    // ���_�錾���X�g
    std::set<CVertexDeclaration*> m_setVertexDecl;

    // ���_�o�b�t�@���X�g
    std::set<CVertexBuffer*> m_setVertexBuffer;

    // �C���f�b�N�X�o�b�t�@���X�g
    std::set<CIndexBuffer*> m_setIndexBuffer;

    // �V�F�[�_���X�g
    std::set<CShader*> m_setShader;
    
    // �t���[���o�b�t�@���X�g
    std::set<CFrameBuffer*> m_setFB;
    // �J���[�o�b�t�@���X�g
    std::set<CColorBuffer*> m_setCB;
    // �[�x�o�b�t�@���X�g
    std::set<CDepthStencilBuffer*> m_setDS;
};

#endif  // __RESOURCE_MANAGER_H__

// EOF
