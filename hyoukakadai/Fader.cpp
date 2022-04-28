#include "Fader.h"
bool Fader::inoutflag = false;
bool Fader::inoutflag_a = false;
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
	alpha = 0.0f;
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
void Fader::feedIn(const float Max, float fspeed)
{	
	if (alpha < Max) {
		alpha += 0.01f;
	}
}

void Fader::feedOut(const float Min, float fspeed)
{
	if (alpha > Min) {
		alpha -= 0.01f;
	}

}


void Fader::feedIn_a(float& alpha, const float Max, float fspeed)
{
	if (alpha < Max) {
		alpha += fspeed;
	}
}

void Fader::feedOut_a(float& alpha, const float Min, float fspeed)
{
	if (alpha > Min) {
		alpha -=fspeed;
	}

}

void Fader::feedInOut(const float Max, const float Min, float fspeed[2])
{
	if (alpha < Max && !inoutflag) {
		feedIn(Max,fspeed[0]);
	} else {
		inoutflag = true;
	}
	if (inoutflag) {
		feedOut(Min,fspeed[1]);
		if (alpha <= Min) {
			//inoutflag = false;
		}
	}
}
void Fader::feedInOut_f(const float Max, const float Min, bool& flag, float fspeed[2])
{
	if (alpha < 1.0f && !flag) {
		feedIn(Max,fspeed[0]);
	}
	if (flag) {
		feedOut(Min,fspeed[1]);
		if (alpha <= Min) {
			//flag = false;
		}
	}
}

void Fader::feedInOutf_f_a(float& alpha, const float Max, const float Min, bool flag, float fspeed[2])
{
	if (alpha < 1.0f && !flag) {
		feedIn_a(alpha,Max,fspeed[0]);
	}
	if (flag) {
		feedOut_a(alpha,Min,fspeed[1]);
		if (alpha <= Min) {
			//flag = false;
		}
	}
}
void Fader::feedInOutf_a(float& alpha, const float Max, const float Min, float fspeed[2])
{
	if (alpha < Max && !inoutflag_a) {
		feedIn_a(alpha,Max,fspeed[0]);
	} else {
		inoutflag_a = true;
	}
	if (inoutflag_a) {
		feedOut_a(alpha,Min,fspeed[1]);
		if (alpha < Min) {
			//inoutflag_a = false;
		}
	}
}
