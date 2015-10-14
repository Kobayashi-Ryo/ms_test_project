//=============================================================================
//
// �[�x�X�e���V���o�b�t�@
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEPTH_STENCIL_BUFFER_DESC_H__
#define __DEPTH_STENCIL_BUFFER_DESC_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
enum DSFormat
{
    DSFMT_D16,
    DSFMT_D32,
    DSFMT_D24S8
};

struct DepthStencilBufferDesc
{
    // �o�b�t�@��
    unsigned            width;
    unsigned            height;
    // �t�H�[�}�b�g
    DSFormat           format;
};

#endif  // __DEPTH_STENCIL_BUFFER_DESC_H__

// EOF
