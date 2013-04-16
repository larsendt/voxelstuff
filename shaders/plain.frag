#version 400

in vec3 light_intensity;

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(light_intensity, 1.0);
}
