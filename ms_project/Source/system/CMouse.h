//=============================================================================
//
// �}�E�X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __MOUSE_H__
#define __MOUSE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CInputObject.h"
#include "interface/IMouse.h"
#include "common.h"

//*****************************************************************************
// �}�E�X
//*****************************************************************************
class CMouse
    : private CUncopyable
    , public IMouse
{
private:

    /**
    * �R���X�g���N�^
    */
    CMouse();

    /**
    * �f�X�g���N�^
    */
    ~CMouse();

public:

    /**
    * ����
    * @ret �}�l�[�W���[
    * @param pObj ���̓I�u�W�F�N�g
    * @param hWnd �E�B���h�E�n���h��
    */
    static CMouse* Create(CInputObject* pObj, HWND hWnd);

    /**
    * �J��
    */
    void Release();

    /**
    * �X�V
    */
    void Update();

    /**
    * ���W�擾
    * @ret ���W
    */
    const POINT& GetPosition() const;

    /**
    * �ړ��ʎ擾
    * @ret �ړ���
    */
    const POINT& GetMove() const;

    /**
    * �X�N���[���ʎ擾
    * @ret �X�N���[����
    */
    LONG GetScroll() const;

    /**
    * �v���X��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    bool GetPress(MouseButton btn) const;

    /**
    * �g���K�[��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    bool GetTrigger(MouseButton btn) const;

    /**
    * �����[�X��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    bool GetRelease(MouseButton btn) const;

    /**
    * ���s�[�g��Ԏ擾
    * @ret ��Ԕ���
    * @param key �Y���L�[
    */
    bool GetRepeat(MouseButton btn) const;

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

    static const s32 KEY_ON = 128;    // ���͂��Ă���
    static const s32 MAX_BUTTON = 8;// �}�E�X�̃{�^����
    static const s32 REPEAT_TIME = 20; // ���s�[�g�^�C��(fps)
    
    // �E�B���h�E�n���h��
    HWND                 m_hWnd;

    // �}�E�X��ԕϐ�
    DIMOUSESTATE2        m_MouseState;
    DIMOUSESTATE2        m_MouseTrigger;
    DIMOUSESTATE2        m_MouseRelease;
    DIMOUSESTATE2        m_MouseRepeat;

    // ���s�[�g
    s32                  m_aMouseRepeatCount[MAX_BUTTON];

    // �}�E�X���W
    POINT                m_pos;
    // �O��ƍ���̍���
    POINT                m_diff;

    // �X�N���[����
    LONG                 m_nScroll;
};

#endif  // __MOUSE_H__

// EOF
