//=============================================================================
//
// �V�[���N���X���
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CNode.h"
#include "CCamera.h"
#include <vector>
#include <system/IShader.h>

static const s32 DEFAULT_CAMERA_NUM = 8;

static const s8* DEFAULT_VERTEX_SHADER_2D = "vs_default.fx";
static const s8* DEFAULT_PIXEL_SHADER_2D = "ps_default.fx";

static const s8* DEFAULT_VERTEX_SHADER_3D = "vs_3d.fx";
static const s8* DEFAULT_PIXEL_SHADER_3D = "ps_3d.fx";

//*****************************************************************************
// �V�[���N���X
//*****************************************************************************
class CScene
    : public CNode
{
public:

    // �J�����擾
    const std::vector<CCamera*>& GetCameras() const;
    // �J���������擾
    u32 GetNumCameras() const;

    // �f�t�H���g�V�F�[�_�[�擾
    IShader* GetShader2D() const;
    IShader* GetShader3D() const;

    // ���C�g�擾

    virtual bool Init();

    // ��������I�[�o�[���C�h����
    // virtual void Update();
    // virtual void Draw();

protected:

    CScene();
    virtual ~CScene() = 0;

private:

    void InitShader();

private:

    std::vector<CCamera*> m_Cameras;

    IShader* m_pShader2D;
    IShader* m_pShader3D;
};

#endif  // __SCENE_H__

// EOF
