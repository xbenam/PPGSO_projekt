#version 330
// A texture is expected as program attribute
struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform Material material;

struct Light {

  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 color;

  float constant;
  float linear;
  float quadratic;
};

struct DirectionalLight {

  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 color;
};

uniform DirectionalLight directLight;

uniform Light light;

uniform vec3 viewPos;

uniform sampler2D Texture;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

uniform vec3 lightColor;

// The vertex shader will feed this input
in vec2 texCoord;

in vec3 FragPos;

// Wordspace normal passed from vertex shader
in vec4 normal;

// The final color
out vec4 FragmentColor;

vec3 DirLight()
{
  vec4 norm = normalize(normal);
  vec4 lightDir = vec4(normalize(directLight.direction),0);
  float diff = max(dot(norm, lightDir), 0.0);

  vec4 viewDir = vec4(normalize(viewPos - FragPos),0);
  vec4 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

  vec3 ambient  = directLight.ambient * material.ambient;
  vec3 diffuse  = directLight.diffuse * (diff * material.diffuse);
  vec3 specular = directLight.specular * (spec * material.specular);

  return (ambient+diffuse+specular) * directLight.color;
}

vec3 LightPoint()
{
  vec4 norm = normalize(normal);
  vec4 lightDir = vec4(normalize(light.position - FragPos),0);
  float diff = max(dot(norm, lightDir), 0.0);

  vec4 viewDir = vec4(normalize(viewPos - FragPos),0);
  vec4 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

  vec3 ambient  = light.ambient * material.ambient;
  vec3 diffuse  = light.diffuse * (diff * material.diffuse);
  vec3 specular = light.specular * (spec * material.specular);

  float distance = length(light.position - FragPos);

  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance*distance));
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient+diffuse+specular) * light.color;
}

void main() {
  // Compute diffuse lighting
  vec3 result = LightPoint() + DirLight();
//  vec3 result = LightPoint();
  // Lookup the color in Texture on coordinates given by texCoord
  // NOTE: Texture coordinate is inverted vertically for compatibility with OBJ
  FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * vec4((result),1);
  FragmentColor.a = Transparency;
}