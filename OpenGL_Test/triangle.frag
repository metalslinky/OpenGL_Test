#version 330 core
out vec4 fragColour;

in vec3 vertexPos;
in vec3 vertexColour;

void main() {
	fragColour = vec4( vertexPos, 1.0f );
}