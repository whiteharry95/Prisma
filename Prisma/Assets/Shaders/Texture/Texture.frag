#version 410 core

in float v_TextureIndex;
in vec2 v_TextureCoordinate;
in float v_Opacity;

out vec4 v_Color;

uniform sampler2D u_Samplers[32];

void main(){
	v_Color = texture(u_Samplers[int(v_TextureIndex)], v_TextureCoordinate) * vec4(vec3(1.f), v_Opacity);
}