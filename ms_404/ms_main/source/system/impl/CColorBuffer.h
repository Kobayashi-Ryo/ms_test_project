//=============================================================================
//
// �J���[�o�b�t�@
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __COLOR_BUFFER_H__
#define __COLOR_BUFFER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../IColorBuffer.h"
#include "CLostResource.h"
#include <common/DirectX.h>
#include <common/CUncopyable.h>

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CDeviceHolder;
class CTexture;

class CColorBuffer
    : public IColorBuffer
    , public CLostResource
{
public:

    static CColorBuffer* Create(CDeviceHolder* pHolder, const ColorBufferDesc& desc);

    HRESULT Initialize(CDeviceHolder* pHolder, const ColorBufferDesc& desc);

    void Release();
    
    void Attach();
    void Detach();
    
    void SetDevice(LPDIRECT3DDEVICE9 pDev);
    void SetRenderTargetIndex(cu32 uIndex);

    u32 GetWidth() const;
    u32 GetHeight() const;

    ITexture* GetTexture() const;

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

protected:

    CColorBuffer();
    ~CColorBuffer();

private:

    void Uninitialize();

private:
    
    // �e�N�X�`���T�[�t�F�X
    LPDIRECT3DSURFACE9  m_pSurface;
    // �����_�����O�^�[�Q�b�g�e�N�X�`��
    CTexture*  m_pTexture;

    // �O��ݒ肳��Ă����T�[�t�F�X
    LPDIRECT3DSURFACE9  m_pPrevSurface;

    // �t���[���o�b�t�@���
    ColorBufferDesc     m_desc;

    // �f�o�C�X
    LPDIRECT3DDEVICE9   m_pDev;
};

#endif  // __COLOR_BUFFER_H__

// EOF
