cbuffer cb : register(b0)
{
    float4x4 mvp;       // MVPs—ñ
    float4 mulColor;    // æZƒJƒ‰[
};

struct VSInput
{
    float4 pos : POSITION;
    float2 uv  : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};