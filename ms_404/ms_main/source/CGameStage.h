//=============================================================================
//
// �Q�[���X�e�[�W
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __GAME_STAGE_H__
#define __GAME_STAGE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "framework.h"
#include <common/common.h>

//*****************************************************************************
// OBJECT ID
//*****************************************************************************
enum ObjectID
{
    OBJECT_PLAYER1,
    OBJECT_PLAYER2
};

//*****************************************************************************
// �N���X
//*****************************************************************************
class CGameStage
    : public CNode
{
public:

    CGameStage();
    ~CGameStage();

    // ����
    static CGameStage* Create(cs8* pFileName);
    // ������
    bool Init(cs8* pFileName);

    // �X�V
    virtual void Update();
    // �`��
    virtual void Draw();

    // �f�o�b�O�`��

    // �J�����ݒ�
    void SetCamera(CCamera* pCamera);

    // �v���C���[�X�R�A�擾

private:

    // �v���C���[�X�V
    void UpdatePlayer();

    // �I�u�W�F�N�g�\�[�g

    // �����蔻��

private:

    // �v���C���[
    // �v���C���[�ړ����[�g

    // �X�e�[�W�I�u�W�F�N�g

    // �t�B�[���h
    CMeshField* m_pField;

    // �J����
    CCamera* m_pCamera;
};

#endif  // __GAME_STAGE_H__

// EOF
