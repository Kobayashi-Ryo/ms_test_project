//=============================================================================
//
// DirectX�w�b�_
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DIRECTX_H__
#define __DIRECTX_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <d3d9.h>
//#include <d3dx9.h>
#include <DxErr.h>
#include "common.h"

//*****************************************************************************
// �X�^�e�B�b�N���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")    // �`�揈���ɕK�v
//#pragma comment (lib, "d3dx9.lib")    // ��̊g�����C�u����
#pragma comment (lib, "dxguid.lib")    // DirectX�̃R���|�[�l���g�g�p�ɕK�v
#pragma comment (lib, "winmm.lib")    // ���ꂪ������time~�֐����g���Ȃ�
#pragma comment (lib, "dxerr.lib")    // �G���[�����o���Ă����֐��Ȃǂ��g���郉�C�u����

// DirectX�ɂ��f�o�b�O�g���[�X
#if    defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                        \
    {                                                \
        if(FAILED( (x) ))                                \
        {                                            \
        DXTrace(__FILE__, __LINE__, x, "�G���[", TRUE);    \
        }                                            \
    }
#endif
#else
#ifndef HR
#define HR(x) x
#endif
#endif

#endif    // __DIRECTX_H__

// EOF