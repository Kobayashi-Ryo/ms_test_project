//=============================================================================
//
// DirectX���̓I�u�W�F�N�g�N���X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INPUT_OBJECT_H__
#define __INPUT_OBJECT_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <common/common.h>

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "dinput8.lib")// DirectX8�̓��̓��C�u����
#pragma comment (lib, "dxguid.lib")    // DirectX�̃R���|�[�l���g�g�p�ɕK�v

//*****************************************************************************
// ���̓I�u�W�F�N�g�N���X
//*****************************************************************************
class CInputObject
    : private CUncopyable
{
private:

    /**
    * �R���X�g���N�^
    */
    CInputObject();

    /**
    * �f�X�g���N�^
    */
    ~CInputObject();

public:

    /**
    * ���̓I�u�W�F�N�g����
    * @ret ���̓I�u�W�F�N�g
    */
    static CInputObject* Create();

    /**
    * �J��
    */
    void Release(void);

    /**
    * DirectInput�擾
    * @ret DirectInput
    */
    LPDIRECTINPUT8 GetDInput() const;

private:

    /**
    * ������
    * @ret S_OK:���� E_FAIL:���s
    */
    HRESULT Init();

private:

    // ���̓I�u�W�F�N�g
    LPDIRECTINPUT8 m_pDInput;
};

#endif  // __INPUT_OBJECT_H__

// EOF
