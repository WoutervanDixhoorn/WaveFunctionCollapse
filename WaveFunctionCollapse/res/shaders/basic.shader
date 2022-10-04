#vertexShader
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_Tilling;

uniform mat4 u_ViewProjection;

out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexIndex;
out float v_Tilling;

void main()
{
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
    v_TexIndex = a_TexIndex;
    v_Tilling = a_Tilling;

    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#fragmentShader
#version 330 core
uniform sampler2D u_Textures[32];

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;
in float v_Tilling;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_Tilling) * v_Color;
}