#pragma once
#include"Input.h"
enum Stage {
	None,
	tyutorial_1,
	tyutorial_2,
	Jungle_1_1,
	Jungle_1_2,
	Jungle_1_3,
	Sea_1_1,
	Sea_1_2,
	Sea_1_3,
	Cas_1_1,
	Cas_1_2,
};
class Retry
{
public:
	
	static Stage getStage() { return stage; }
	static Stage stage;
	
	static void SetStage(Stage st) { stage = st; };
	static void init();


};

