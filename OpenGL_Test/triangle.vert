#version 330 core
layout ( location = 0 ) in vec3 attributePos;
layout ( location = 1 ) in vec2 attributeTextureCoord;

out vec2 textureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4( attributePos, 1.0 );
	textureCoord = attributeTextureCoord;
}