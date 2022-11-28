#include "Bear.h"

Bear::Bear() :
	head(Head(glm::vec3(255. / 255, 167. / 255, 167. / 255), 3)),
	body(Body(glm::vec3(255. / 255, 167. / 255, 167. / 255), 3)),
	bodyf(Body(glm::vec3(255. / 255, 239. / 255, 239. / 255), 4)),
	armL(Arm(glm::vec3(255. / 255, 167. / 255, 167. / 255), -1, 3)),
	armR(Arm(glm::vec3(255. / 255, 167. / 255, 167. / 255), 1, 3)),
	legL(Leg(glm::vec3(255. / 255, 167. / 255, 167. / 255), -1, 3)),
	legR(Leg(glm::vec3(255. / 255, 167. / 255, 167. / 255), 1, 3)),
	earL(Ear(glm::vec3(255. / 255, 167. / 255, 167. / 255), -1, 3)),
	earR(Ear(glm::vec3(255. / 255, 167. / 255, 167. / 255), 1, 3)),

	eyebrowL(Beard(glm::vec3(0. / 255, 0. / 255, 0. / 255), -1, 1, 3)),
	eyebrowR(Beard(glm::vec3(0. / 255,0. / 255, 0. / 255), 1, 2, 3)),

	nose(Nose(glm::vec3(36. / 255, 36. / 255, 36. / 255), 3)),
	eyesL(Eyes(glm::vec3(255. / 255, 54. / 255, 54. / 255), -1, 3)),
	eyesR(Eyes(glm::vec3(255. / 255, 54. / 255, 54. / 255), 1, 3)),
	Position(glm::vec3(1.f, -1.f, -1.f)), Direction(0.f),
	swordL(Sword(glm::vec3(72. / 255, 255. / 255, 255. / 255), -1, 3)),
	swordR(Sword(glm::vec3(72. / 255, 255. / 255, 255. / 255), 1, 3))
{

}


void Bear::draw()
{
	nose.draw();
	head.draw();
	armL.draw();
	armR.draw();
	body.draw();
	bodyf.draw();
	legL.draw();
	legR.draw();
	eyesL.draw();
	eyesR.draw();
	earL.draw();
	earR.draw();
	eyebrowL.draw();
	eyebrowR.draw();

	swordL.draw();
	swordR.draw();
}

void Bear::update()
{
	hero.location();
	float dz = HeroLocationZ - Position.z;
	float dx = HeroLocationX - Position.x;

	Direction = atan2(dx, dz);

	closelineX = HeroLocationX - Position.x;
	if (!(closelineX <= 0.000001 && closelineX >= -0.000001)) {

		if (closelineX >= 0) {
			closelineX -= 0.01;
			Position.x += 0.01;
		}
		if (closelineX < 0) {
			closelineX += 0.01;
			Position.x -= 0.01;
		}
	}

	closelineZ = HeroLocationZ - Position.z;
	if (!(closelineZ <= 0.000001 && closelineZ >= -0.000001)) {
		if (closelineZ > 0) {
			closelineZ -= 0.01;
			Position.z += 0.01;
		}
		if (closelineZ < 0) {
			closelineZ += 0.01;
			Position.z -= 0.01;
		}

	}

	


	nose.keyIn(Position, Direction);
	head.keyIn(Position, Direction);
	armL.keyIn(Position, Direction);
	armR.keyIn(Position, Direction);
	body.keyIn(Position, Direction);
	bodyf.keyIn(Position, Direction);
	legL.keyIn(Position, Direction);
	legR.keyIn(Position, Direction);
	eyesL.keyIn(Position, Direction);
	eyesR.keyIn(Position, Direction);
	earL.keyIn(Position, Direction);
	earR.keyIn(Position, Direction);
	eyebrowL.keyIn(Position, Direction);
	eyebrowR.keyIn(Position, Direction);

	swordL.keyIn(Position, Direction);
	swordR.keyIn(Position, Direction);
}

Bear::~Bear()
{
}

float Bear::getLeft()
{
	return Position.x - 0.15f;
}

float Bear::getRight()
{
	return Position.x + 0.15f;
}

float Bear::getBehind()
{
	return Position.z - 0.15f;
}

float Bear::getFront()
{
	return Position.z + 0.15f;
}

float Bear::getBottom()
{
	return Position.y;
}

float Bear::getTop()
{
	return 0.0f;				//계산하기 귀찮으니 대충 0으로 잡겠음(의미없는값)
}


