#include "Helper.h"
Helper::FeedState Helper::feedState = FeedState::None;
bool Helper::inoutflag = false;
void Helper::feedIn(float& alpha,const float Max)
{
	if(alpha <Max) {
		alpha += 0.05f;
	}
	

}

void Helper::feedOut(float& alpha, const float Min)
{
	if (alpha >Min) {
		alpha -= 0.05f;
	}
	
}

void Helper::feedInOut(float& alpha, const float Max,const float Min)
{
	if (alpha < 1.0f&&!inoutflag) {
		feedIn(alpha,Max);
	}
	else {
		inoutflag = true;
	}
	if (inoutflag) {
		feedOut(alpha,Min);
		if (alpha <=Min) {
			inoutflag = false;
		}
	}
}
void Helper::feedInOut_f(float &alpha, const float Max, const float Min, bool& flag)
{
	if (alpha < 1.0f && !flag) {
		feedIn(alpha, Max);
	} 
	if (flag) {
		feedOut(alpha, Min);
		if (alpha <= Min) {
			flag = false;
		}
	}
}
