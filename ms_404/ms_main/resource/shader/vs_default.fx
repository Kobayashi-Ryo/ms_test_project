//=============================================================================
//
// デフォルト頂点シェーダ
// Author : Ryo Kobayashi
//
//=============================================================================

struct InputVS
{
    float3 pos : POSITION0;
    float4 diffuse : COLOR0;
    float2 texCoord : TEXCOORD0;
};

struct OutputVS
{
    float4 posH : POSITION0;
    float4 diffuse : COLOR0;
    float2 texCoord : TEXCOORD0;
};

// 変換行列
uniform float4x4 gWVP;

OutputVS VS(InputVS ivs)
{
    OutputVS ovs = (OutputVS)0;
    
    ovs.posH = mul(float4(ivs.pos, 1.0f), gWVP);
    ovs.diffuse = ivs.diffuse;
    ovs.texCoord = ivs.texCoord;

    return ovs;
}

// EOF
