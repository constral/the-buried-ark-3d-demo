#version 330 core

in vec3 TexCoords;

out vec4 FragColor;

uniform samplerCube skybox;  // Texture sampler for the cubemap

void main() {

    FragColor = texture(skybox, TexCoords);  // Sample the cubemap texture at the given coordinates

}