//=============================================================================
//
// �e�N�X�`��
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <common/DirectX.h>
#include "CDeviceHolder.h"
#include "CLostResource.h"
#include "../ITexture.h"
#include "../TextureDesc.h"

//*****************************************************************************
// �e�N�X�`���N���X
//*****************************************************************************
class CTexture
    : public CLostResource
    , public ITexture
{
private:

    /**
    * �R���X�g���N�^
    */
    CTexture();

    /**
    * �f�X�g���N�^
    */
    ~CTexture();

public:

    /**
    * ����
    * @ret �e�N�X�`��
    * @param pHolder �f�o�C�X�z���_�[
    * @param pFileName �t�@�C����
    */
    static CTexture* Create(CDeviceHolder* pHolder, cs8* pFileName);

    /**
    * ����
    * @ret �e�N�X�`��
    * @param pHolder �f�o�C�X�z���_�[
    * @param desc �e�N�X�`�����
    */
    static CTexture* Create(CDeviceHolder* pHolder, const TextureDesc& desc);

    /**
    * �J��
    */
    void Release();

    // LostResource
    /**
    * ���\�[�X�̋����I�ȍ폜
    */
    void CleanUp();

    /**
    * ���\�[�X���̕ۑ�
    */
    void Restore();

    /**
    * ���\�[�X���̍ēǂݍ���
    */
    void Reload(CDeviceHolder* pHolder);

    // ITexture
    /**
    * �e�N�X�`���擾
    * @ret DirectX�e�N�X�`���C���^�[�t�F�[�X
    */
    LPDIRECT3DTEXTURE9 GetTexture() const;

    /**
    * �T�[�t�F�X�擾
    * @ret DirectX�T�[�t�F�X�C���^�[�t�F�[�X
    */
    LPDIRECT3DSURFACE9 GetSurface() const;

    /**
    * �����擾
    * @ret ����
    */
    u32 GetWidth() const;

    /**
    * �c���擾
    * @ret �c��
    */
    u32 GetHeight() const;

    /**
    * ���O�擾
    * @ret ���O
    */
    const std::string& GetName() const;

    /**
    * �K�p
    */
    void Attach();
    /**
    * ����
    */
    void Detach();

    /**
    * �e�N�X�`���X�e�[�W�C���f�b�N�X�ݒ�
    * @param index �C���f�b�N�X
    */
    void SetIndex(u32 index);

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    * @param pHolder �f�o�C�X�z���_�[
    * @param pFileName �t�@�C����
    */
    HRESULT Init(CDeviceHolder* pHolder, cs8* pFileName);

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    * @param pHolder �f�o�C�X�z���_�[
    * @param desc �e�N�X�`�����
    */
    HRESULT Init(CDeviceHolder* pHolder, const TextureDesc& desc);

private:

    // �e�N�X�`��
    LPDIRECT3DTEXTURE9 m_pTex;

    // �T�[�t�F�X
    LPDIRECT3DSURFACE9 m_pSurface;

    // �e�N�X�`�����
    D3DSURFACE_DESC m_desc;

    // ���O
    std::string m_strName;

    LPDIRECT3DDEVICE9 m_pDev;

    u32 m_index;
};

#endif  // __TEXTURE_H__

// EOF
