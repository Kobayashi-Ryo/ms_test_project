//=============================================================================
//
// �A�v���P�[�V�����̓Ǝ��ݒ�
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "AppDelegate.h"
#include "CSceneGame.h"

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::Init()
{
    // ������
    auto scene = CSceneGame::CreateScene();
    ReplaceScene(scene);

    return true;
}

void AppDelegate::Release()
{
    delete this;
}

// EOF
