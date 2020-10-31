#version 330 core
layout (location = 0) in vec3 position; // <vec2 position, vec2 texCoords>
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform vec3 offset;
uniform vec4 color;

void main()
{
    float scale = 1000.0f;
    TexCoords = texCoords;
    ParticleColor = color;
    gl_Position = projection * vec4((position * scale) + offset, 1.0);
}

