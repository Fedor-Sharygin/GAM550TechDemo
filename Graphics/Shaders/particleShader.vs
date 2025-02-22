#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform vec3 position;
uniform vec4 color;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    ParticleColor = color;
    
    gl_Position = projection * view * vec4(position + aPos, 1.0);
}

