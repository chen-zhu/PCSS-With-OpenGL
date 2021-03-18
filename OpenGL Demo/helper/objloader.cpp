#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

#include "objloader.hpp"


//https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
void load_obj(const char* filename, vector<glm::vec3> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements, bool swap_y_z)
{
    ifstream in(filename, ios::in);
    if (!in)
    {
        exit(1);
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            if(swap_y_z){
                glm::vec4 v;
                s >> v.x;
                s >> v.z;
                s >> v.y;
                vertices.push_back(v);
            } else {
                glm::vec4 v;
                s >> v.x;
                s >> v.y;
                s >> v.z;
                vertices.push_back(v);
            }
        }
        else if (line.substr(0,2) == "f ")
        {
            GLushort a,b,c;
            string sub_a, sub_b, sub_c;
            
            string substring = line.substr(2);
            
            if(substring.find("/")){
                int find_a_pos = substring.find(" ");
                sub_a = substring.substr(0, find_a_pos);
                istringstream s(sub_a.substr(0, sub_a.find("/")));
                s >> a;
                
                substring = substring.substr(find_a_pos+1);
                int find_b_pos = substring.find(" ");
                sub_b = substring.substr(0, find_b_pos);
                istringstream ss(sub_b.substr(0, sub_b.find("/")));
                ss >> b;
                
                sub_c = substring.substr(find_b_pos+1);
                istringstream sss(sub_c.substr(0, sub_c.find("/")));
                sss >> c;
            } else {
                istringstream s(substring);
                GLushort a,b,c;
                s >> a; s >> b; s >> c;
            }
            
            a--; b--; c--;
           elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
        else if (line[0] == '#')
        {
            /* ignoring this line */
        }
        else
        {
            /* ignoring this line */
        }
    }

    normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (int i = 0; i < elements.size(); i+=3)
    {
        GLushort ia = elements[i];
        GLushort ib = elements[i+1];
        GLushort ic = elements[i+2];
        glm::vec3 normal = glm::normalize(glm::cross(
        glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
        glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
        normals[ia] = normals[ib] = normals[ic] = normal;
    }
}
