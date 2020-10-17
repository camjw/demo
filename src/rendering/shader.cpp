#include <rendering/shader.h>

void Shader::init(const std::string& vertex_filepath, const std::string& fragment_filepath)
{
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vertex_file;
    std::ifstream fragment_file;

    vertex_file.open(vertex_filepath);
    fragment_file.open(fragment_filepath);
    std::stringstream vertex_stream, fragment_stream;
    vertex_stream << vertex_file.rdbuf();
    fragment_stream << fragment_file.rdbuf();
    vertex_file.close();
    fragment_file.close();
    vertex_code = vertex_stream.str();
    fragment_code = fragment_stream.str();

    const char* vShaderCode = vertex_code.c_str();
    const char* fShaderCode = fragment_code.c_str();

    unsigned int vertex, fragment;

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX");

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT");

    // shader Program
    id_ = glCreateProgram();
    glAttachShader(id_, vertex);
    glAttachShader(id_, fragment);
    glLinkProgram(id_);
    check_compile_errors(id_, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::destroy() const
{
    glDeleteProgram(id_);
}