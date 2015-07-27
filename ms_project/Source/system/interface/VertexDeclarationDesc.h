//=============================================================================
//
// 頂点宣言情報
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __VERTEX_DECLARATION_DESC_H__
#define __VERTEX_DECLARATION_DESC_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "common.h"

//*****************************************************************************
// 頂点宣言タイプ
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
// 頂点宣言使用方法
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
// 頂点宣言構造体
//*****************************************************************************
struct VertexDeclarationDesc
{
    u16             Stream;     // ストリーム番号
    u16             Offset;     // ストリーム内でのバイトオフセット
    VtxDeclType     Type;       // データタイプ
    VtxDeclUsage    Usage;      // シェーダー内でのセマンティクス(POSITION, NORMAL, TEXCOORD etc.)
    u8              UsageIndex; // セマンティクスインデックス ex)TEXCOORD3 <- この数字
};

#endif  // __VERTEX_DECLARATION_DESC_H__

// EOF
