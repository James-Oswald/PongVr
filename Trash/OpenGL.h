
#include<GL/gl.h>
#define GL_GLEXT_PROTOTYPES
#include<GL/glext.h>
#include<GL/wglext.h>


//PFNGLGENBUFFERSARBPROC glGenBuffers;
 //glShaderSource
 //glCompileShader
 //glCreateProgram
 //glAttachShader
 //glLinkProgram
 //glDeleteShader
 //glGenBuffers
 //glBindVertexArray
 //glBindBuffer
 //glBufferData
 //glVertexAttribPointer
 //glEnableVertexAttribArray
//PFNGLUSEPROGRAMPROC glUseProgram

inline void initFunctions(){
	
}
//glCreateShader

/*inline void InitOGL()
{
	float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
	};
	GLuint hVBO;
	glGenBuffers(1, &hVBO);
	glBindBuffer(GL_ARRAY_BUFFER, hVBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

inline void RenderOGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	SwapBuffers(hDC);
}*/