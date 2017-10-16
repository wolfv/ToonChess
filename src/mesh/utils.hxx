#ifndef UTILS_HXX_
#define UTILS_HXX_

#include <GL/gl.h>

#include <vector>
#include <string>

template<typename Out>
void split(const std::string &s, char delim, Out result);

std::vector<std::string> split(const std::string &s, char delim);

void extractFloatVec3(std::vector<std::string> *line, std::vector<GLfloat> *vector);

void extractFace(std::vector<std::string> *line, std::vector<GLuint> *indices);

#endif