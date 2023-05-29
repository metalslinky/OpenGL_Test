#version 330 core
layout ( location = 0 ) in vec3 attributePos;
layout ( location = 1 ) in vec3 attributeColour;
layout ( location = 2 ) in vec2 attributeTextureCoord;

out vec3 vertexColour;
out vec2 textureCoord;

void main() {
	gl_Position = vec4( attributePos, 1.0 );
	vertexColour = attributeColour;
	textureCoord = attributeTextureCoord;
}