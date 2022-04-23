#include "Fader.h"

void Fader::FadeIn(float&alpha)
{
	alpha += 0.05f;
}

void Fader::FadeOut(float& alpha)
{
	alpha -= 0.05f;
}
void Fader::FadeInOut(float& alpha)
{

}