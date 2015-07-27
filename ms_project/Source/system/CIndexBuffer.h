//=============================================================================
//
// �C���f�b�N�X�o�b�t�@
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INDEX_BUFFER_H__
#define __INDEX_BUFFER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "common.h"
#include "IIndexBuffer.h"
#include "CLostResource.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// �C���f�b�N�X�o�b�t�@
//*****************************************************************************
class CIndexBuffer
    : public IIndexBuffer
    , public CLostResource
{
private:

    /**
    * �R���X�g���N�^
    */
    CIndexBuffer();

    /**
    * �f�X�g���N�^
    */
    ~CIndexBuffer();

public:

    /**
    * �C���f�b�N�X�o�b�t�@����
    * @ret �C���f�b�N�X�o�b�t�@
    * @param pHolder �f�o�C�X�z���_�[
    * @param desc �C���f�b�N�X���
    */
    static CIndexBuffer* Create(CDeviceHolder* pHolder, const IndexBufferDesc& desc);

    /**
    * DirectX�C���f�b�N�X�o�b�t�@�擾
    * @ret DirectX�C���f�b�N�X�o�b�t�@
    */
    LPDIRECT3DINDEXBUFFER9 GetPointer() const;

    /**
    * �J��
    */
    void Release();

    /**
    * �C���f�b�N�X�o�b�t�@���b�N
    * @ret S_OK:���b�N���� E_FAIL:���b�N���s
    * @param pBuff ���b�N�����������̐擪�|�C���^
    */
    HRESULT Lock(void** pBuff);

    /**
    * �C���f�b�N�X�o�b�t�@�A�����b�N
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

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    * @param pHolder �f�o�C�X�z���_�[
    * @param desc �C���f�b�N�X���
    */
    HRESULT Init(CDeviceHolder* pHolder, const IndexBufferDesc& desc);

private:

    // �C���f�b�N�X�o�b�t�@
    LPDIRECT3DINDEXBUFFER9 m_pIdx;

    // �C���f�b�N�X�o�b�t�@���
    D3DINDEXBUFFER_DESC m_desc;
};

#endif  // __INDEX_BUFFER_H__

// EOF
