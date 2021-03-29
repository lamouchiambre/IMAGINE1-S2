// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cmath>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace glm;

#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 camera_position   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);
// glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
//                    glm::vec3(0.0f, 0.0f, 0.0f), 
//                    glm::vec3(0.0f, 1.0f, 0.0f));
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//rotation
float angle = 0.;
float zoom = 1.;

//time i
float i = 0.0f;

/*******************************************************************************/

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "TP4 - Transformations", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    //  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Dark blue background
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    //glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "vertex_shader.glsl", "fragment_shader.glsl" );

    /*****************TODO***********************/
    // Get a handle for our "Model View Projection" matrices uniforms

    /****************************************/
    std::vector<unsigned short> indices; //Triangles concaténés dans une liste
    std::vector<std::vector<unsigned short> > triangles;
    std::vector<glm::vec3> indexed_vertices;

    //Chargement du fichier de maillage
    //std::string filename("chair.off");
    std::string filename("sphere.off");
    loadOFF(filename, indexed_vertices, indices, triangles );

    // Load it into a VBO

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
    


    // For speed computation
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    
    do{

        // Measure speed
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);


        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        /*****************TODO***********************/
        // Model matrix : an identity matrix (model will be at the origin) then change

        // View matrix : camera/view transformation lookat() utiliser camera_position camera_target camera_up

        // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units

        // Send our transformation to the currently bound shader,
        // in the "Model View Projection" to the shader uniforms

        /****************************************/

        //les astres
        glm::mat4 lune, terre, soleil, mars, mercure, venus, jupiter, saturne, uranus, neptune;

        //CONSTRUCTION DU DESSIN
        soleil = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(camera_position, camera_position + camera_target, camera_up);
        glm::mat4 mvp_out = projection * view * soleil;
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                    0,                  // attribute
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                    );

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        GLuint MVP_id = glGetUniformLocation(programID, "MVP");

        GLuint myLoc = glGetUniformLocation(programID, "in_color");
        //glProgramUniform4fv(p, myLoc, 1, myFloats);


        soleil = glm::rotate(soleil, glm::radians(5.0f+i), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 color_p = glm::vec3(1.0f, 1.0f, 0.0f);
        glUniform3fv(myLoc, 1, &color_p[0]);
        glUniformMatrix4fv(MVP_id, 1, false, &mvp_out[0][0]);
        
        glDrawElements(
                    GL_LINES,      // mode
                    indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );

        // terre

        terre = glm::translate(soleil, glm::vec3(10.0f, 0.0f, 0.0f));
        terre = glm::scale(terre, glm::vec3(0.5f, 0.5f, 0.5f));
        terre =  glm::rotate(terre, glm::radians(23.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        terre =  glm::rotate(terre, glm::radians(23.0f+i*23.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        
        mvp_out = projection * view * terre;

        color_p = glm::vec3(0.0f, 1.0f, 1.0f);

        glUniform3fv(myLoc, 1, &color_p[0]);
        glUniformMatrix4fv(MVP_id, 1, false, &mvp_out[0][0]);
        glDrawElements(
                    GL_LINES,      // mode
                    indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );


        //lune
        lune = glm::translate(terre, glm::vec3(2.0f, 0.0f, 0.0f));
        //lune = glm::rotate(terre, glm::radians(23.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        lune = glm::scale(lune, glm::vec3(0.2f, 0.2f, 0.2f));
        lune = glm::rotate(lune, glm::radians(-6.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        lune = glm::rotate(lune, glm::radians(45.0f + i*45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        mvp_out = projection * view * lune;

        color_p = glm::vec3(0.2f, 0.2f, 1.0f);

        glUniform3fv(myLoc, 1, &color_p[0]);
        glUniformMatrix4fv(MVP_id, 1, false, &mvp_out[0][0]);
        glDrawElements(
                    GL_LINES,      // mode
                    indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );

        // //mars
        mars = glm::translate(soleil, glm::vec3(13.0f, 0.0f, 0.0f));
        mars = glm::scale(mars, glm::vec3(0.4f, 0.4f, 0.4f));

        mvp_out = projection * view * mars;

        color_p = glm::vec3(1.0f, 0.2f, 0.0f);

        glUniform3fv(myLoc, 1, &color_p[0]);
        glUniformMatrix4fv(MVP_id, 1, false, &mvp_out[0][0]);
        glDrawElements(
                    GL_LINES,      // mode
                    indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );

        // //mars
        // mars = soleil;
        mercure = glm::translate(soleil, glm::vec3(6.0f, 0.0f, 1.0f));
        mercure = glm::scale(mercure, glm::vec3(0.4f, 0.4f, 0.4f));

        mvp_out = projection * view * mercure;

        color_p = glm::vec3(1.0f, 0.5f, 0.0f);

        glUniform3fv(myLoc, 1, &color_p[0]);
        glUniformMatrix4fv(MVP_id, 1, false, &mvp_out[0][0]);
        glDrawElements(
                    GL_LINES,      // mode
                    indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );

        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //Camera zoom in and out
    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera_position += cameraSpeed * camera_target;
        //printf("w\n");
    }
        
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera_position -= cameraSpeed * camera_target;
        //printf("s\n");
    }
        
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera_position -= glm::normalize(glm::cross(camera_target, camera_up)) * cameraSpeed;
        //printf("a\n");
    }
        
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera_position += glm::normalize(glm::cross(camera_target, camera_up)) * cameraSpeed;
        //printf("d\n");
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        i++;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        i--;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
