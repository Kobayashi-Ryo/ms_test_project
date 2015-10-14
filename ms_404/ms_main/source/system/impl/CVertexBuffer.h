//=============================================================================
//
// ���_�o�b�t�@
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <common/common.h>
#include "../IVertexBuffer.h"
#include "CLostResource.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// ���_�o�b�t�@
//*****************************************************************************
class CVertexBuffer
    : public IVertexBuffer
    , public CLostResource
{
private:

    /**
    * �R���X�g���N�^
    */
    CVertexBuffer();

    /**
    * �f�X�g���N�^
    */
    ~CVertexBuffer();

public:

    /**
    * ���_�o�b�t�@����
    * @ret ���_�o�b�t�@
    * @param pHolder �f�o�C�X�z���_�[
    * @param desc ���_���
    */
    static CVertexBuffer* Create(CDeviceHolder* pHolder, const VertexBufferDesc& desc);

    /**
    * DirectX���_�o�b�t�@�擾
    * @ret DirectX���_�o�b�t�@
    */
    LPDIRECT3DVERTEXBUFFER9 GetPointer() const;

    /**
    * �J��
    */
    void Release();

    /**
    * ���_�o�b�t�@���b�N
    * @ret S_OK:���b�N���� E_FAIL:���b�N���s
    * @param pBuff ���b�N�����������̐擪�|�C���^
    */
    HRESULT Lock(void** pBuff);

    /**
    * ���_�o�b�t�@�A�����b�N
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT Unlock();

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
    
    /**
    * �X�g���[���ԍ��ݒ�
    * @param index �X�g���[���ԍ�
    */
    void SetStreamIndex(u32 index);
    /**
    * �o�b�t�@�I�t�Z�b�g�ݒ�
    * @param offset �I�t�Z�b�g�l
    */
    void SetOffset(u32 offset);
    /**
    * �X�g���[���ɗ������_�T�C�Y�ݒ�
    * @param stride �o�b�t�@�v�f�T�C�Y
    */
    void SetStride(u32 stride);

    void SetDevice(LPDIRECT3DDEVICE9 pDev);

    void Attach();
    void Detach();

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    * @param pHolder �f�o�C�X�z���_�[
    * @param desc ���_���
    */
    HRESULT Init(CDeviceHolder* pHolder, const VertexBufferDesc& desc);

private:

    // ���_�o�b�t�@
    LPDIRECT3DVERTEXBUFFER9 m_pVtx;

    // ���_�o�b�t�@���
    D3DVERTEXBUFFER_DESC m_desc;

    LPDIRECT3DDEVICE9 m_pDev;

    u32 m_index;
    u32 m_offset;
    u32 m_stride;
};

#endif  // __VERTEX_BUFFER_H__

// EOF
