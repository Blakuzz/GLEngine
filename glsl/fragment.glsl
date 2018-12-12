#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 textureCoord;

uniform sampler2D texture0;
//uniform sampler2D texture1;

uniform vec3 lightColor;

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
	FragColor = texture(texture0, textureCoord) * lightColor;
	//FragColor = mix(texture(texture0, textureCoord), texture(texture1, textureCoord), 0.5);
} 