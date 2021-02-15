#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "shader.hpp"

GLuint load_shaders(const char * vertex_file_path,const char * fragment_file_path){

        // Create the shaders
        //*** A completer *************/
        //use glCreateShader()

        //**********************/

        // Read the Vertex Shader code from the file
        std::string vertex_shader_code;
        std::ifstream vertex_shader_stream(vertex_file_path, std::ios::in);
        if(vertex_shader_stream.is_open()){
                std::stringstream sstr;
                sstr << vertex_shader_stream.rdbuf();
                vertex_shader_code = sstr.str();
                vertex_shader_stream.close();
        }else{
                printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
                getchar();
                return 0;
        }

        // Read the Fragment Shader code from the file
        std::string fragment_shader_code;
        std::ifstream fragment_shader_stream(fragment_file_path, std::ios::in);
        if(fragment_shader_stream.is_open()){
                std::stringstream sstr;
                sstr << fragment_shader_stream.rdbuf();
                fragment_shader_code = sstr.str();
                fragment_shader_stream.close();
        }

        GLint result = GL_FALSE;
        int info_log_length;


        //*** A completer *************/

        // Compile Vertex Shader

        printf("Compiling shader : %s\n", vertex_file_path);
        char const * vertex_source_pointer = vertex_shader_code.c_str();

        //Ajouter ici
        // Check Vertex Shader
        //Ajouter ici

        //**********************/


        //*** A completer *************/

        // Compile Fragment Shader
        printf("Compiling shader : %s\n", fragment_file_path);
        char const * FragmentSourcePointer = fragment_shader_code.c_str();

        // Check Fragment Shader

        //**********************/



        //*** A completer *************/
        // Link the program
        printf("Linking program\n");

        // Check the program

        //**********************/

        //*** A completer *************/

        //Detacher et supprimer


        //******************************/

        //return *program_ID;

        return 0; //A changer
        //******************************/
}


