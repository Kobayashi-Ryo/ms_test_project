//=============================================================================
//
// 3D頂点シェーダ
// Author : Ryo Kobayashi
//
//=============================================================================

struct InputVS
{
    float3 pos : POSITION0;
    float3 normal : NORMAL0;
    float2 texCoord : TEXCOORD0;
};

struct OutputVS
{
    float4 posH : POSITION0;
    float3 posW : TEXCOORD0;
    float3 normalW : TEXCOORD1;
    float2 texCoord : TEXCOORD2;
};

// 変換行列
uniform float4x4 gWVP;
uniform float4x4 gWorld;
uniform float4x4 gNormal;

OutputVS VS(InputVS ivs)
{
    OutputVS ovs = (OutputVS)0;
    
    ovs.posH = mul(float4(ivs.pos, 1.0f), gWVP);
    ovs.posW = mul(float4(ivs.pos, 1.0f), gWorld);
    ovs.normalW = mul(float4(ivs.normal, 0.0f), gNormal);
    ovs.texCoord = ivs.texCoord;

    return ovs;
}

// EOF
