//=============================================================================
//
// �X�v���C�g�N���X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CNode.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class IVertexBuffer;
class ITexture;

//*****************************************************************************
// �X�v���C�g���
//*****************************************************************************
struct SpriteDesc
{
    u8 vertexSize; // ���_�������̃o�C�g�T�C�Y
    vec3 pos;
    f32 width;
    f32 height;
    D3DXCOLOR color;
    bool useTexSize;

    SpriteDesc()
        : vertexSize(0)
        , pos(0, 0, 0)
        , width(0)
        , height(0)
        , color(1,1,1,1)
        , useTexSize(false)
    {}
};

//*****************************************************************************
// �X�v���C�g�N���X
//*****************************************************************************
class CSprite
    : public CNode
{
private:

    /**
    * �R���X�g���N�^
    */
    CSprite();

    /**
    * �f�X�g���N�^
    */
    ~CSprite();

public:

    // ����
    static CSprite* Create(const SpriteDesc& desc);
    static CSprite* Create(const SpriteDesc& desc, cs8* pFileName);

    // �X�V
    void Update();
    // �`��
    void Draw();

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
    // �ݒ肵���Ƃ��Ƀe�N�X�`���̃T�C�Y��ݒ肵�����̂�
    // �����I�ɐݒ肷��t���O�������
    void SetTexture(cs8* pFileName, bool bUseTexSize = false);
    void SetTexture(ITexture* pTex, bool bUseTexSize = false);

    // �����ݒ�
    void SetWidth(cf32 fWidth);
    // �����擾
    f32 GetWidth() const;

    // �c���ݒ�
    void SetHeight(cf32 fHeight);
    // �c���擾
    f32 GetHeight() const;

    // �c���̕��ݒ�
    void SetSize(const vec2& size);
    void SetSize(cf32 fWidth, cf32 fHeight);
    // �c���̕��擾
    const vec2& GetSize() const;

private:

    // ������
    HRESULT Init(const SpriteDesc& desc);
    HRESULT Init(const SpriteDesc& desc, cs8* pFileName);

    // �o�b�t�@�X�V
    void UpdateBuffer();

private:

    // ���_�o�b�t�@
    IVertexBuffer* m_pVtxBuff;

    // �e�N�X�`��
    ITexture* m_pTex;

    // �F���
    D3DXCOLOR m_color;

    // ��
    vec2 m_size;
};

#endif  // __SPRITE_H__

// EOF
