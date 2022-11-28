#include "Camera.h"


GLuint shaderID;
float carY;
float carAddX;
float carAddY;
float carAddZ;
float VAngleX;
float VAngleY;

void camera() {
	glm::vec3 CPos(carAddX+1, carAddY-0.5 , carAddZ + 10);
	glm::mat4 RotC = glm::rotate(glm::mat4(1.f), glm::radians(carY), glm::vec3(0, 1, 0));
	CPos = RotC * glm::vec4(CPos, 1.f);
	glm::vec3 CDir(0.f + carAddX, 0.0f + carAddY, 0.0f + carAddZ);
	CDir = RotC * glm::vec4(CDir, 1.f);


	glm::mat4 VAngleY_Rot = glm::rotate(glm::mat4(1.0f), glm::radians(VAngleY), glm::vec3(0.0, 1.0, 0.0)); //y?
	glm::mat4 VAngleX_Rot = glm::rotate(glm::mat4(1.0f), glm::radians(VAngleX), glm::vec3(1.0, 0.0, 0.0)); // x

	glm::vec3 cameraPos = glm::vec3(CPos.x, CPos.y, CPos.z);      //--- 카메라 위치 (어디서 볼건지)
	glm::vec3 cameraDirection = glm::vec3(CDir.x, CDir.y, CDir.z);               //--- 카메라 바라보는 방향 (어디볼건지 하면될듯)
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);                     //--- 카메라 위쪽 방향->벡터임(방향만) (음수하면 화면 상하거꾸로보임)

	glm::mat4 view = VAngleX_Rot * VAngleY_Rot * glm::lookAt(cameraPos, cameraDirection, cameraUp);

	unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int viewPosLocation = glGetUniformLocation(shaderID, "viewPos");      //--- viewPos 값 전달: 카메라 위치
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);


}


//void onecamera() {
//	glm::vec3 cameraPos;
//	glm::mat4 orbitRot = glm::mat4(1.0f);
//	glm::mat4 orbitRot1 = glm::mat4(1.0f);
//	glm::mat4 view = glm::mat4(1.0f);
//	
//	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // 고정 
//
//	glm::vec3 cameraDirection = glm::vec3(0.f+ AddX, 3.0f+ AddY, 0.0f+ AddZ); // 카메라 봐라보기
//	orbitRot = glm::rotate(orbitRot, glm::radians(orbit), glm::vec3(0.0, 1.0, 0.0));
//	orbitRot1 = glm::rotate(orbitRot1, glm::radians(orbit1), glm::vec3(1.0, 0.0, 0.0));
//
//	cameraPos = glm::vec3(0.f+ AddX, 3.f+AddY, 29.f+AddZ); //카메라 위치
//	view = orbitRot1 * orbitRot * glm::lookAt(cameraPos, cameraDirection, cameraUp);
//	unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- 뷰잉 변환 설정
//	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//
//}
//
//
////미니맵
//void camera2() {
//	glm::vec3 cameraPos;
//
//	cameraPos = glm::vec3(0.f, 30.f, 0.f); //카메라 위치
//	glm::vec3 cameraDirection = glm::vec3(0.f, 0.0f, 0.0f); // 카메라 봐라보기
//	glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, -1.0f); // 고정 
//	glm::mat4 view = glm::mat4(1.0f);
//	glm::mat4 orbitRot = glm::mat4(1.0f);
//
//	if (Ybutton || ybutton) { // 공전
//
//		view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//		view = glm::rotate(view, glm::radians(carY), glm::vec3(0.0, 1.0, 0.0));
//	}
//	else {
//		view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//	}
//	unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- 뷰잉 변환 설정
//	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//}
