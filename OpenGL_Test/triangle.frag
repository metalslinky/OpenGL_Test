#version 330 core
out vec4 fragColour;

in vec3 vertexColour;
in vec2 textureCoord;

uniform sampler2D fragTexture1;
uniform sampler2D fragTexture2;

void main() {
	fragColour = mix( texture( fragTexture1, textureCoord ), texture( fragTexture2, textureCoord ), 0.2 );
	//fragColour = texture( fragTexture1, textureCoord );
}