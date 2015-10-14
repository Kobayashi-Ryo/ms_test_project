//=============================================================================
//
// �X���b�h�N���X [CThread.h]
//
// Date : 2015/4/9
//
//=============================================================================
#pragma once
#ifndef __THREAD_H__
#define __THREAD_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>

/**
 * @class   CThread
 * @brief
 */
class CThread
{
public:

/**
 * @enum    STATE
 * @brief �X���b�h�̏��
 */
    enum STATE
    {
        ACTIVE = 0,
        DEAD,
        SUSPENDED,
    };

/**
 * CThread
 * 
 * @return  void
 * @note �R���X�g���N�^
 */
    CThread();

/**
 * ~CThread
 * 
 * @return  void
 * @note �f�X�g���N�^
 */
    ~CThread();

/**
 * create
 * 
 * @param[in/out]   CThread **  pp_thread
 * 
 * @return  HRESULT
 * @note �X���b�h�̐���
 */
    static HRESULT create(CThread** pp_thread);

/**
 * release
 * 
 * @return  void
 * @note �J��
 */
    void release();

/**
 * start
 * 
 * @param[in/out]   void *  p_object
 * @param[in]       void *  proc
 * @param[in]       bool    immediate
 * 
 * @return  bool
 * @note �X���b�h�̋N��
 */
    bool start(void *p_object, void* proc, bool immediate);

/**
 * resume
 * 
 * @return  bool
 * @note �X���b�h�̍ċN��
 */
    bool resume();

/**
 * suspend
 * 
 * @return  bool
 * @note �X���b�h�̈ꎞ��~
 */
    bool suspend();

/**
 * terminate
 * 
 * @return  bool
 * @note �X���b�h�̏I��
 */
    bool terminate();

private:

    ///< @brief �X���b�h�n���h��
    HANDLE _h_thread;

    ///< @brief �X���b�h���
    STATE _thread_state;
};

#endif    // __THREAD_H__

// EOF