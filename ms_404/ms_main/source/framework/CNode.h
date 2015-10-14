//=============================================================================
//
// �m�[�h�N���X
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __NODE_H__
#define __NODE_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <common/CRef.h>
#include <common/common.h>
#include <set>
#include <common/msMath.h>
#include <string>

//*****************************************************************************
// �m�[�h�N���X
//*****************************************************************************
class CNode
    : public CRef
{
public:

    // �q�m�[�h��ǉ�
    void AddChild(CNode* pChild);

    // ������e����폜���āA�����̎q�����Ə�����
    void RemoveFromParentAndCleanUp();

    // ������e����폜����
    void RemoveFromParent();

    // �e�擾
    CNode* GetParent() const;

    // �q�̃��X�g�擾
    const std::set<CNode*>& GetChildren() const;

    // �J��
    virtual void Release();
    // �X�V
    virtual void Update();
    // �`��
    virtual void Draw();

    // ���W�ݒ�
    void SetPosition(const vec3& pos);
    void SetPosition(cf32 x, cf32 y, cf32 z);
    void SetPositionX(cf32 pos);
    void SetPositionY(cf32 pos);
    void SetPositionZ(cf32 pos);
    // ���W�擾
    const vec3& GetPosition() const;

    // ��]�ʐݒ�
    void SetRotation(const vec3& rot);
    void SetRotation(cf32 x, cf32 y, cf32 z);
    void SetRotationX(cf32 rot);
    void SetRotationY(cf32 rot);
    void SetRotationZ(cf32 rot);
    // ��]�ʎ擾
    const vec3& GetRotation() const;

    // �g�k�ݒ�
    void SetScaling(const vec3& scl);
    void SetScaling(cf32 x, cf32 y, cf32 z);
    void SetScalingX(cf32 scl);
    void SetScalingY(cf32 scl);
    void SetScalingZ(cf32 scl);
    // �g�k�擾
    const vec3& GetScaling() const;

    // �\���ݒ�
    void SetVisible(const bool bVisible);
    // �\����Ԏ擾
    bool IsVisible() const;

    // �ϊ��s��擾
    const mat4x4& GetTransform() const;

    // �m�[�h�̖��O��ݒ肷��
    void SetName(const std::string& strName);
    // �m�[�h�̖��O�擾
    const std::string& GetName() const;

    // ���O�ɂ���Ďq���擾
    CNode* GetChildrenByName(const std::string& strName);

protected:

    // �ϊ��s��ݒ�
    void SetupTransform();

    // �e��ݒ�
    void SetParent(CNode* pParent);

    // �q�����폜
    void RemoveChild(CNode* pChild);

    CNode();

    virtual ~CNode() = 0;

private:

    CNode* m_pParent;

    std::set<CNode*> m_Children;

    mat4x4 m_transform;
    vec3 m_pos;
    vec3 m_rot;
    vec3 m_scl;

    std::string m_Name;

    bool m_bVisible;

    bool m_bUpdate;
};

#endif  // __NODE_H__

// EOF
