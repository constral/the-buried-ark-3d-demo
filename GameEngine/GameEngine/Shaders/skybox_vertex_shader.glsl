#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main() {
    TexCoords = aPos;  // Pass the vertex position to the fragment shader as texture coordinates
    
    // Apply the projection and view matrix to the vertex position
    vec4 pos = projection * view * vec4(aPos, 1.0);
   
    // Use the full position vector (not just X and Y)
    gl_Position = pos;  // This gives us the complete homogeneous clip-space position
}
