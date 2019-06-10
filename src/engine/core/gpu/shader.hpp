#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <string>
#include <memory>
#include <glbinding/gl/gl.h>

class Shader;
typedef std::shared_ptr<Shader> Shader_ptr;

class Shader {
public:
    template <class ...Args>
    static Shader_ptr Make(Args&& ...args) {
        return Shader_ptr(new Shader(std::forward<Args>(args)...));
    }

    // will be casted to gl::GLenum
    enum Type : unsigned int {
        vertex   = 0x8B31,
        fragment = 0x8B30
    };

    gl::GLuint id;
    const Type type;

    ~Shader();
    
private:
    Shader(const Shader& copy) = default;
    Shader(const std::string& source, const Type type);
};


#endif//SHADER_HPP_
