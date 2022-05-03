#version 330 core
layout (location = 0) in vec3 pos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
layout (location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main()
{
    // note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(pos, 1.0);
	UV = vertexUV;
}
