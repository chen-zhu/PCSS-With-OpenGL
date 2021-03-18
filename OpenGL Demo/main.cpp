// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;

#include "helper/shader.hpp"
#include "helper/objloader.hpp"
#include "helper/control.hpp"


//thanks to the tutorial from
//https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/basic_lighting_specular.cpp

const unsigned int WIDTH = 1300;
const unsigned int HEIGHT = 1300;

const unsigned int SHADOW_WIDTH = 1024;
const unsigned int SHADOW_HEIGHT = 1024;

void drawFloor(float floor_scale, GLuint planeVAO, Shader itemShader);
void drawObject(GLuint VertexArrayID, float object_scale, GLuint vertexbuffer, GLuint normalbuffer, GLuint indicesbuffer, Shader itemShader, float translate_x = 0.0f, float translate_y = -0.2f, float translate_z = 0.0f, glm::vec3 object_color = glm::vec3(1, 0.53, 0), glm::vec3 rotate_axis = glm::vec3(0.0f, 1.0f, 0.0f));


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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // this line is for MacOS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "280 Final Proj - Chen Zhu", NULL, NULL);
    int retina_w, retina_h;
    glfwGetFramebufferSize(window, &retina_w, &retina_h);
    
    
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

    glViewport(0, 0, retina_w, retina_h);
    
    // grey background
    //glClearColor(0.53f, 0.81f, 0.98f, 0.0f);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // create shader for the item object
    Shader itemShader("vertexShader", "fragmentShader");
    
       
    //OBJECT Buffer!
    //here to load obj/or create vertex!
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<GLushort> indices; // Won't be used at the moment.
    //load_obj("spot_triangulated.obj", vertices, normals, indices, false);
    load_obj("bunny.obj", vertices, normals, indices, false);
    float object_scale_1 = 0.6;
    //printf("%d", vertices.size());
    
    //vertex buffer
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    
    //normal buffer
    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    
    //indices buffer
    GLuint indicesbuffer;
    glGenBuffers(1, &indicesbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);
    
    
    //OBJECT Buffer!
    //here to load obj/or create vertex!
    std::vector<glm::vec3> vertices2;
    std::vector<glm::vec3> normals2;
    std::vector<GLushort> indices2; // Won't be used at the moment.
    load_obj("spot_triangulated.obj", vertices2, normals2, indices2, false);
    float object_scale_2 = 3.5;
    
    //vertex buffer
    GLuint vertexbuffer2;
    glGenBuffers(1, &vertexbuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
    glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);
    
    //normal buffer
    GLuint normalbuffer2;
    glGenBuffers(1, &normalbuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
    glBufferData(GL_ARRAY_BUFFER, normals2.size() * sizeof(glm::vec3), &normals2[0], GL_STATIC_DRAW);
    
    //indices buffer
    GLuint indicesbuffer2;
    glGenBuffers(1, &indicesbuffer2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(unsigned short), &indices2[0] , GL_STATIC_DRAW);
    
    
    
    //OBJECT Buffer!
    //here to load obj/or create vertex!
    std::vector<glm::vec3> vertices3;
    std::vector<glm::vec3> normals3;
    std::vector<GLushort> indices3; // Won't be used at the moment.
    load_obj("pumpkin.obj", vertices3, normals3, indices3, false);
    float object_scale_3 = 200;
    
    //vertex buffer
    GLuint vertexbuffer3;
    glGenBuffers(1, &vertexbuffer3);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
    glBufferData(GL_ARRAY_BUFFER, vertices3.size() * sizeof(glm::vec3), &vertices3[0], GL_STATIC_DRAW);
    
    //normal buffer
    GLuint normalbuffer3;
    glGenBuffers(1, &normalbuffer3);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer3);
    glBufferData(GL_ARRAY_BUFFER, normals3.size() * sizeof(glm::vec3), &normals3[0], GL_STATIC_DRAW);
    
    //indices buffer
    GLuint indicesbuffer3;
    glGenBuffers(1, &indicesbuffer3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices3.size() * sizeof(unsigned short), &indices3[0] , GL_STATIC_DRAW);
    
    float floor[] = {
        // positions            // normals
         2.0f, -0.5f,  -1.5f,  0.0f, 1.0f, 0.0f,
        -2.0f, -0.5f,  -1.5f,  0.0f, 1.0f, 0.0f,
        -2.0f, -0.5f,   1.5f,  0.0f, 1.0f, 0.0f,

         2.0f, -0.5f,  -1.5f,  0.0f, 1.0f, 0.0f,
        -2.0f, -0.5f,   1.5f,  0.0f, 1.0f, 0.0f,
         2.0f, -0.5f,   1.5f,  0.0f, 1.0f, 0.0f
    };
    GLuint planeVBO;
    GLuint planeVAO;
    float floor_scale = 1;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor), floor, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glBindVertexArray(VertexArrayID);
    
    //https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
    //Depth map - Create Framebuffer Object
    
    Shader shadowShader("shadowVertexShader", "shadowFragmentShader");
    GLuint depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    
    //Then 2D texture as the framebuffer depth buffer
    GLuint depthMap;
    glGenTextures(1, &depthMap);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); //What is this for?
    // Depth Texture -> FBO depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE); //no need to pass in any color here~
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
    GLuint depthMapFBO2;
    glGenFramebuffers(1, &depthMapFBO2);

    //Then 2D texture as the framebuffer depth buffer
    GLuint depthMap2;
    glGenTextures(1, &depthMap2);
    glBindTexture(GL_TEXTURE_2D, depthMap2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // Depth Texture -> FBO depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO2);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap2, 0);
    glDrawBuffer(GL_NONE); //no need to pass in any color here~
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    
    //itemShader.use();
    itemShader.setInt("shadowMap", 0);
    itemShader.setInt("shadowMap2", 1);
    
    glm::vec3 lightPos = glm::vec3(2.0f, 0.8f, 1.0f);
    glm::vec3 lightColor = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)retina_w / (float)retina_h, 0.1f, 100.0f);
    
    //double lastTime = glfwGetTime();
    //int nbFrames = 0;
    
    do{
        /*double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%d frames per second\n", nbFrames);
            nbFrames = 0;
            lastTime += 1.0;
        }*/
        
        //Clear the screen buffer
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //float light_X = sin(0.4 * glfwGetTime()) * 1.6f;
        float light_X = 1.2f;
        float light_Z = 2.5f;
        lightPos = glm::vec3(light_X, 0.8f, light_Z);
        
        /**
         Render Shadow Depth here~
        */
        //shadowShader.use();
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 7.0f;
        lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
        //lightProjection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;

        // render scene from light's point of view
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        shadowShader.use();
        shadowShader.setMat4("LIGHTSPACE", lightSpaceMatrix);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawFloor(floor_scale, planeVAO, shadowShader);
        //bunny
        drawObject(VertexArrayID, object_scale_1, vertexbuffer, normalbuffer, indicesbuffer, shadowShader, 0.0f, -0.5f, 0.5f, glm::vec3(0.9, 0.9, 0.9), glm::vec3(0.0f, 1.0f, 0.0f));
        //cow
        drawObject(VertexArrayID, object_scale_2, vertexbuffer2, normalbuffer2, indicesbuffer2, shadowShader, -0.5f, -0.20f, 0.3f, glm::vec3(0.63, 0.32, 0.18), glm::vec3(0.0f, 1.0f, 0.0f));
        //pumpkin
        drawObject(VertexArrayID, object_scale_3, vertexbuffer3, normalbuffer3, indicesbuffer3, shadowShader, 0.5f, 0.3f, 0.0f, glm::vec3(0.9, 0.55, 0.2), glm::vec3(1.0f, 0.0f, 0.0f));
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        
        //-------second light
        
        glm::vec3 lightPos2 = glm::vec3(-1.2f, 0.8f, 2.5f);

        glm::mat4 lightSpaceMatrix2;
        //shadowShader.use();
        lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
        //lightProjection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightPos2, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix2 = lightProjection * lightView;

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        shadowShader.use();
        shadowShader.setMat4("LIGHTSPACE", lightSpaceMatrix2);
        
        // render scene from light's point of view
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO2);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawFloor(floor_scale, planeVAO, shadowShader);
        //bunny
        drawObject(VertexArrayID, object_scale_1, vertexbuffer, normalbuffer, indicesbuffer, shadowShader, 0.0f, -0.5f, 0.5f, glm::vec3(0.9, 0.9, 0.9), glm::vec3(0.0f, 1.0f, 0.0f));
        //cow
        drawObject(VertexArrayID, object_scale_2, vertexbuffer2, normalbuffer2, indicesbuffer2, shadowShader, -0.5f, -0.20f, 0.3f, glm::vec3(0.63, 0.32, 0.18), glm::vec3(0.0f, 1.0f, 0.0f));
        //pumpkin
        drawObject(VertexArrayID, object_scale_3, vertexbuffer3, normalbuffer3, indicesbuffer3, shadowShader, 0.5f, 0.3f, 0.0f, glm::vec3(0.9, 0.55, 0.2), glm::vec3(1.0f, 0.0f, 0.0f));
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        
        /**
         Render Normal Object here~
         */
        
        //Reset before drawing the object
        glViewport(0, 0, retina_w, retina_h);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        itemShader.use();
        
        //Deal with view position here
        float view_X = sin(0.4*glfwGetTime()) * 5.0f;
        float View_Z = cos(0.4*glfwGetTime()) * 5.0f;
        //float view_X = sin(0) * 3.0f;
        //float View_Z = cos(0) * 3.0f;
        float View_Y = std::abs(cos(0.5*glfwGetTime()) * 5.0f);
        
        glm::vec3 viewPos = glm::vec3(view_X, View_Y, View_Z);
        //glm::vec3 viewPos = glm::vec3(0, 1.0f, 2.0f);
        itemShader.setVec3("VIEW_POS", viewPos);
        
        //View --> world to view
        glm::mat4 view = glm::lookAt(
                           viewPos,
                           glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 3.0f, 0.0f));
        itemShader.setMat4("VIEW", view);
        
        //Projection --> view to clip
        //glm::mat4 projection = glm::mat4(1.0f);
        //projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        itemShader.setMat4("PROJECTION", projection);
        
        //std::cout<<glm::to_string(projection)<<std::endl;
        
        //Deal with light color here~
        itemShader.setVec3("LIGHT_COLOR", lightColor);
        
        //Deal with light position here
        itemShader.setVec3("LIGHT_POS", lightPos);
        
        itemShader.setMat4("LIGHTSPACE", lightSpaceMatrix);
        
        
        itemShader.setVec3("LIGHT_POS2", lightPos2);
        
        itemShader.setMat4("LIGHTSPACE2", lightSpaceMatrix2);
        
//        shadowShader.use();
        itemShader.setInt("shadowMap", 0);
        itemShader.setInt("shadowMap2", 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glActiveTexture(GL_TEXTURE0+1);
        glBindTexture(GL_TEXTURE_2D, depthMap2);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, depthMap);
        
        drawFloor(floor_scale, planeVAO, itemShader);
        //bunny
        drawObject(VertexArrayID, object_scale_1, vertexbuffer, normalbuffer, indicesbuffer, itemShader, 0.0f, -0.5f, 0.5f, glm::vec3(0.9, 0.9, 0.9), glm::vec3(0.0f, 1.0f, 0.0f));
        //cow
        drawObject(VertexArrayID, object_scale_2, vertexbuffer2, normalbuffer2, indicesbuffer2, itemShader, -0.5f, -0.20f, 0.3f, glm::vec3(0.53, 0.22, 0.08), glm::vec3(0.0f, 1.0f, 0.0f));
        //pumpkin
        drawObject(VertexArrayID, object_scale_3, vertexbuffer3, normalbuffer3, indicesbuffer3, itemShader, 0.5f, 0.3f, 0.0f, glm::vec3(0.9, 0.55, 0.2), glm::vec3(1.0f, 0.0f, 0.0f));
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteBuffers(1, &vertexbuffer2);
    glDeleteBuffers(1, &normalbuffer2);
    glDeleteBuffers(1, &vertexbuffer3);
    glDeleteBuffers(1, &normalbuffer3);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(itemShader.ID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


void drawFloor(float floor_scale, GLuint planeVAO, Shader itemShader){
    //Draw floor here
    glm::mat4 model = glm::mat4(1.0f);
    //std::cout<<"before: " << glm::to_string(model)<<std::endl;
    model = glm::scale(model, glm::vec3(1/floor_scale));
    //std::cout<<"after:" << glm::to_string(model)<<std::endl;
    itemShader.setMat4("MODEL", model);
    itemShader.setVec3("OBJ_COLOR", glm::vec3(0.95, 1.0, 1.0));
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void drawObject(GLuint VertexArrayID, float object_scale, GLuint vertexbuffer, GLuint normalbuffer, GLuint indicesbuffer, Shader itemShader, float translate_x, float translate_y, float translate_z, glm::vec3 object_color, glm::vec3 rotate_axis){
    //set back to vertex array of the object
    glBindVertexArray(VertexArrayID);
    
    //Model --> local to world
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(0.0f));
    model = glm::translate(model, glm::vec3(translate_x, translate_y, translate_z));
    model = glm::rotate(model, glm::radians(-90.0f), rotate_axis);
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1/object_scale));
    itemShader.setMat4("MODEL", model);
    itemShader.setVec3("OBJ_COLOR", object_color);
    
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    
    // 2nd place attribute buffer: normal
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(
        1,                  // attribute 1.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    
    //process indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer);
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    
}




