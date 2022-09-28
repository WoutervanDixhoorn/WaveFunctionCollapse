#vertexShader
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;

uniform mat4 u_Projection;

out vec2 v_TexCoord;
out vec4 v_Color;

void main()
{
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
    gl_Position = u_Projection * vec4(a_Position, 1.0);
}

#fragmentShader
#version 330 core
uniform sampler2D u_Texture;

in vec2 v_TexCoord;
in vec4 v_Color;

out vec4 FragColor;

void main()
{
    FragColor = v_Color; //texture(u_Texture, v_TexCoord) *
}