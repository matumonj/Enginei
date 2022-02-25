#include"Blur.hlsli"

Texture2D<float4> sceneTexture : register(t0); // シーンテクスチャ
sampler Sampler : register(s0);

float4 main(PSInput In) : SV_Target0
{
    float4 color = sceneTexture.Sample(Sampler, In.uv);

    // step-1 基準テクセル+近傍8テクセルの平均を計算する
    // 2.5テクセル分ずらすためのUV値を求める
    float offsetU = 1.5f / 1280.0f;
    float offsetV = 1.5f / 720.0f;

    // 基準テクセルから右のテクセルのカラーをサンプリングする
    color += sceneTexture.Sample(Sampler, In.uv + float2(offsetU, 0.0f));

    // 基準テクセルから左のテクセルのカラーをサンプリングする
    color += sceneTexture.Sample(Sampler, In.uv + float2(-offsetU, 0.0f));

    // 基準テクセルから下のテクセルのカラーをサンプリングする
    color += sceneTexture.Sample(Sampler, In.uv + float2(0.0f, offsetV));

    // 基準テクセルから上のテクセルのカラーをサンプリングする
    color += sceneTexture.Sample(Sampler, In.uv + float2(0.0f, -offsetV));

    // 基準テクセルから右下のテクセルのカラーをサンプリングする
    color += sceneTexture.Sample(Sampler, In.uv + float2(offsetU, offsetV));

    // 基準テクセルから右上のテクセルのカラーをサンプリングする
    color += sceneTexture.Sample(Sampler, In.uv + float2(offsetU, -offsetV));

    // 基準テクセルから左下のテクセルのカラーをサンプリングする
    color += sceneTexture.Sample(Sampler, In.uv + float2(-offsetU, offsetV));

    // 基準テクセルから左上のテクセルのカラーをサンプリングする
    color += sceneTexture.Sample(Sampler, In.uv + float2(-offsetU, -offsetV));

    // 基準テクセルと近傍8テクセルの平均なので9で除算する
    color /= 9.0f;
    float y = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    color.r = y;
    color.g = y;
    color.b = y;
    return color;
}