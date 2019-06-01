#version 130

#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif

uniform sampler2D texture;
uniform sampler2D normal;

varying vec2 tex_cord;
out vec4 FragColor;

void main()
{
    vec2 TexLoc = vec2(tex_cord.x, 1-tex_cord.y);
    vec4 n_color = texture2D(normal, TexLoc);
    vec4 t_color = texture2D(texture, TexLoc); 
    FragColor = t_color + (n_color * .1);
}
