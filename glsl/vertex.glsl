#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoord;

uniform mat4 transformation;

out vec3 ourColor;
out vec2 textureCoord;

void main(){
	gl_Position = transformation * vec4(aPos, 1.0);
	//gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	textureCoord = aTextureCoord;
}