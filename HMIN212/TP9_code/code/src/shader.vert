#version 120

varying vec4 P; // Per-vertex position
varying vec3 N; // Per-vertex normal
varying vec4 C; // Per-vertex color
//varying vec4 UV; // Per-vertex color


uniform mat4 modelviewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

void main(void) {
    P = gl_Vertex;
    N = gl_Normal;
    C = gl_Color;
    //UV = gl_MutiTexCoord0;

    vec4 p = projectionMatrix * modelviewMatrix * P;
    // gl_Position = vec4(p.xyz / p.w, 1); // this gives an error !
    gl_Position = p;
}
