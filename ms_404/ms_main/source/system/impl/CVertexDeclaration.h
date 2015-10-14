//=============================================================================
//
// ���_�錾
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __VERTEX_DECLARATION_H__
#define __VERTEX_DECLARATION_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../IVertexDeclaration.h"
#include "../VertexDeclarationDesc.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// ���_�錾
//*****************************************************************************
class CVertexDeclaration
    : private CUncopyable
    , public IVertexDeclaration
{
private:

    /**
    * �R���X�g���N�^
    */
    CVertexDeclaration();

    /**
    * �f�X�g���N�^
    */
    ~CVertexDeclaration();

public:

    /**
    * ����
    * @ret ���_�錾
    * @param pHolder �f�o�C�X�z���_�[
    * @param uNumDescs ���_�錾�̃G�������g��
    * @param pDesc ���_�錾���
    */
    static CVertexDeclaration* Create(
        CDeviceHolder* pHolder,
        u8 uNumElems,
        const VertexDeclarationDesc* pDesc);

    /**
    * �J��
    */
    void Release();

    /**
    * DirectX�C���^�[�t�F�[�X�擾
    * @ret DirectX���_�錾�C���^�[�t�F�[�X
    */
    LPDIRECT3DVERTEXDECLARATION9 GetPointer() const;

    void SetDevice(LPDIRECT3DDEVICE9 pDev);
    
    void Attach();
    void Detach();

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    * @param pHolder �f�o�C�X�z���_�[
    * @param uNumDescs ���_�錾�G�������g��
    * @param pDesc ���_�錾���
    */
    HRESULT Init(CDeviceHolder* pHolder, u8 uNumDescs, const VertexDeclarationDesc* pDesc);

private:

    LPDIRECT3DVERTEXDECLARATION9 m_pDecl;

    LPDIRECT3DDEVICE9 m_pDev;
};

#endif  // __VERTEX_DECLARATION_H__

// EOF
