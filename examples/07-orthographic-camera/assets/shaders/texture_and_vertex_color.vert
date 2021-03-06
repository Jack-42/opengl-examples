#version 330 core

uniform mat4 u_mvpMatrix;

in vec2 a_position;
in vec3 a_color;
in vec2 a_textureCoord;

out vec3 v_color;
out vec2 v_textureCoord;

void main()
{
    v_color = a_color;
    v_textureCoord = a_textureCoord;
    
    gl_Position = u_mvpMatrix * vec4(a_position, 0.0, 1.0);
}
