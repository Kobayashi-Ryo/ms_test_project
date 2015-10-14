//=============================================================================
//
// �X���b�h�N���X [CThread.cpp]
//
// Date : 2015/4/8
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CThread.h"
#include <process.h>
#include <common/DebugUtil.h>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CThread::CThread() :
_h_thread(nullptr),
_thread_state(DEAD)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CThread::~CThread()
{
    terminate();
}

//=============================================================================
// ��������
//=============================================================================
HRESULT CThread::create(CThread** pp_thread)
{
    if(!pp_thread) return E_FAIL;

    *pp_thread = new CThread();

    if(nullptr == *pp_thread) return E_FAIL;

    return S_OK;
}

//=============================================================================
// �N��
//=============================================================================
void CThread::release()
{
    delete this;
}

//=============================================================================
// �N��
//=============================================================================
bool CThread::start(void *p_object, void* proc, bool immediate)
{
    if(DEAD != _thread_state)
    {
        // �܂��X���b�h�������Ă���̂Ŏ~�߂�
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
        nullptr,                                // SECURITY_ATTRIBUTES�\���̂ւ̃|�C���^
        0,                                      // �X�^�b�N�T�C�Y�B0���ƌĂяo�����Ɠ����ɂȂ�
        (unsigned int (__stdcall *)(void*))proc,// �X���b�h�֐��̃A�h���X
        p_object,                               // �X���b�h�ɓn������
        immediate_flag,                         // 0:�����s, CREATE_SUSPENDED:�ꎞ��~
        nullptr);                               // �X���b�h���ʎq�B

    if((HANDLE)-1 == _h_thread ||
        (HANDLE)0 == _h_thread)
    {
        return false;
    }

    _thread_state = TO_STATE;

    return true;
}

//=============================================================================
// �ċN��
//=============================================================================
bool CThread::resume()
{
    if(ACTIVE == _thread_state) return true;
    else if(DEAD == _thread_state) return false;

    DWORD ret = ResumeThread(_h_thread);

    if(ret > 1)
    {
        // �ˑR���f
        return false;
    }

    _thread_state = ACTIVE;

    return true;
}

//=============================================================================
// �ꎞ��~
//=============================================================================
bool CThread::suspend()
{
    if(SUSPENDED == _thread_state) return true;
    else if(DEAD == _thread_state) return false;

    DWORD ret = SuspendThread(_h_thread);

    if(-1 == ret)
    {
        // ���s
        return false;
    }
    
    _thread_state = SUSPENDED;

    return true;
}

//=============================================================================
// �I��
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