//=============================================================================
//
// �f�o�b�O����
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEBUG_UTIL_H__
#define __DEBUG_UTIL_H__


//*****************************************************************************
//
//
// !!!����!!!
// ���̃t�@�C���̓w�b�_�ł͂Ȃ��A�ucpp�t�@�C���v�ŃC���N���[�h���邱��
// ����Ɂu����cpp�t�@�C���̃C���N���[�h�̍Ō�ɃC���N���[�h�v���邱��
//
// ��)
// #include <stdio.h>
// #include <stdlib.h>
// �c
// �c
// �c
// #include "DebugUtil.h"
//
// // �ȉ��֐��Ȃ�
//
//
//*****************************************************************************



//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
#include <stdio.h>
#include <cstdlib>

#else

#include <Windows.h>
#include <stdio.h>
#include <cstdlib>

#endif

#ifdef _DEBUG
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DBGNEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBGNEW
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define calloc(c, s) _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define realloc(p, s) _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _realloc(p, c, s) _realloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _expand(p, s) _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)

// ������0�̂Ƃ��A�x��
#define _Assert(expr)\
    {\
        if(!(expr))\
        {\
            char assertExp[512];\
            char path[256];\
            GetModuleFileName(nullptr, path, sizeof(path));\
            sprintf_s(assertExp, 512, "Program Failed\n\nProgram : %s\nFile : %s\nLine : %d\nFunction : %s\n", path, __FILE__, __LINE__, __FUNCTION__);\
            int nRet = MessageBox(nullptr, assertExp, "Error", MB_ABORTRETRYIGNORE | MB_ICONERROR);\
            if(nRet == IDABORT){ std::abort(); }\
            else if(nRet == IDRETRY){}\
            else if(nRet == IDIGNORE){}\
        }\
    }
// ������0�̂Ƃ��A�x���ƕ�����
#define _AssertExpr(expr, str)\
    {\
        if(!(expr))\
        {\
            char assertExp[512];\
            char path[256];\
            GetModuleFileName(nullptr, path, sizeof(path));\
            sprintf_s(assertExp, 512, "Program Failed\n\nProgram : %s\nFile : %s\nLine : %d\nFunction : %s\n\n%s", path, __FILE__, __LINE__, __FUNCTION__, str);\
            int nRet = MessageBox(nullptr, assertExp, "Error", MB_ABORTRETRYIGNORE | MB_ICONERROR);\
            if(nRet == IDABORT){ std::abort(); }\
            else if(nRet == IDRETRY){}\
            else if(nRet == IDIGNORE){}\
        }\
    }

// ������0�̂Ƃ��A�x���ƕ�����
#define _AssertExprArg(expr, str, ...)\
    {\
        if(!(expr))\
        {\
            char assertExp[1024];\
            char path[256];\
            char c[512];\
            sprintf_s(c, 512, str, __VA_ARGS__);\
            GetModuleFileName(nullptr, path, sizeof(path));\
            sprintf_s(assertExp, 1024, "Program Failed\n\nProgram : %s\nFile : %s\nLine : %d\nFunction : %s\n\n%s", path, __FILE__, __LINE__, __FUNCTION__, c);\
            int nRet = MessageBox(nullptr, assertExp, "Error", MB_ABORTRETRYIGNORE | MB_ICONERROR);\
            if(nRet == IDABORT){ std::abort(); }\
            else if(nRet == IDRETRY){}\
            else if(nRet == IDIGNORE){}\
        }\
    }

// �t�@�C�����݂̂̕�����ɕϊ�
#define _FILE_NAME_ strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1) : __FILE__

// �w�肵������(��)���o��
#define _PrintConsole(str, ...) \
    {\
        /* �R�s�[�敶���� */\
        char c[256];\
        sprintf_s(c, 256, str, __VA_ARGS__);\
        /* �w�肳�ꂽ������\�� */\
        OutputDebugString(c);\
    }

// �t�@�C�����A�֐����A�s���t�o��
#define _PrintConsoleEx(str, ...) \
    {\
        char fileFuncLine[256];\
        sprintf_s(fileFuncLine, 256, "FILE :%s / FUNC :%s() / LINE :%d\n", _FILE_NAME_, __FUNCTION__, __LINE__);\
        /* �t�@�C�����A�֐����A�s���o�� */\
        OutputDebugString(fileFuncLine);\
        /* �R�s�[�敶���� */\
        char c[256];\
        sprintf_s(c, 256, str"\n", __VA_ARGS__);\
        /* �w�肳�ꂽ������\�� */\
        OutputDebugString(c);\
    }

#else

#define _PrintConsole(str, ...)
#define _PrintConsoleEx(str, ...)
#define _Assert(expr)
#define _AssertExpr(expr, str)
#define _AssertExprArg(expr, str, ...)

#endif

// ������0�̂Ƃ��A�x��
#define _CriticalAssert(expr)\
    {\
        if(!(expr))\
        {\
            char assertExp[512];\
            char path[256];\
            GetModuleFileName(nullptr, path, sizeof(path));\
            sprintf_s(assertExp, 512, "Program Failed\n\nProgram : %s\nFile : %s\nLine : %d\nFunction : %s\n", path, __FILE__, __LINE__, __FUNCTION__);\
            MessageBox(nullptr, assertExp, "Error", MB_OK | MB_ICONERROR);\
            std::abort();\
        }\
    }

// ������0�̂Ƃ��A�x���ƕ�����
#define _CriticalAssertExpr(expr, str)\
    {\
        if(!(expr))\
        {\
            char assertExp[512];\
            char path[256];\
            GetModuleFileName(nullptr, path, sizeof(path));\
            sprintf_s(assertExp, 512, "Program Failed\n\nProgram : %s\nFile : %s\nLine : %d\nFunction : %s\n\n%s", path, __FILE__, __LINE__, __FUNCTION__, str);\
            MessageBox(nullptr, assertExp, "Error", MB_OK | MB_ICONERROR);\
            std::abort();\
        }\
    }

// �����I��
#define _AbortExpr(str)\
    {\
        char assertExp[512];\
        char path[256];\
        GetModuleFileName(nullptr, path, sizeof(path));\
        sprintf_s(assertExp, 512, "Program Failed\n\nProgram : %s\nFile : %s\nLine : %d\nFunction : %s\n\n%s", path, __FILE__, __LINE__, __FUNCTION__, str);\
        MessageBox(nullptr, assertExp, "Error", MB_OK | MB_ICONERROR);\
        std::abort();\
    }

#endif  // __DEBUG_UTIL_H__

// EOF
