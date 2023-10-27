#version 440 core
layout(location = 0)in vec3 FragPos;
layout(location = 1) in vec2 TexCoord;
layout(location = 2)in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 FragColor;
//uniform sampler2D texture1;

void main() {
    vec3 ambient = 0.1 * lightColor; // Ambient lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor; // Diffuse lighting
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result,1.0f);
    //FragColor = texture(texture1, TexCoord);
}
