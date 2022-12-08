#include "DoorR.h"


DoorR::~DoorR()
{
}

DoorR::DoorR(int open)
{
	Open = open;
}


void DoorR::Update()
{
	//FixUpdate();
	//Tx = glm::translate(Tx, glm::vec3(0, 0, 0));
	glm::mat4 Scale = glm::scale(Unit, glm::vec3(0.5, 1, 0.125));
	glm::mat4 Trans;
	if (Open == 1) {
		Trans = glm::translate(Unit, glm::vec3(-99.5+openingCat, 0, -4.9));

	}
	else
		Trans = glm::translate(Unit, glm::vec3(100.5+openingDog, 0, -4.9));
	//glm::mat4 Trans1 = glm::translate(Unit, glm::vec3(0, 1, 0));
	Change = Trans * Scale;
}

void DoorR::Draw()
{
	if (dogopen || catopen) {

		glBindVertexArray(VAO);
		GLuint Color = glGetUniformLocation(shaderID, "objectColor");
		glUniform4f(Color, 0, 0, 1., 1.0);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환

		glDrawArrays(GL_TRIANGLES, 0, vertex1.size() * 3);
	}
}


