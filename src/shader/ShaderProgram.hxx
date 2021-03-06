#ifndef SHADERPROGRAM_HXX_
#define SHADERPROGRAM_HXX_

#include <GL/gl.h>

#include <SFML/Graphics.hpp>

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
    explicit ShaderProgram(std::vector<Shader*>& shaders);

    /* Compile method, this will compile and link the shaders together
      \throw CompilationException if a shader compilation is not a success
      \throw LinkingException if the linking of shaders is not a success
    */
    void compile();

    /* Set an int uniform value, given its name. The program must be bound with
      glUseProgram before using this method, otherwise there will be undefined
      behavior depending on the context
      \param name The uniform name
      \param value The int value
    */
    void setInt(std::string name, GLfloat value);

    /* Set a vec3 uniform value, given its name. The program must be bound with
      glUseProgram before using this method, otherwise there will be undefined
      behavior depending on the context
      \param name The uniform name
      \param x First component of the vec3
      \param y Second component of the vec3
      \param z Third component of the vec3
    */
    void setVector3f(std::string name, GLfloat x, GLfloat y, GLfloat z);

    /* Set a vec4 uniform value, given its name. The program must be bound with
      glUseProgram before using this method, otherwise there will be undefined
      behavior depending on the context
      \param name The uniform name
      \param x First component of the vec4
      \param y Second component of the vec4
      \param z Third component of the vec4
      \param w Fourth component of the vec4
    */
    void setVector4f(
      std::string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

    /* Set a bool uniform value, given its name. The program must be bound with
      glUseProgram before using this method, otherwise there will be undefined
      behavior depending on the context
      \param name The uniform name
      \param value The boolean value
    */
    void setBoolean(std::string name, bool value);

    /* Set a matrix uniform value, given its name. The program must be bound with
      glUseProgram before using this method, otherwise there will be undefined
      behavior depending on the context
      \param name The uniform name
      \param matrix The matrix value as a vector of GLfloats
    */
    void setMatrix4fv(std::string name, std::vector<GLfloat>* matrix);

    /* Set the movement matrix
      \param matrix The matrix value as a vector of GLfloats
    */
    void setMoveMatrix(std::vector<GLfloat>* matrix);

    /* Set the view matrix
      \param matrix The matrix value as a vector of GLfloats
    */
    void setViewMatrix(std::vector<GLfloat>* matrix);

    /* Set the projection matrix
      \param matrix The matrix value as a vector of GLfloats
    */
    void setProjectionMatrix(std::vector<GLfloat>* matrix);

    /* Set the normal matrix
      \param matrix The matrix value as a vector of GLfloats
    */
    void setNormalMatrix(std::vector<GLfloat>* matrix);

    /* Bind a texture to sampler "n"
      \param n The index of the sampler
      \param target The target for the sampler, must be GL_TEXTUREn with n the
        index of the sampler
      \param name The name of the sampler in shaders
      \param value The texture
    */
    void bindTexture(GLuint n, GLenum target, std::string name, GLuint texture);

    /* Bind an SFML texture to sampler "n"
      \param n The index of the sampler
      \param target The target for the sampler, must be GL_TEXTUREn with n the
        index of the sampler
      \param name The name of the sampler in shaders
      \param texture The SFML texture
    */
    void bindTexture(GLuint n, GLenum target, std::string name, sf::Texture* texture);

    /* Destructor, this will remove the shaders from memory */
    ~ShaderProgram();
};

#endif
