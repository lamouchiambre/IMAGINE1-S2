#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

//Definir une matrice MVP

void main(){


        gl_Position =  vec4(vertexPosition_modelspace,1);

}

