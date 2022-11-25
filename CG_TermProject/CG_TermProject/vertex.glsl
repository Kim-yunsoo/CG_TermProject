#version 330 core

layout (location = 0) in vec3 vPos;      //--- ���� ���α׷����� �޾ƿ� ���� ��ǥ��
layout (location = 1) in vec3 vNormal;   //--- ��������
layout (location = 2) in vec3 vColor;

out vec3 FragPos;                  //--- ��ü�� ��ġ���� �����׸�Ʈ ���̴��� ������.
out vec3 outColor;
out vec3 Normal;                  //--- ��ְ��� �����׸�Ʈ ���̴��� ������.

uniform mat4 modelTransform;         //--- �𵨸� ��ȯ
uniform mat4 viewTransform;            //--- ���� ��ȯ(ī�޶�)
uniform mat4 projectionTransform;      //--- ���� ��ȯ(����, ����)

void main()
{
   gl_Position =  projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0);   //--- ��ǥ���� ���� * ī�޶� * �� ��ȯ�� �����Ѵ�.

   FragPos = vec3(modelTransform * vec4(vPos, 1.0));   //--- ��ü�� ���� ���� ����� �����׸�Ʈ ���̴����� �Ѵ�. 
                                          //--- ���� ��������� �ִ� ���ؽ� ���� �����׸�Ʈ ���̴��� ������.
   Normal = mat3(transpose(inverse(modelTransform))) * vNormal;         //--- ��ְ��� �����׸�Ʈ ���̴��� ������.

   outColor = vColor;
}