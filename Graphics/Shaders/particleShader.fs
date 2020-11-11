#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 ParticleColor;

uniform sample2D particleTexture;

void main()
{
	FragColor = texture(particleTexture, TexCoords) * ParticleColor;
}

