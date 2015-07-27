//=============================================================================
//
// ���_�錾���
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __VERTEX_DECLARATION_DESC_H__
#define __VERTEX_DECLARATION_DESC_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "common.h"

//*****************************************************************************
// ���_�錾�^�C�v
//*****************************************************************************
enum VtxDeclType
{
    VDDECLTYPE_FLOAT1 = 0,
    VDDECLTYPE_FLOAT2,
    VDDECLTYPE_FLOAT3,
    VDDECLTYPE_FLOAT4,
    VDDECLTYPE_COLOR,

    VDDECLTYPE_UBYTE4,
    VDDECLTYPE_SHORT2,
    VDDECLTYPE_SHORT4,

    VDDECLTYPE_UBYTE4N,
    VDDECLTYPE_SHORT2N,
    VDDECLTYPE_SHORT4N,
    VDDECLTYPE_USHORT2N,
    VDDECLTYPE_USHORT4N,
    VDDECLTYPE_UDEC3,
    VDDECLTYPE_DEC3N,
    VDDECLTYPE_FLOAT16_2,
    VDDECLTYPE_FLOAT16_4,
    VDDECLTYPE_UNUSED
};

//*****************************************************************************
// ���_�錾�g�p���@
//*****************************************************************************
enum VtxDeclUsage
{
    VDDECLUSAGE_POSITION = 0,
    VDDECLUSAGE_BLENDWEIGHT,
    VDDECLUSAGE_BLENDINDICES,
    VDDECLUSAGE_NORMAL,
    VDDECLUSAGE_PSIZE,
    VDDECLUSAGE_TEXCOORD,
    VDDECLUSAGE_TANGENT,
    VDDECLUSAGE_BINORMAL,
    VDDECLUSAGE_TESSFACTOR,
    VDDECLUSAGE_POSITIONT,
    VDDECLUSAGE_COLOR,
    VDDECLUSAGE_FOG,
    VDDECLUSAGE_DEPTH,
    VDDECLUSAGE_SAMPLE
};

//*****************************************************************************
// ���_�錾�\����
//*****************************************************************************
struct VertexDeclarationDesc
{
    u16             Stream;     // �X�g���[���ԍ�
    u16             Offset;     // �X�g���[�����ł̃o�C�g�I�t�Z�b�g
    VtxDeclType     Type;       // �f�[�^�^�C�v
    VtxDeclUsage    Usage;      // �V�F�[�_�[���ł̃Z�}���e�B�N�X(POSITION, NORMAL, TEXCOORD etc.)
    u8              UsageIndex; // �Z�}���e�B�N�X�C���f�b�N�X ex)TEXCOORD3 <- ���̐���
};

#endif  // __VERTEX_DECLARATION_DESC_H__

// EOF
