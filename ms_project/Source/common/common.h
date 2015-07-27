//=============================================================================
//
// �悭�g������ [common.h]
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CUncopyable.h"

//*****************************************************************************
// �f�o�b�O�t���O
//*****************************************************************************
#ifndef _DEBUG
#define _RELEASE
#endif

//*****************************************************************************
// �J���p�֐�
//*****************************************************************************
// Release�ŊJ��
template<typename T>
void SafeRelease(T*& obj)
{
	if(obj)
	{
		obj->Release();
		obj = nullptr;
	}
}

// delete�ŊJ��
template<typename T>
void SafeDelete(T*& obj)
{
	if(obj)
	{
		delete obj;
		obj = nullptr;
	}
}

// �z��delete�ŊJ��
template<typename T>
void SafeDeleteArray(T*& obj)
{
	if(obj)
	{
		delete [] obj;
		obj = nullptr;
	}
}


//*****************************************************************************
// �g�ݍ��ݕϐ��G�C���A�V���O��`
// �Ȃ�ׂ�������g���Ăق���
//*****************************************************************************
// �ϐ�
// 8bit
typedef char s8;
typedef unsigned char u8;
// 16bit
typedef short s16;
typedef unsigned short u16;
// 32bit
typedef int s32;
typedef unsigned u32;
typedef float f32;
// 64bit
typedef long long s64;
typedef unsigned long long u64;
typedef double f64;

// �萔
// 8bit
typedef const char cs8;
typedef const unsigned char cu8;
// 16bit
typedef const short cs16;
typedef const unsigned short cu16;
// 32bit
typedef const int cs32;
typedef const unsigned cu32;
typedef const float cf32;
// 64bit
typedef const long long cs64;
typedef const unsigned long long cu64;
typedef const double cf64;

//*****************************************************************************
// �k���`�F�b�N
//*****************************************************************************
#define IS_NULL(p) (nullptr == (p) ? true : false)

#ifdef _DEBUG
//*****************************************************************************
// �������`�F�b�N
//*****************************************************************************
#define INIT_CHECK(p) HRESULT hr = (p); _Assert(SUCCEEDED(hr))
#else
#define INIT_CHECK(p) (p)
#endif

#endif	// __KBR_COMMON_H__

// EOF