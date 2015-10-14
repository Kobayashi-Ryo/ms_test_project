//=============================================================================
//
// �[�x�X�e���V���o�b�t�@
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEPTH_STENCIL_BUFFER_H__
#define __DEPTH_STENCIL_BUFFER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../IDepthStencilBuffer.h"
#include <common/DirectX.h>
#include "CLostResource.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CDeviceHolder;

class CDepthStencilBuffer
    : public IDepthStencilBuffer
    , public CLostResource
{
public:
    
    static CDepthStencilBuffer* Create(CDeviceHolder* pHolder, const DepthStencilBufferDesc& desc);

    HRESULT Initialize(CDeviceHolder* pHolder, const DepthStencilBufferDesc& desc);

    void Release();
    
    void Attach();
    void Detach();
    
    void SetDevice(LPDIRECT3DDEVICE9 pDev);

    u32 GetWidth() const;
    u32 GetHeight() const;
    
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

    CDepthStencilBuffer();
    ~CDepthStencilBuffer();

private:

    // �[�x�o�b�t�@�T�[�t�F�X
    LPDIRECT3DSURFACE9      m_pDepthSurface;

    // �O��̐[�x�o�b�t�@
    LPDIRECT3DSURFACE9      m_pPrevSurface;

    // �[�x�o�b�t�@���
    D3DSURFACE_DESC  m_desc;

    // �f�o�C�X
    LPDIRECT3DDEVICE9       m_pDev;
};

#endif  // __DEPTH_STENCIL_BUFFER_H__

// EOF
