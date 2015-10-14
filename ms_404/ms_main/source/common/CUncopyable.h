//=============================================================================
//
// コピー禁止
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __UNCOPYABLE_H__
#define __UNCOPYABLE_H__

//*****************************************************************************
// コピー禁止クラス
//*****************************************************************************
class CUncopyable
{
protected:

	CUncopyable(){}
	~CUncopyable(){}

private:

	CUncopyable(const CUncopyable&);
	CUncopyable& operator=(const CUncopyable&);
};

#endif	// __UNCOPYABLE_H__

// EOF
