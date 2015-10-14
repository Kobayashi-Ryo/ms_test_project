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
#include "Vertex2D.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class IVertexBuffer;
class IVertexDeclaration;
class ITexture;

//*****************************************************************************
// �X�v���C�g���
//*****************************************************************************
struct SpriteDesc
{
    vec3 pos;
    f32 width;
    f32 height;
    D3DXCOLOR color;
    bool useTexSize;

    SpriteDesc()
        : pos(0, 0, 0)
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
    static CSprite* Create();
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
    // �����I�ɐݒ肷��t���O����
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
    
    // �e�N�X�`���\���̈�ݒ�
    void SetTexRect(cf32 left, cf32 top, cf32 right, cf32 bottom);

    // �e�N�X�`���\���J�n���W�ݒ�
    void SetTexPosU(cf32 u);
    void SetTexPosV(cf32 v);
    void SetTexPos(const vec2& pos);
    // �e�N�X�`���\�����ݒ�
    void SetTexWidth(cf32 w);
    void SetTexHeight(cf32 h);
    void SetTexSize(const vec2& size);

private:

    // ������
    HRESULT Init(const SpriteDesc& desc);
    HRESULT Init(const SpriteDesc& desc, cs8* pFileName);

    // �o�b�t�@�X�V
    void UpdateBuffer();

private:

    // ���_�o�b�t�@
    IVertexBuffer* m_pVtxBuff;
    // TODO ���_�錾�͈�ӏ��ɂ܂Ƃ߂�
    IVertexDeclaration* m_pDecl;

    // �e�N�X�`��
    ITexture* m_pTex;

    // �F���
    D3DXCOLOR m_color;

    // ��
    vec2 m_size;

    // �e�N�X�`���J�n���W
    vec2 m_texPos;
    // �e�N�X�`���\����
    vec2 m_texSize;

    // �X�v���C�g�X�V�t���O
    bool m_bSpriteUpdate;
};

#endif  // __SPRITE_H__

// EOF
