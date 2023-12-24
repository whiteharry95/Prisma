#version 410 core
layout (location = 0) in float a_TextureIndex;
layout (location = 1) in vec2 a_TextureCoordinate;
layout (location = 2) in vec2 a_VertexCoordinate;
layout (location = 3) in vec2 a_Position;
layout (location = 4) in float a_Rotation;
layout (location = 5) in vec2 a_Size;
layout (location = 6) in float a_Opacity;

out float v_TextureIndex;
out vec2 v_TextureCoordinate;
out float v_Opacity;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main(){
	mat4 modelMatrix = mat4(
		a_Size.x * cos(a_Rotation), -a_Size.x * sin(a_Rotation), 0.f, 0.f,
		a_Size.y * sin(a_Rotation), a_Size.y * cos(a_Rotation), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		a_Position.x, a_Position.y, 0.f, 1.f
	);

	gl_Position = u_ProjectionMatrix * u_ViewMatrix * modelMatrix * vec4(a_VertexCoordinate, 0.f, 1.f);
	
	v_TextureIndex = a_TextureIndex;
	v_TextureCoordinate = a_TextureCoordinate;
	v_Opacity = a_Opacity;
}