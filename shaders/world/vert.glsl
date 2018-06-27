#version 450

layout(location = 0)in vec3 vertex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

//out vec3 texCoord;

void main()
{
    //texCoord = vertex;
    gl_Position = projection * view * model * vec4(vertex, 1.0f);
    //gl_Position = vec4(vertex, 1.0f);
}
