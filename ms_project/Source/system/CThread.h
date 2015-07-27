//=============================================================================
//
// スレッドクラス [CThread.h]
//
// Date : 2015/4/9
//
//=============================================================================
#pragma once
#ifndef __THREAD_H__
#define __THREAD_H__

//*****************************************************************************
// インクルードファイル
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
 * @brief スレッドの状態
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
 * @note コンストラクタ
 */
    CThread();

/**
 * ~CThread
 * 
 * @return  void
 * @note デストラクタ
 */
    ~CThread();

/**
 * create
 * 
 * @param[in/out]   CThread **  pp_thread
 * 
 * @return  HRESULT
 * @note スレッドの生成
 */
    static HRESULT create(CThread** pp_thread);

/**
 * release
 * 
 * @return  void
 * @note 開放
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
 * @note スレッドの起動
 */
    bool start(void *p_object, void* proc, bool immediate);

/**
 * resume
 * 
 * @return  bool
 * @note スレッドの再起動
 */
    bool resume();

/**
 * suspend
 * 
 * @return  bool
 * @note スレッドの一時停止
 */
    bool suspend();

/**
 * terminate
 * 
 * @return  bool
 * @note スレッドの終了
 */
    bool terminate();

private:

    ///< @brief スレッドハンドル
    HANDLE _h_thread;

    ///< @brief スレッド状態
    STATE _thread_state;
};

#endif    // __THREAD_H__

// EOF