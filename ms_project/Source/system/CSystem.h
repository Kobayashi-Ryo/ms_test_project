//=============================================================================
//
// �V�X�e���N���X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <string>
#include <functional>

// common
#include "common.h"

// interface
#include "interface/ISystem.h"


//*****************************************************************************
// �O���Q��
//*****************************************************************************
// window
class CWindow;
// device holder
class CDeviceHolder;
// sound manager
class CSoundManager;
// input manager
class CInputManager;
// debug
class CDebug;
// resource manager
class CResourceManager;

// hardware timer
class CHardwareTimer;

//*****************************************************************************
// �V�X�e���N���X
//*****************************************************************************
class CSystem
    : private CUncopyable
    , public ISystem
{
private:

    /**
    * �R���X�g���N�^
    */
    CSystem();

    /**
    * �f�X�g���N�^
    */
    ~CSystem();
    
public:

    /**
    * �V�X�e���̎��s
    * @ret ���s����
    * @param arg �v���O�����ɓn���ꂽ����
    */
    static s32 Run(const std::string& arg);
    
    /**
    * ������
    * @ret ����:S_OK ���s:E_FAIL
    * @param �v���O�����ɓn���ꂽ����
    */
    HRESULT Initialize(const std::string& arg);

    /**
    * �J��
    */
    void Release();
    
    /**
    * �X�V
    */
    s32 Update();
    
    /**
    * �I��
    */
    void Finish();
    
    /**
    * �V�X�e���N�������ǂ���
    * @ret true:�N���� false:�I����
    */
    bool IsRunning();


    /**
    * �E�B���h�E�擾
    * @ret �E�B���h�E�C���^�[�t�F�[�X
    */
    IWindow* GetWindow() const;

    /**
    * �f�o�C�X�z���_�[�擾
    * @ret �f�o�C�X�z���_�[�C���^�[�t�F�[�X
    */
    IDeviceHolder* GetDeviceHolder() const;

    /**
    * �T�E���h�擾
    * @ret �T�E���h�C���^�[�t�F�[�X
    */
    ISound* GetSound() const;

    /**
    * ���̓}�l�[�W���擾
    * @ret ���̓}�l�[�W���C���^�[�t�F�[�X
    */
    IInputManager* GetInputManager() const;

    /**
    * �f�o�b�O�擾
    * @ret �f�o�b�O�C���^�[�t�F�[�X
    */
    IDebug* GetDebug() const;
    
    /**
    * ���\�[�X�擾
    * @ret ���\�[�X�C���^�[�t�F�[�X
    */
    IResource* GetResource() const;

    /**
    * �����I��
    */
    void Abort();

    /**
    * �t�b�N�v���V�[�W���ݒ�
    * @param hook �t�b�N�֐�
    */
    void SetWndProcHook(WND_PROC_HOOK hook);


    /**
    * �E�B���h�E�擾
    * @ret �E�B���h�E�C���X�^���X
    */
    CWindow* GetWindowInst() const;
    
    /**
    * �f�o�C�X�z���_�[�擾
    * @ret �f�o�C�X�z���_�[�C���X�^���X
    */
    CDeviceHolder* GetDeviceHolderInst() const;

private:

    /**
    * �E�B���h�E����
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT CreateWindowMS();

    /**
    * �f�o�C�X�z���_�[����
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT CreateDeviceHolder();

    /**
    * �T�E���h�}�l�[�W���[����
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT CreateSoundManager();

    /**
    * ���̓}�l�[�W���[����
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT CreateInputManager();

    /**
    * �f�o�b�O����
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT CreateDebug();

    /**
    * ���\�[�X�}�l�[�W������
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT CreateResourceManager();

    /**
    * �E�B���h�E�v���V�[�W��
    * �ׂ��������̓O�O����
    */
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    /**
    * �L�[����
    * ���̂����p�~
    */
    static void KeyInputProc(HWND hWnd, WPARAM wParam);

private:

    // �E�B���h�E
    CWindow* m_pWindow;

    // �f�o�C�X
    CDeviceHolder* m_pDeviceHolder;

    // �T�E���h
    CSoundManager* m_pSoundManager;

    // ����
    CInputManager* m_pInputManager;

    // �f�o�b�O
    CDebug* m_pDebug;

    // ���\�[�X�}�l�[�W���[
    CResourceManager* m_pResourceManager;

    // �n�[�h�E�F�A�^�C�}�[
    CHardwareTimer* m_pHardwareTimer;

    // �V�X�e���N�����t���O
    bool m_bIsRunning;


    // �A�v���P�[�V����


    // �v���V�[�W���t�b�N
    static std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> m_sWndProcHook;
};

#endif  // __SYSTEM_H__

// EOF
