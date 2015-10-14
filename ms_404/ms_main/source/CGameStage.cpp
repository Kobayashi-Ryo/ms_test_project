//=============================================================================
//
// ゲームステージ
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CGameStage.h"

#include "CPlayer.h"

#include <common/DebugUtil.h>

CGameStage::CGameStage()
{
}

CGameStage::~CGameStage()
{
}

// 生成
CGameStage* CGameStage::Create(cs8* pFileName)
{
    CGameStage* pObj = new CGameStage();

    if(pObj)
    {
        bool suc = pObj->Init(pFileName);
        _Assert(suc);
        _PrintConsole("ゲームステージ\n");
    }

    return pObj;
}

// 初期化
bool CGameStage::Init(cs8* pFileName)
{
    SpriteDesc desc;
    auto left = CSprite::Create();
    left->SetPositionX(100);
    left->SetPositionY(100);
    left->SetSize(100, 100);
    left->SetTexture("box.bmp");
    left->SetName("left");
    AddChild(left);

    auto right = CSprite::Create();
    right->SetPositionX(100);
    right->SetPositionY(300);
    right->SetSize(500, 200);
    right->SetTexture("box.bmp");
    right->SetName("right");
    AddChild(right);

    // ステージが広そうなのでフィールドは複数用意する
    // カリングもした方がよい
    MeshFieldDesc mfDesc;
    mfDesc.numXGrid = 100;
    mfDesc.numZGrid = 100;
    mfDesc.widthGrid = 1.0f;
    mfDesc.depthGrid = 1.0f;
    mfDesc.textureName = "box.bmp";
    m_pField = CMeshField::Create(mfDesc);
    AddChild(m_pField);
    // ここで頂点をいじれる
    m_pField->ControlVertex(
    []
    (Vertex3D* pVtx, u32 width, u32 depth)
    {
        pVtx[width * depth / 2 - 1].pos.y = 0.5f;
        pVtx[width * depth / 2].pos.y = 0.2f;
        pVtx[width * depth / 2 + 1].pos.y = 0.5f;
        for(int i = 0; i < width * depth; i++)
        {
            pVtx[i].texcoord.x *= 0.05f;
            pVtx[i].texcoord.y *= 0.05f;
        }
    });

    auto sphere = CSphere::Create();
    sphere->SetName("sphere");
    AddChild(sphere);

    auto player = CPlayer::Create(0);
    AddChild(player);

    return true;
}

// 更新
void CGameStage::Update()
{
    auto left = GetChildrenByName("left");
    if(left)
    {
        static f32 r = 0.0f;
        left->SetRotation(0,0,r);
        r+=D3DX_PI * 0.001f;
    }
    auto pSphere = GetChildrenByName("sphere");
    if(pSphere)
    {
        pSphere->SetPositionY(1.0f);
    }

    // プレイヤー更新
    UpdatePlayer();

    // 当たり判定

    // 出来ればオブジェクト描画順ソート

    CNode::Update();
}

// 描画
void CGameStage::Draw()
{
    if(!IsVisible())
    {
        return;
    }
    auto p = GetParent();
    if(p->GetName().compare("SceneGame") != 0)
    {
        return;
    }

    CScene* pScene = static_cast<CScene*>(GetParent());
    
    // 2D
    pScene->GetShader2D()->Attach();
    CCamera2D cam;
    f32 width = 480;
    f32 height = 540;
    cam.SetVolumeWidth(width);
    cam.SetVolumeHeight(height);
    cam.SetupMatrix();
    mat4x4 out;
    auto pRight = GetChildrenByName("left");
    D3DXMatrixMultiply(&out, &pRight->GetTransform(), &cam.GetOrtho());
    pScene->GetShader2D()->SetMatrix(IShader::VERTEX, "gWVP", &out);
    pRight->Draw();
    pScene->GetShader2D()->Detach();

    // 3D
    pScene->GetShader3D()->Attach();
    auto cam3 = pScene->GetCameras()[0];
    cam3->SetPos(20.0f, 5.0f, -20.0f);
    cam3->SetAspect(width / height);
    cam3->SetupMatrix();

    pScene->GetShader3D()->SetMatrix(IShader::VERTEX, "gWorld", &m_pField->GetTransform());
    pScene->GetShader3D()->SetMatrix(IShader::VERTEX, "gNormal", &m_pField->GetTransform());
    D3DXMatrixMultiply(&out, &m_pField->GetTransform(), &cam3->GetViewProj());
    pScene->GetShader3D()->SetMatrix(IShader::VERTEX, "gWVP", &out);
    m_pField->Draw();

    auto pSphere = GetChildrenByName("sphere");
    pScene->GetShader3D()->SetMatrix(IShader::VERTEX, "gWorld", &pSphere->GetTransform());
    pScene->GetShader3D()->SetMatrix(IShader::VERTEX, "gNormal", &pSphere->GetTransform());
    D3DXMatrixMultiply(&out, &pSphere->GetTransform(), &cam3->GetViewProj());
    pScene->GetShader3D()->SetMatrix(IShader::VERTEX, "gWVP", &out);
    pSphere->Draw();

    pScene->GetShader3D()->Detach();
}

// カメラ設定
void CGameStage::SetCamera(CCamera* pCamera)
{
    m_pCamera = pCamera;
}

// プレイヤー更新
void CGameStage::UpdatePlayer()
{
    auto player = static_cast<CPlayer*>(GetChildrenByName("sphere"));
    if(player)
    {
        auto key = CApplication::GetInstance()->GetSystem()->GetInputManager()->GetKeyboard();
        auto cam3 = ((CScene*)GetParent())->GetCameras()[0];
        vec3 dir(0, 0, 1);
        vec3 move(0,0,0);
        D3DXVec3TransformNormal(&move, &dir, &cam3->GetAttitudeMatrix());
        if(key->GetPress(DIK_A))
        {
            player->Move(move);
        }
        if(key->GetPress(DIK_D))
        {
            player->Move(-move);
        }
    }
}

// EOF
