#version 400

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec4 color;

out vec3 light_intensity;

uniform mat4 mv_mat;
uniform mat3 n_mat;
uniform mat4 p_mat;
uniform mat4 mvp_mat;

uniform vec4 light_pos;
uniform vec3 Kd; // diffuse reflectivity
uniform vec3 Ld; // light source intensity

void main()
{
    vec3 tnorm = normalize(n_mat * norm);
    vec4 eye = mv_mat * vec4(pos, 1.0);
    vec3 light_dir = normalize((light_pos - eye).xyz);
    light_intensity = Ld * Kd * max(dot(light_dir, tnorm), 0.0);
    gl_Position = mvp_mat * vec4(pos, 1.0);
}
