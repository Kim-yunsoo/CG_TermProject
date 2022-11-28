#pragma once

#include "Head.h"
#include "Nose.h"
#include "Body.h"
#include "Arm.h"
#include "Leg.h"
#include "Eyes.h"
#include "Ear.h"
#include "Beard.h"
#include "sword.h"

#include "Hero.h"

extern Hero hero;


class Cat
{

	
	Head head;
	Nose nose;
	Body body;
	Arm armL;
	Arm armR;
	Leg legL;
	Leg legR;
	Eyes eyesL;
	Eyes eyesR;
	Ear earL;
	Ear earR;
	Beard beardL1;
	Beard beardR1;
	Beard beardL2;
	Beard beardR2;
	Beard beardL3;
	Beard beardR3;
	Sword swordR;
	Sword swordL;
	float closelineX;
	float closelineZ;

	glm::vec3 Position;
	float Direction;

public:
	Cat();
	~Cat();

	void draw();
	void update();

	float getLeft();
	float getRight();
	float getBehind();
	float getFront();
	float getBottom();
	float getTop();
};

