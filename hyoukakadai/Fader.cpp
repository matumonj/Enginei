#include "Fader.h"
bool Fader::inoutflag = false;
Sprite* Fader::sprite;
float Fader::alpha = 0;
Fader* Fader::GetInstance()
{
	static Fader instance;
	return &instance;
}
bool Fader::SetFeedSprite()
{
	Sprite::LoadTexture(10, L"Resources/feed.png");
	sprite = Sprite::Create(10, { 0,0 });

	return true;
}

void Fader::FeedSpriteUpdate()
{
	sprite->setcolor({ 0,0,0,alpha});
	sprite->SetSize({ 1920,1080 });
}

void Fader::FeedSpriteDraw()
{
	sprite->Draw();
}
void Fader::feedIn(const float Max)
{	
	if (alpha < Max) {
		alpha += 0.025f;
	}
}

void Fader::feedOut(const float Min)
{
	if (alpha > Min) {
		alpha -= 0.025f;
	}

}

void Fader::feedInOut(const float Max, const float Min)
{
	if (alpha < 1.0f && !inoutflag) {
		feedIn(Max);
	} else {
		inoutflag = true;
	}
	if (inoutflag) {
		feedOut(Min);
		if (alpha <= Min) {
			inoutflag = false;
		}
	}
}
void Fader::feedInOut_f(const float Max, const float Min, bool& flag)
{
	if (alpha < 1.0f && !flag) {
		feedIn(Max);
	}
	if (flag) {
		feedOut(Min);
		if (alpha <= Min) {
			//flag = false;
		}
	}
}