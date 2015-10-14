//=============================================================================
//
// スレッドクラス [CThread.cpp]
//
// Date : 2015/4/8
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CThread.h"
#include <process.h>
#include <common/DebugUtil.h>

//=============================================================================
// コンストラクタ
//=============================================================================
CThread::CThread() :
_h_thread(nullptr),
_thread_state(DEAD)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CThread::~CThread()
{
    terminate();
}

//=============================================================================
// 生成処理
//=============================================================================
HRESULT CThread::create(CThread** pp_thread)
{
    if(!pp_thread) return E_FAIL;

    *pp_thread = new CThread();

    if(nullptr == *pp_thread) return E_FAIL;

    return S_OK;
}

//=============================================================================
// 起動
//=============================================================================
void CThread::release()
{
    delete this;
}

//=============================================================================
// 起動
//=============================================================================
bool CThread::start(void *p_object, void* proc, bool immediate)
{
    if(DEAD != _thread_state)
    {
        // まだスレッドが生きているので止める
        terminate();
    }

    int immediate_flag = immediate ? 0 : CREATE_SUSPENDED;
    STATE TO_STATE = DEAD;
    if(immediate)
    {
        immediate_flag = 0;
        TO_STATE = ACTIVE;
    }
    else
    {
        immediate_flag = CREATE_SUSPENDED;
        TO_STATE = SUSPENDED;
    }

    _h_thread = (HANDLE)_beginthreadex(
        nullptr,                                // SECURITY_ATTRIBUTES構造体へのポインタ
        0,                                      // スタックサイズ。0だと呼び出し側と同じになる
        (unsigned int (__stdcall *)(void*))proc,// スレッド関数のアドレス
        p_object,                               // スレッドに渡す引数
        immediate_flag,                         // 0:即実行, CREATE_SUSPENDED:一時停止
        nullptr);                               // スレッド識別子。

    if((HANDLE)-1 == _h_thread ||
        (HANDLE)0 == _h_thread)
    {
        return false;
    }

    _thread_state = TO_STATE;

    return true;
}

//=============================================================================
// 再起動
//=============================================================================
bool CThread::resume()
{
    if(ACTIVE == _thread_state) return true;
    else if(DEAD == _thread_state) return false;

    DWORD ret = ResumeThread(_h_thread);

    if(ret > 1)
    {
        // 依然中断
        return false;
    }

    _thread_state = ACTIVE;

    return true;
}

//=============================================================================
// 一時停止
//=============================================================================
bool CThread::suspend()
{
    if(SUSPENDED == _thread_state) return true;
    else if(DEAD == _thread_state) return false;

    DWORD ret = SuspendThread(_h_thread);

    if(-1 == ret)
    {
        // 失敗
        return false;
    }
    
    _thread_state = SUSPENDED;

    return true;
}

//=============================================================================
// 終了
//=============================================================================
bool CThread::terminate()
{
    if(!_h_thread) return true;

    DWORD ret = WaitForSingleObject(_h_thread, INFINITE);

    if(WAIT_FAILED == ret)
    {
        return false;
    }

    CloseHandle(_h_thread);

    _h_thread = nullptr;

    _thread_state = DEAD;

    return true;
}

// EOF