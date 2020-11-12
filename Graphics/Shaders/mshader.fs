#version 330 core
out vec4 FragColor;

<<<<<<< HEAD
<<<<<<< HEAD
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;

    vec4 colorDiffuse;
    vec3 colorSpecular;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
=======
=======
>>>>>>> c561e23f51fcef73f0bc14f7d32dc598985e3643
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

<<<<<<< HEAD
>>>>>>> c561e23f51fcef73f0bc14f7d32dc598985e3643
=======
>>>>>>> c561e23f51fcef73f0bc14f7d32dc598985e3643
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform bool textureMaterial;

void main()
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
    vec4 objectDiffuse = (true == textureMaterial) ? texture(material.diffuse, TexCoords) : material.colorDiffuse;
    vec3 objectSpecular = (true == textureMaterial) ? texture(material.specular, TexCoords).rgb : material.colorSpecular;

>>>>>>> ted/particles2
    // ambient
    vec3 ambient = light.ambient * objectDiffuse.rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * objectDiffuse.rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * objectSpecular;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 
=======
=======
>>>>>>> c561e23f51fcef73f0bc14f7d32dc598985e3643
	/// ambient part of light
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	/// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	/// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
}
>>>>>>> c561e23f51fcef73f0bc14f7d32dc598985e3643

