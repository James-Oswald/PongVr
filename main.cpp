
#include<windows.h>
#include<wingdi.h>

#include <GL/glew.h> 

#include<string>
#include<vector>
#include<exception>

#include"PongIO.h"
#include"PongShaders.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName = "PongClass";
	if(!RegisterClassEx(&wc)){
		error("Failed to register window class");
		return 1;
	}
	HWND window = CreateWindowEx(0, wc.lpszClassName, "LearnOpenGL", WS_OVERLAPPEDWINDOW|WS_VISIBLE, 0, 0, 640, 480, 0, 0, hInstance, 0);
	if(!window){
		error("Failed to create window");
		return 1;
	}
	
	if(glewInit() != GLEW_OK){
		error("Failed to init GLEW");
		return 1;
	}
	try{
		ShaderProgram sp({GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}, {"default.vert", "default.frag"}, true);
	
		float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		
		glBindVertexArray(VAO);	//first bind the vao
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO); 
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);	//unbind everything
		glBindVertexArray(0); 	
		 
		HDC hDC = GetDC(window);	//Device context of the window
		MSG msg = {};
		while(GetMessage(&msg, NULL, 0, 0)){
			//RenderOGL();
			
			glEnable(GL_DEPTH_TEST);
			
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			sp.use();
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			SwapBuffers(hDC);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}catch(std::runtime_error e){
		error(e.what());
		return 1;
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	static HGLRC hRC; 	//Handle to rendering context
	static HDC hDC; 	//Handle to the device context
	
	switch(message){
		case WM_CREATE:{
			hDC = GetDC(hWnd);
			PIXELFORMATDESCRIPTOR pfd = {};
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cRedBits = 0;
			pfd.cRedShift = 0;
			pfd.cGreenBits = 0; 
			pfd.cGreenShift = 0; 
			pfd.cBlueBits = 0; 
			pfd.cBlueShift = 0; 
			pfd.cAlphaBits = 0; 
			pfd.cAlphaShift = 0; 
			pfd.cAccumBits = 0; 
			pfd.cAccumRedBits = 0; 
			pfd.cAccumGreenBits = 0;
			pfd.cAccumBlueBits = 0;
			pfd.cAccumAlphaBits = 0;
			pfd.cDepthBits = 16; 
			pfd.cStencilBits = 0;
			pfd.cAuxBuffers = 0;
			pfd.iLayerType = PFD_MAIN_PLANE;
			pfd.bReserved = 0;
			pfd.dwLayerMask = 0;
			pfd.dwVisibleMask = 0;
			pfd.dwDamageMask = 0;
			int nPixelFormat = ChoosePixelFormat(hDC, &pfd);	
			SetPixelFormat(hDC, nPixelFormat, &pfd);		
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);
			//MessageBoxA(hWnd, (char*)glGetString(GL_VERSION), "OGLV", MB_OK);
			//std::cout<<<<std::endl;
			return 0;
			break;
		}case WM_CLOSE:{
			wglMakeCurrent(hDC, NULL);
			wglDeleteContext(hRC);
			wglDeleteContext(hRC);
			PostQuitMessage(0);
			return 0; 
			break;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

