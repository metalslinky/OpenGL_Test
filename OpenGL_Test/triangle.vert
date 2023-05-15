#version 330 core
layout ( location = 0 ) in vec3 attributePos;
layout ( location = 1 ) in vec3 attributeColour;

out vec3 vertexColour;

void main() {
	gl_Position = vec4( attributePos.x, -attributePos.y, attributePos.z, 1.0 );
	vertexColour = attributeColour;
}