//=============================================================================
//
// ���b�V���t�B�[���h
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __MESHFIELD_H__
#define __MESHFIELD_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CNode.h"
#include "Vertex3D.h"
#include <functional>

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class IVertexBuffer;
class IVertexDeclaration;
class IIndexBuffer;
class ITexture;

//*****************************************************************************
// ���b�V���t�B�[���h���\����
//*****************************************************************************
struct MeshFieldDesc
{
    vec3 center;
    u16 numXGrid;
    u16 numZGrid;
    f32 widthGrid;
    f32 depthGrid;
    s8* textureName;

    MeshFieldDesc()
        : center(0, 0, 0)
        , numXGrid(1)
        , numZGrid(1)
        , widthGrid(1.0f)
        , depthGrid(1.0f)
        , textureName(nullptr)
    {}
};

//*****************************************************************************
// �N���X
//*****************************************************************************
class CMeshField
    : public CNode
{
public:

    CMeshField();
    ~CMeshField();

    // ����
    static CMeshField* Create(const MeshFieldDesc& desc);

    // �`��
    virtual void Draw();

    // X�������_��
    u32 GetNumVertexX() const;
    // Z�������_��
    u32 GetNumVertexZ() const;

    // ���_�o�b�t�@����
    void ControlVertex(std::function<void(Vertex3D*, u32, u32)> func);

    // �����擾
    f32 GetWidth() const;

    // ���s�擾
    f32 GetDepth() const;

private:

    // ������
    bool Init(const MeshFieldDesc& desc);

private:

    // ���_�o�b�t�@
    IVertexBuffer* m_pVtxBuff;
    // ���_�錾
    IVertexDeclaration* m_pDecl;

    // �C���f�b�N�X�o�b�t�@
    IIndexBuffer* m_pIdxBuff;

    // �e�N�X�`��
    ITexture* m_pTex;

    // ���_��
    u32 m_uNumVtxX;
    u32 m_uNumVtxZ;

    // �v���~�e�B�u��
    u32 m_uNumPrimitive;

    // ����
    f32 m_fWidth;
    // �c��
    f32 m_fDepth;

};

#endif  // __MESHFIELD_H__

// EOF
