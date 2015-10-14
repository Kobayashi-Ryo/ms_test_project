//=============================================================================
//
// �E�B���h�E�N���X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __WINDOW_H__
#define __WINDOW_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <string>

#include "../IWindow.h"
#include <common/CUncopyable.h>

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CThread;

//*****************************************************************************
// �E�B���h�E���N���X
//*****************************************************************************
struct WindowDesc
{
    DWORD uWidth;
    DWORD uHeight;
    std::string strCaption;
    std::string strClassName;
    WNDPROC pWndProc;
    void* pAsyncData;   // �񓯊������p�f�[�^
    void* pAsyncProc;   // �񓯊������p�֐�
};

//*****************************************************************************
// �E�B���h�E�N���X
//*****************************************************************************
class CWindow
    : private CUncopyable
    , public IWindow
{
private:
    CWindow();

    ~CWindow();

public:

    enum Message
    {
        MESSAGE_OK,         // ���b�Z�[�W���������ꂽ
        MESSAGE_TERMINATE   // �I�����b�Z�[�W������
    };

    // ��������
    static CWindow* Create(
        const WindowDesc& desc);

    // �J��
    void Release();

    // ���b�Z�[�W����
    Message ProcMessage(MSG& msg);

    // �E�B���h�E�\��
    void ShowWindow();

    // �E�B���h�E�����擾
    DWORD GetWidth() const;

    // �E�B���h�E�c���擾
    DWORD GetHeight() const;

    // �E�B���h�E�n���h���擾
    HWND GetHandle() const;

    // �L���v�V�����ݒ�
    void SetCaption(const std::string& strCaption);

    // �J�[�\�����N���b�v����
    void ClipCursor(const int x, const int y);
    // �J�[�\���̃N���b�v����
    void UnclipCursor();

    // �������ςݔ���
    bool IsInitialized();

    // ������
    HRESULT Initialize();

private:

    // ������������
    HRESULT InnerCreate(const WindowDesc& desc);

private:
    
    // �E�B���h�E�X�^�C��
    static const int GAME_WINDOW;

    // �E�B���h�E�n���h��
    HWND m_hWnd;

    // �E�B���h�E���
    WindowDesc m_desc;

    // �X���b�h
    CThread *m_pThread;

    // �������ς݃t���O
    volatile bool m_bInitialized;
};

#endif  // __WINDOW_H__

// EOF
