//=============================================================================
//
// �L�[�{�[�h
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CInputObject.h"
#include "../IKeyboard.h"
#include <common/common.h>

//*****************************************************************************
// �L�[�{�[�h
//*****************************************************************************
class CKeyboard
    : private CUncopyable
    , public IKeyboard
{
private:

    /**
    * �R���X�g���N�^
    */
    CKeyboard();

    /**
    * �f�X�g���N�^
    */
    ~CKeyboard();

public:

    /**
    * ����
    * @ret �}�l�[�W���[
    * @param pObj ���̓I�u�W�F�N�g
    * @param hWnd �E�B���h�E�n���h��
    */
    static CKeyboard* Create(CInputObject* pObj, HWND hWnd);

    /**
    * �J��
    */
    void Release();

    /**
    * �X�V
    */
    void Update();

    /**
    * �v���X��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    bool GetPress(u8 key) const;

    /**
    * �g���K�[��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    bool GetTrigger(u8 key) const;

    /**
    * �����[�X��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    bool GetRelease(u8 key) const;

    /**
    * ���s�[�g��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    bool GetRepeat(u8 key) const;

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    * @param pObj ���̓I�u�W�F�N�g
    * @param hWnd �E�B���h�E�n���h��
    */
    HRESULT Init(CInputObject* pObj, HWND hWnd);

private:

    LPDIRECTINPUTDEVICE8 m_pDev;    // �f�o�C�X�ւ̃|�C���^

    static const s32 MAX_KEY = 256;    // �L�[�ő吔
    static const s32 REPEAT_TIME = 20; // ���s�[�g�^�C��(�J�E���^)
    static const s32 KEY_ON = 128;    // �L�[���̓t���O

    BYTE m_aKeyState[MAX_KEY];      // �L�[�{�[�h�̏�Ԃ��i�[���郏�[�N
    BYTE m_aKeyTrigger[MAX_KEY];    // �g���K�[���͏��
    BYTE m_aKeyRelease[MAX_KEY];    // �L�[�����[�X���
    BYTE m_aKeyRepeat[MAX_KEY];     // ���s�[�g���
    s32 m_aKeyRepeatCount[MAX_KEY]; // �L�[�������Ă��鎞�Ԃ̃J�E���g
};

#endif  // __KEYBOARD_H__

// EOF
