//=============================================================================
//
// ����
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SPHERE_H__
#define __SPHERE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CNode.h"
#include "Vertex3D.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class IVertexBuffer;
class IVertexDeclaration;
class IIndexBuffer;
class ITexture;

//*****************************************************************************
// ���̏��
//*****************************************************************************
struct SphereDesc
{
    vec3 center;    // ���W
    f32 radius;     // ���a
    bool outside;  // �O�������ǂ���
    u16 div;        // ������
    D3DXCOLOR color; // �F

    SphereDesc()
        : center(0,0,0)
        , radius(1.0f)
        , outside(true)
        , div(8)
        , color(1,1,1,1)
    {}
};

//*****************************************************************************
// ����
//*****************************************************************************
class CSphere
    : public CNode
{
public:

    CSphere();
    ~CSphere();

    static CSphere* Create();
    static CSphere* Create(const SphereDesc& desc, cs8* pFileName);

    // �`��
    virtual void Draw();
    
    // �F�ݒ�
    void SetColor(const D3DXCOLOR& color);
    void SetColor(cf32 r, cf32 g, cf32 b);
    // �F�擾
    const D3DXCOLOR& GetColor() const;

    // �A���t�@�l�ݒ�
    void SetAlpha(cf32 a);
    // �A���t�@�l�擾
    f32 GetAlpha() const;

    // �e�N�X�`���ݒ�
    void SetTexture(cs8* pFileName);
    void SetTexture(ITexture* pTex);

    // ���a�ݒ�
    void SetRadius(cf32 radius);
    // ���a�擾
    f32 GetRadius() const;

private:

    // ������
    bool Init(const SphereDesc& desc, cs8* pFileName);

    // ��������
    void SetSphere(bool bOutside);

private:

    // ���_�o�b�t�@
    IVertexBuffer* m_pVtxBuff;
    // ���_�錾
    IVertexDeclaration* m_pDecl;

    // �C���f�b�N�X�o�b�t�@
    IIndexBuffer* m_pIdxBuff;

    // �e�N�X�`��
    ITexture* m_pTex;

    // �F���
    D3DXCOLOR m_color;

    // ���a
    f32 m_fRadius;

    // ������
    u16 m_uDiv;
    
    // ���_��
    u32 m_uNumVertex;
    // �v���~�e�B�u��
    u32 m_uNumPrimitive;

    bool m_bSphereUpdate;
};

#endif  // __SPHERE_H__

// EOF
