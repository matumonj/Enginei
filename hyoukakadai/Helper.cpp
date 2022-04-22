#include "Helper.h"
Helper::FeedState Helper::feedState = FeedState::None;
void Helper::feedIn(float& alpha)
{
	feedState = FeedState::FeedIn;
}

void Helper::feedOut(float& alpha)
{
	feedState = FeedState::FeedOut;
}

void Helper::feedInOut(float& alpha)
{	

}

void Helper::Update(float&alpha)
{
	switch (feedState)
	{
	case FeedState::Setting:
		//color = { 0,0,0,0 };
		break;

	case FeedState::FeedIn:
		alpha += 0.05f;
		if (alpha >= 1.0f) {
			FeedState::End;
		}
		break;

	case FeedState::FeedOut:
		alpha -= 0.05f;
		if (alpha <= 0.0f) {
			FeedState::End;
		}
		break;

	case FeedState::FeedInOut:
		if (alpha>= 1.0f) {
			feedState = FeedState::FeedOut;
		}
		else if (alpha < 1.0f && feedState != FeedState::FeedOut && feedState != FeedState::End) {
			feedState = FeedState::FeedIn;
		}
		break;

	case FeedState::End:
		break;
	}
	alpha = min(alpha, 1);
	alpha = max(alpha, 0);
}