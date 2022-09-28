#vertexShader
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in int a_TexIndex;

uniform mat4 u_Projection;
//uniform mat4 u_Model;

out vec2 v_TexCoord;
out vec4 v_Color;
flat out v_TexIndex;

void main()
{
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
    v_TexIndex = int(a_TexIndex);
    gl_Position = u_Projection * vec4(a_Position, 1.0);
}

#fragmentShader
#version 330 core

//uniform vec4 u_Color;
uniform sampler2D u_Texture;
//uniform float u_Tilling;

in vec2 v_TexCoord;
in vec4 v_Color;
in int v_TexIndex;

out vec4 FragColor;

//uniform Sampler2D u_Sampler;

void main()
{
    FragColor = texture(u_Texture, v_TexCoord) * v_Color;
}