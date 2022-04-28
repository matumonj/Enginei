#pragma once
#include"Sprite.h"
class Fader
{
private:

public:
	static Fader* GetInstance();
private:
	static Sprite* sprite;
	static bool inoutflag;
	static bool inoutflag_a;
	static float alpha;
public:
	static bool SetFeedSprite();
	static void FeedSpriteUpdate();
	static void FeedSpriteDraw();
	static void feedIn(const float Max,float fspeed);
	static void feedOut(const float Min, float fspeed);
	static void feedInOut(const float Max, const float Min, float fspeed[2]);
	//feedoutのタイミング指定
	static void feedInOut_f(const float Max, const float Min, bool& flag, float fspeed[2]);
	//任意のアルファ値をいじくり回す
	static void  feedInOutf_a(float& alpha, const float Max, const float Min, float fspeed[2]);
	static void  feedInOutf_f_a(float& alpha, const float Max, const float Min, bool flag, float fspeed[2]);
	static void feedIn_a(float& alpha, const float Max, float fspeed);
	static void feedOut_a(float& alpha, const float Min, float fspeed);
	float GetAlpha() { return alpha; }
};

