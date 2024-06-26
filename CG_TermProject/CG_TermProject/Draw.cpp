#include "Draw.h"

void draw();
float circleSize = 2;
void AnimalCollideCat();
void AnimalCollideDog();
struct CatAttack;

void BulletCollideCat();
void BulletCollideDog();

void Catroomtest();
void Dogroomtest();
void Bearroomtest();

bool isCollideCatroom(Cat r1, Room r2);
bool isCollideDogroom(Dog r1, Room r2);
bool isCollideBearroom(Bear r1, Room r2);
bool HeroVSRoom(Hero r1, Room r2);
void HeroVSDog();
void HeroVSBear();
void HeroVSCat();

bool isCollideDog(Dog r1, Gun r2);
bool isCollide2D(Cat r1, Gun r2);
bool isBearCollide = true;

int catdead{};
int dogdead{};
int beardead{};

int HerogetHP = 10;
float lightPosX = 0.0;
float lightPosY = 30.0;
float lightPosZ = 0.0;
int lightcolorN = 0;
float lightRot;
float lightColorR = 1.0f;
float lightColorG = 1.0f;
float lightColorB = 1.0f;
bool isParticle = false;
bool isBullet = false;

float ortho = 12.0;
vector<Gun*> gun;
bool isCollideBear(Bear r1, Gun r2);


vector<Particle*> particle{ new Particle,new Particle, new Particle, new Particle, new Particle
						,new Particle, new Particle,new Particle,new Particle,new Particle,
						 new Particle,new Particle, new Particle, new Particle, new Particle
						,new Particle, new Particle,new Particle,new Particle,new Particle,new Particle,new Particle, new Particle, new Particle, new Particle
						,new Particle, new Particle,new Particle,new Particle,new Particle,
						 new Particle,new Particle, new Particle, new Particle, new Particle
						,new Particle, new Particle,new Particle,new Particle,new Particle };

vector<Cat*> cats{ new Cat, new Cat, new Cat, new Cat, new Cat, new Cat };
vector<Dog*> dogs{ new Dog, new Dog, new Dog, new Dog, new Dog, new Dog };
Hero hero(0.3, 0.3, 0.3, 0, 0.5, 10.0);
World world{};
Tree tree[400];
Grass grass[600];
Crown crown{};
CastleObj castle{};
Room catRoom{ 0 };
Room dogRoom{ 1 };
Room bearRoom{ 2 };
Bear bear;
Tunnel Dogopen{ 2 };
DoorL Dogleft{ 2 };
DoorR Dogright{ 2 };

Tunnel Catopen{ 1 };
DoorL Catleft{ 1 };
DoorR Catright{ 1 };


float CatEndPosX;
float CatEndPosZ;

float DogEndPosX;
float DogEndPosZ;

random_device rd;
default_random_engine dre(rd());
uniform_real_distribution<float> urd{ 0, 255 };


GLvoid drawScene()
{

	GLuint SelectColor = glGetUniformLocation(shaderID, "SelectColor");
	glUniform1i(SelectColor, 1);

	if (lightColorR < 0.35)
		glClearColor(0.f, 0.f, 0.f, 1.0f);
	else
		glClearColor(1.f, 1.f, 1.f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DITHER);
	//glEnable(GL_CULL_FACE);  
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);

	glm::mat4 projection;

	projection = glm::perspective(glm::radians(90.0f), (float)width / height, 0.1f, 200.0f);
	unsigned int projectionLocation = glGetUniformLocation(shaderID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	glViewport(0, 0, width, height);
	camera();
	draw();
	for (int i = 0; i < hero.InfoHP(); ++i) {
		glm::mat4 Change;
		Change = Unit;
		GLuint projectionTransform = glGetUniformLocation(shaderID, "projectionTransform");
		glUniformMatrix4fv(projectionTransform, 1, GL_FALSE, glm::value_ptr(Change));
		Change = Unit;
		GLuint viewTransform = glGetUniformLocation(shaderID, "viewTransform");
		glUniformMatrix4fv(viewTransform, 1, GL_FALSE, glm::value_ptr(Change));

		glm::mat4 Scale = glm::scale(Unit, glm::vec3(0.3));
		glm::mat4 Trans = glm::translate(Unit, glm::vec3(-0.95, 0.95, 0));
		Change = Trans * Scale;
		Change = glm::translate(Unit, glm::vec3(i * 0.08f, 0, 0)) * Change;
		GLuint modelTransform = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelTransform, 1, GL_FALSE, glm::value_ptr(Change));

		glDrawArrays(GL_POLYGON, 0, 4);
	}

	glViewport(width / 1.26, height / 1.35, 200, 200);
	projection = glm::mat4(1.0f);
	projection = glm::ortho(-ortho, ortho, -ortho, ortho, -ortho, ortho);
	projectionLocation = glGetUniformLocation(shaderID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	TopView();

	draw();

	glutSwapBuffers();
};





void draw() {

	if (beardead) {
		lightColorR = 1.0f;
		lightColorG = 1.0f;
		lightColorB = 1.0f;
	}
	if (herodead) {
		lightColorR = 0.5f;
		lightColorG = 0.5f;
		lightColorB = 0.5f;


	}
	unsigned int lightPosLocation = glGetUniformLocation(shaderID, "lightPos");      //--- lightPos 
	glm::vec4 tempv(lightPosX, lightPosY, lightPosZ, 1);
	glm::mat4 Lightrotate = glm::rotate(glm::mat4(1.f), glm::radians(lightRot), glm::vec3(0, 1, 0));
	tempv = Lightrotate * tempv;
	glUniform3f(lightPosLocation, tempv.x, tempv.y, tempv.z);
	unsigned int lightColorLocation = glGetUniformLocation(shaderID, "lightColor");   //--- lightColor 
	glUniform3f(lightColorLocation, lightColorR, lightColorG, lightColorB);
	unsigned int aColor = glGetUniformLocation(shaderID, "objectColor");   //--- object Color
	glUniform4f(aColor, 1, 1., 1., 1.);

	world.Draw();




	glEnable(GL_BLEND); //투명 객체 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	for (int i = 0; i < 400; ++i) {
		tree[i].Draw();
		tree[i].Update();

	}




	for (int i = 0; i < 600; ++i) {
		grass[i].Draw();
		grass[i].Update();
	}

	glDisable(GL_BLEND);


	if (catdead == 6) {
		catopen = true;
		dogopen = false;
	}


	if (dogdead == 6) {
		catopen = false;
		dogopen = true;
	}


	catRoom.Draw();
	catRoom.Update();
	dogRoom.Draw();
	dogRoom.Update();
	bearRoom.Draw();
	bearRoom.Update();

	castle.Draw();
	castle.Update();


	Catleft.Draw();
	Catleft.Update();
	Catright.Draw();
	Catright.Update();


	Dogleft.Draw();
	Dogleft.Update();
	Dogright.Draw();
	Dogright.Update();




	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");
	glUniform1i(selectColorLocation, 0);

	Dogopen.Draw();
	Dogopen.Update();
	Catopen.Draw();
	Catopen.Update();


	crown.Draw();
	crown.Update();

	if (herodead) {

	}
	for (int i = 0; i < cats.size(); ++i) {
		cats[i]->draw();
	}

	for (int i = 0; i < dogs.size(); ++i) {
		dogs[i]->draw();
	}

	if (BearLife) {
		bear.draw();
	}
	hero.Update();
	hero.Draw();


	for (Gun*& gunbullet : gun) {
		gunbullet->Update();
		gunbullet->Draw();

	}
	if (CatEndPosX != 0 && CatEndPosZ != 0) {
		if (isParticle) {
			for (int i = 0; i < 40; ++i) {
				particle[i]->update();
				particle[i]->draw();
			}
		}
	}

	if (isBullet && BulletLimit == 0) {
		BulletLimit += 1;
		gun.push_back(new Gun{ cameraPos.x,cameraPos.y,cameraPos.z, TermGunDir.x,TermGunDir.y,TermGunDir.z });
		//cout << "(X) : " << cameraPos.x << "(Z) : " << cameraPos.z << endl;
	}
	for (Gun* guns : gun) {
		cout << "guns X : " << guns->GetPosX() << endl;
		cout << "guns Z : " << guns->GetPosZ() << endl;
	}
	auto p = find_if(gun.begin(), gun.end(), [](Gun* guns) {
		if ((guns->GetPosX()) > 1000 || (guns->GetPosX()) < -1000 || (guns->GetPosZ()) > 1000 || (guns->GetPosZ()) < -1000) {
			return true;
		}
		else {
			return false;
		}
		});
	if (p != gun.end() && gun.begin()!=gun.end()) {
		gun.erase(p);
		cout << "지워짐!!!" << endl;
	}

	/*int index{};
	for (Gun* guns : gun) {
		++index;
		if ((guns->GetPosX()) > 1000 || (guns->GetPosX()) < -1000 || (guns->GetPosZ()) > 1000 || (guns->GetPosZ()) < -1000) {
		}
	}*/

	glBindVertexArray(HeroHPVAO);
	aColor = glGetUniformLocation(shaderID, "objectColor");
	glUniform4f(aColor, 1.0, 0.0, 0., 1);



}

void AnimalCollideCat() {

	for (int i = 0; i < cats.size(); ++i) {
		for (int j = i + 1; j < cats.size(); ++j) {
			float distanceX = abs(cats[i]->Position.x - cats[j]->Position.x);

			float distanceZ = abs(cats[i]->Position.z - cats[j]->Position.z);
			if (distanceX <= 0.1f) {
				cats[i]->Position.x += 0.1f;
			}
			if (distanceZ <= 0.1f) {
				cats[i]->Position.z += 0.1f;
			}
		}
	}
}

void AnimalCollideDog() {
	for (int i = 0; i < dogs.size(); ++i) {
		for (int j = i + 1; j < dogs.size(); ++j) {
			float distanceX = abs(dogs[i]->Position.x - dogs[j]->Position.x);
			float distanceZ = abs(dogs[i]->Position.z - dogs[j]->Position.z);
			if (distanceX <= 0.1f) {
				dogs[i]->Position.x += 0.1f;
			}
			if (distanceZ <= 0.1f) {
				dogs[i]->Position.z += 0.1f;
			}
		}
	}

}



void BulletCollideCat() {

	for (int i = 0; i < gun.size(); ++i) {
		for (int j = 0; j < cats.size(); ++j) {
			if (isCollide2D(*cats[j], *gun[i])) {
				cats[j]->HP -= gun[i]->Damage;
				delete gun[i];
				if (0 == cats[j]->HP) {
					for (int i = 0; i < 40; ++i) {
						particle[i]->dirY = -0.2;
					}
					CatEndPosX = cats[j]->Position.x;
					CatEndPosZ = cats[j]->Position.z;
					isParticle = true;
					delete cats[j];
					catdead++;
					cats.erase(cats.begin() + j);
					--j;
				}
				gun.erase(gun.begin() + i);
				--i;
				break;
			}

		}

	}
}

void BulletCollideDog() {

	for (int i = 0; i < gun.size(); ++i) {
		for (int j = 0; j < dogs.size(); ++j) {
			if (isCollideDog(*dogs[j], *gun[i])) {
				dogs[j]->HP -= gun[i]->Damage;
				delete gun[i];
				if (0 == dogs[j]->HP) {
					for (int i = 0; i < 40; ++i) {
						particle[i]->dirY = -0.2;
					}
					CatEndPosX = dogs[j]->Position.x;
					CatEndPosZ = dogs[j]->Position.z;
					isParticle = true;
					delete dogs[j];
					dogdead++;
					dogs.erase(dogs.begin() + j);
					--j;
				}
				gun.erase(gun.begin() + i);
				--i;
				break;
			}

		}

	}
}

void BulletCollideBear() {

	for (int i = 0; i < gun.size(); ++i) {
		if (isCollideBear(bear, *gun[i])) {
			bear.HP -= gun[i]->Damage;
			delete gun[i];
			if (0 == bear.HP) {
				for (int i = 0; i < 40; ++i) {
					particle[i]->dirY = -0.2;
				}
				CatEndPosX = bear.Position.x;
				CatEndPosZ = bear.Position.z;
				BearLife = false;
				beardead = true;
				isParticle = true;
			}
			gun.erase(gun.begin() + i);
			--i;
		}
	}
}

bool isCollide2D(Cat r1, Gun r2)
{
	if (r1.getRight() < r2.getLeft() || r1.getLeft() > r2.getRight()) return false;
	if (r1.getFront() < r2.getBehind() || r1.getBehind() > r2.getFront()) return false;
	return true;
}

bool isCollideDog(Dog r1, Gun r2)
{
	if (r1.getRight() < r2.getLeft() || r1.getLeft() > r2.getRight()) return false;
	if (r1.getFront() < r2.getBehind() || r1.getBehind() > r2.getFront()) return false;
	return true;
}


bool isCollideBear(Bear r1, Gun r2)
{
	if (r1.getRight() < r2.getLeft() || r1.getLeft() > r2.getRight()) return false;
	if (r1.getFront() < r2.getBehind() || r1.getBehind() > r2.getFront()) return false;
	return true;
}


bool isCollideCatroom(Cat r1, Room r2)
{
	if (r1.getRight() < r2.getLeft() || r1.getLeft() > r2.getRight()) return false;
	if (r1.getFront() < r2.getBehind() || r1.getBehind() > r2.getFront()) return false;
	return true;
}

bool isCollideDogroom(Dog r1, Room r2)
{
	if (r1.getRight() < r2.getLeft() || r1.getLeft() > r2.getRight()) return false;
	if (r1.getFront() < r2.getBehind() || r1.getBehind() > r2.getFront()) return false;
	return true;
}

bool isCollideBearroom(Bear r1, Room r2)
{
	if (r1.getRight() < r2.getLeft() || r1.getLeft() > r2.getRight()) return false;
	if (r1.getFront() < r2.getBehind() || r1.getBehind() > r2.getFront()) return false;
	return true;
}

bool HeroVSRoom(Hero r1, Room r2)
{
	if (r1.getRight() < r2.getLeft() || r1.getLeft() > r2.getRight()) return false;
	if (r1.getFront() < r2.getBehind() || r1.getBehind() > r2.getFront()) return false;
	return true;
}

void Catroomtest()
{
	for (int i = 0; i < 6; ++i) {
		if (isCollideCatroom(*cats[i], catRoom)) {

			if (cats[i]->Position.x < catRoom.PositionX - 5)
				cats[i]->Position.x += 1;
			if (cats[i]->Position.x > catRoom.PositionX + 5)
				cats[i]->Position.x -= 1;
			if (cats[i]->Position.z < catRoom.PositionZ - 5)
				cats[i]->Position.z += 1;
			if (cats[i]->Position.z > catRoom.PositionZ + 5)
				cats[i]->Position.z -= 1;
		}
	}
}


void Dogroomtest()
{
	for (int i = 0; i < 6; ++i) {
		if (isCollideDogroom(*dogs[i], dogRoom)) {

			if (dogs[i]->Position.x < dogRoom.PositionX - 5)
				dogs[i]->Position.x += 1;
			if (dogs[i]->Position.x > dogRoom.PositionX + 5)
				dogs[i]->Position.x -= 1;
			if (dogs[i]->Position.z < dogRoom.PositionZ - 5)
				dogs[i]->Position.z += 1;
			if (dogs[i]->Position.z > dogRoom.PositionZ + 5)
				dogs[i]->Position.z -= 1;
		}
	}
}


void Bearroomtest()
{

	if (isCollideBearroom(bear, bearRoom)) {

		if (bear.Position.x < bearRoom.PositionX - 5)
			bear.Position.x += 1;
		if (bear.Position.x > bearRoom.PositionX + 5)
			bear.Position.x -= 1;
		if (bear.Position.z < bearRoom.PositionZ - 5)
			bear.Position.z += 1;
		if (bear.Position.z > bearRoom.PositionZ + 5)
			bear.Position.z -= 1;
	}

}



void HeroVSBear()
{
	if (HeroVSRoom(hero, bearRoom)) {

		if (hero.PosX < bearRoom.PositionX - 5)
			hero.PosX += 1.0;
		if (hero.PosX > bearRoom.PositionX + 5)
			hero.PosX -= 1.0;
		if (hero.PosZ < bearRoom.PositionZ - 5)
			hero.PosZ += 1.0;
		if (hero.PosZ > bearRoom.PositionZ + 5)
			hero.PosZ -= 1.0;
	}
}

void HeroVSCat()
{
	if (HeroVSRoom(hero, catRoom)) {

		if (hero.PosX < catRoom.PositionX - 5)
			hero.PosX += 1.0;
		if (hero.PosX > catRoom.PositionX + 5)
			hero.PosX -= 1.0;
		if (hero.PosZ < catRoom.PositionZ - 5)
			hero.PosZ += 1.0;
		if (hero.PosZ > catRoom.PositionZ + 5)
			hero.PosZ -= 1.0;
	}
}

void HeroVSDog()
{
	if (HeroVSRoom(hero, dogRoom)) {

		if (hero.PosX < dogRoom.PositionX - 5)
			hero.PosX += 1.0;
		if (hero.PosX > dogRoom.PositionX + 5)
			hero.PosX -= 1.0;
		if (hero.PosZ < dogRoom.PositionZ - 5)
			hero.PosZ += 1.0;
		if (hero.PosZ > dogRoom.PositionZ + 5)
			hero.PosZ -= 1.0;
	}
}