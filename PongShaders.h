
#ifndef PongShaders
#define PongShaders

#include<string>
#include<vector>
#include<exception>

#include <GL/glew.h> 

#include"PongIO.h"

class Shader{
	private:
		GLuint ID;
		GLenum type;
	public:
		Shader() = delete;
		Shader(GLenum type, const std::string& input, bool isfile);
		~Shader();
		GLuint getID();
		GLenum getType();
};

Shader::Shader(GLenum type_, const std::string& input, bool isfile = true){
	this->type = type_;
	this->ID = glCreateShader(this->type); 
	const char* sourceCode = isfile ? readFile(input).c_str() : input.c_str();
	glShaderSource(this->ID, 1, &sourceCode, NULL);
	glCompileShader(this->ID);
	GLint success = 0;
	glGetShaderiv(this->ID, GL_COMPILE_STATUS, &success);
	if(!success){
		char errorLog[512];
		glGetShaderInfoLog(this->ID, 512, NULL, errorLog);
		throw std::runtime_error(std::string("Failed to compile shader: ") + (isfile ? input : "") + "\n" + errorLog + "\n");
	}
}

Shader::~Shader(){
	glDeleteShader(this->ID);
}

GLuint Shader::getID(){
	return this->ID;
}

class ShaderProgram{
	private:
		GLuint ID;
		inline void link();
	public:
		ShaderProgram() = delete;
		ShaderProgram(const std::vector<Shader&>& shaders);
		ShaderProgram(const std::vector<GLenum>& types, const std::vector<std::string>& input, bool isfile);
		inline void use();
};

ShaderProgram::ShaderProgram(const std::vector<Shader&>& shaders){
	this->ID = glCreateProgram();
	for(int i = 0; i < shaders.size(); i++)
		glAttachShader(this->ID, shaders[i].getID());
	link();
}

ShaderProgram::ShaderProgram(const std::vector<GLenum>& types, const std::vector<std::string>& input, bool isfile = true){
	if(types.size() != input.size())
		throw std::invalid_argument(std::string("Malformed Shader Program Constructor Inputs: ") + std::to_string(types.size()) + "!=" + std::to_string(input.size()) + "\n");
	this->ID = glCreateProgram();
	for(int i = 0; i < types.size(); i++){
		Shader shader(types[i], input[i], isfile);
		glAttachShader(this->ID, shader.getID());
	}
	link();
}

inline void ShaderProgram::link(){
	glLinkProgram(this->ID);
	GLint success = 0;
	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if(!success){
		char errorLog[512];
		glGetProgramInfoLog(this->ID, 512, NULL, errorLog);
		throw std::runtime_error(std::string("Failed to link shader program: ") + "\n" + errorLog + "\n");
	}
}

inline void ShaderProgram::use(){
	glUseProgram(this->ID);
}

#endif

/*
https://stackoverflow.com/questions/6432838/what-is-the-correct-file-extension-for-glsl-shaders
.vert - a vertex shader
.tesc - a tessellation control shader
.tese - a tessellation evaluation shader
.geom - a geometry shader
.frag - a fragment shader
.comp - a compute shader
*/