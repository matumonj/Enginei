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
	static float alpha;
public:
	static bool SetFeedSprite();
	static void FeedSpriteUpdate();
	static void FeedSpriteDraw();
	static void feedIn(const float Max);
	static void feedOut(const float Min);
	static void feedInOut(const float Max, const float Min);
	//feedoutのタイミング指定
	static void feedInOut_f(const float Max, const float Min, bool& flag);

	float GetAlpha() { return alpha; }
};

