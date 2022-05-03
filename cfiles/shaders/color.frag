#version 330 core

// Interpolated values from the vertex shaders

// Ouput data
out vec3 color;
in vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){

    // Output color = color of the texture at the specified UV
//	color = vec3(1,0,0);
   color = texture(myTextureSampler, UV).rgb;
}
