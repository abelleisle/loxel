#version 130

//layout(location = 0)in vec3 vertex;
in vec3 vertex;
in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec2 tex_cord;

void main()
{
    tex_cord = texCoord;
    gl_Position = projection * view * model * vec4(vertex, 1.0f);
}
