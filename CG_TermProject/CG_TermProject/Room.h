
#pragma once
#include "Header.h"

//좌표 XYZ / 스케일 / 색상 

class Room
{
	glm::mat4 Change;
	int AnimalRoom;
	float PositionX;
	float PositionZ;
	float PositionY;
public:

	Room(int room);

	~Room();
	void Update();
	void Draw();
	float getLeft();
	float getRight();
	float getBehind();
	float getFront();
	friend void Catroomtest();
	friend void Dogroomtest();
	friend void Bearroomtest();
};


