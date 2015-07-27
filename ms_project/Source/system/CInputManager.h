//=============================================================================
//
// ���̓}�l�[�W���[
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CUncopyable.h"
#include "interface/IInputManager.h"

//*****************************************************************************
// �O���Q��
//*****************************************************************************
// input object
class CInputObject;
// input
class CKeyboard;
class CMouse;

//*****************************************************************************
// ���̓}�l�[�W���[
//*****************************************************************************
class CInputManager
    : private CUncopyable
    , public IInputManager
{
private:

    /**
    * �R���X�g���N�^
    */
    CInputManager();

    /**
    * �f�X�g���N�^
    */
    ~CInputManager();

public:

    /**
    * ����
    * @ret �}�l�[�W���[
    */
    static CInputManager* Create(HWND hWnd);

    /**
    * �J��
    */
    void Release();

    /**
    * �X�V
    */
    void Update();

    /**
    * �L�[�{�[�h�擾
    * @ret �L�[�{�[�h
    */
    IKeyboard* GetKeyboard() const;

    /**
    * �}�E�X�擾
    * @ret �}�E�X
    */
    IMouse* GetMouse() const;

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT Init(HWND hWnd);

private:

    // ���̓I�u�W�F�N�g
    CInputObject* m_pInputObject;

    // �L�[�{�[�h
    CKeyboard* m_pKeyboard;

    // �}�E�X
    CMouse* m_pMouse;
};

#endif  // __INPUT_MANAGER_H__

// EOF
