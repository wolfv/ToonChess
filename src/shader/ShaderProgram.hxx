#ifndef SHADERPROGRAM_HXX_
#define SHADERPROGRAM_HXX_

#include <GL/gl.h>

#include <vector>

#include "Shader.hxx"

class ShaderProgram {
  public:
    /* The list of shaders to use in this program */
    std::vector<Shader*> shaders;

    /* The ID of the program */
    GLuint id;

    /* Constructor
      \param shaders The list of shaders to use in this program
    */
    explicit ShaderProgram(std::vector<Shader*> shaders);

    /* Compile method, this will compile and link the shaders together
      \throw CompilationException if a shader compilation is not a success
      \throw LinkingException if the linking of shaders is not a success
    */
    void compile();

    /* Set a vec4 uniform value, given its name. The program must be bind with
      glUseProgram before using this method, otherwise there will be undefined
      behavior depending on the context
      \param name The uniform name
      \param x First component of the vec4
      \param y Second component of the vec4
      \param z Third component of the vec4
      \param w Fourth component of the vec4
    */
    void setUniform4f(
      std::string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

    /* Destructor, this will remove the shaders from memory */
    ~ShaderProgram();
};

#endif
