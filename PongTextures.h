

#ifndef PongTextures
#define PongTextures

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include<string>
#include<exception>

#include <GL/glew.h> 


class Texture{
	private:
		GLuint ID;
	public:
		Texture(std::string filename);
		inline void use();
};

Texture::Texture(std::string){
	glGenTextures(1, this->ID);
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (!data)
		throw std::runtime_error(std::string("Failed to generate texture: ") + filename);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

inline void Texture::use(){
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

#endif
