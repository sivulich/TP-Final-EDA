#pragma once

#include "Animations.h"
#include "MoveAnimation.h"
class FlipAnimation :public Animation
{
public:
	FlipAnimation(ObjectInterface* ob,double duration);
	void play(ObjectInterface* ob);
	bool passedMiddle() { return middle; };
private:
	Animation* move;
	Animation*zoom;
	double rate,rateY,duration;
	std::pair<int, int> startPos,midPos;
	std::pair<double, double> scales;
	long initialFrames;
	bool middle;

};