//=============================================================================
//
// よく使う処理 [common.h]
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CUncopyable.h"

//*****************************************************************************
// デバッグフラグ
//*****************************************************************************
#ifndef _DEBUG
#define _RELEASE
#endif

//*****************************************************************************
// 開放用関数
//*****************************************************************************
// Releaseで開放
template<typename T>
void SafeRelease(T*& obj)
{
	if(obj)
	{
		obj->Release();
		obj = nullptr;
	}
}

// deleteで開放
template<typename T>
void SafeDelete(T*& obj)
{
	if(obj)
	{
		delete obj;
		obj = nullptr;
	}
}

// 配列deleteで開放
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
// 組み込み変数エイリアシング定義
// なるべくこれを使ってほしい
//*****************************************************************************
// 変数
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

// 定数
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
// ヌルチェック
//*****************************************************************************
#define IS_NULL(p) (nullptr == (p) ? true : false)

#ifdef _DEBUG
//*****************************************************************************
// 初期化チェック
//*****************************************************************************
#define INIT_CHECK(p) HRESULT hr = (p); _Assert(SUCCEEDED(hr))
#else
#define INIT_CHECK(p) (p)
#endif

#endif	// __KBR_COMMON_H__

// EOF