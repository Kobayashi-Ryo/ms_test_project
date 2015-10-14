//=============================================================================
//
// �f�o�b�O����
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEBUG_H__
#define __DEBUG_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <common/DirectX.h>
#include <common/d3dx.h>
#include <system/IResource.h>
#include <system/IDebug.h>

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// �f�o�b�O����
//*****************************************************************************
class CDebug
    : private CUncopyable
    , public IDebug
{
private:

    /**
    * �R���X�g���N�^
    */
    CDebug();

    /**
    * �f�X�g���N�^
    */
    ~CDebug();

public:

    /**
    * �f�o�b�O��������
    * @ret �f�o�b�O����
    * @param pHolder �f�o�C�X�z���_�[
    * @param pRes ���\�[�X�C���^�[�t�F�[�X
    */
    static CDebug* Create(CDeviceHolder *pHolder, IResource* pRes);

    /**
    * �J��
    */
    void Release();

    /**
    * �`��
    */
    void Draw();

    /**
    * �f�o�b�O���N���A
    */
    void Clear();

    /**
    * �f�o�b�O�����񑗏o
    * @param str ������t�H�[�}�b�g
    * @param ... �t�H�[�}�b�g����
    */
    void Print(cs8* str, ...);

    /**
    * �f�o�b�O�\��
    */
    void Show();

    /**
    * �f�o�b�O��\��
    */
    void Hide();

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    * @param pHolder �f�o�C�X�z���_�[
    */
    HRESULT Init(CDeviceHolder *pHolder, IResource* pRes);

private:

    // �ő啶����
    static cs16 MAX_DEBUG_BUF = 2048;

    // �f�o�b�O�\���p�t�H���g
    IFont* m_pFont;

    // �f�o�b�O�\���p�o�b�t�@
    s8 m_aStrDebugProc[MAX_DEBUG_BUF];

    // �f�o�b�O�\���p�o�b�t�@�̌��݂̎g�p��
    s32 m_nNumDebugProcLength;

    // �f�o�b�O��\�����邩�ǂ����̃t���O
    bool m_bUseDebugFlag;
};

#endif  // __DEBUG_H__

// EOF
