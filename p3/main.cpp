
#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qno = 1;
float tx1, ty1, tx2, ty2= 0;
float tSpeed = 0.1;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_LEFT ) {
			tx1 -= tSpeed;
			tx2 += tSpeed;
		}

		else if ( wParam == VK_RIGHT) {
			tx1 += tSpeed;
			tx2 -= tSpeed;
		}

		else if ( wParam == VK_DOWN) {
			ty1 -= tSpeed;
			ty2 += tSpeed;
		}
		else if (wParam == VK_UP ) {
			ty1 += tSpeed;
			ty2 -= tSpeed;
		}

		else if (wParam == VK_SPACE) {
			tx1 = 0;
			tx2 = 0;
			ty1 = 0;
			ty2 = 0;
		}

		else if (wParam == '1') {
			qno = 1;
		}

		else if (wParam == '2') {
			qno = 2;
		}
		else if (wParam == '3') {
			qno = 3;
		}

		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void p3Demo() {
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	glScalef(0.5, 0.5, 0.5);

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, 0);
	glVertex2f(0, 0.5);
	glVertex2f(0.5, 0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glPushMatrix();

	glTranslatef(0.5, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex2f(-0.5, 0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0);
	glEnd();
	glPopMatrix();




	glPushMatrix();
	glTranslatef(-0.5, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex2f(-0.5, 0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}


void p3Q1() {
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);






	glPushMatrix();

	glTranslatef(tx1,ty1, 0);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, 0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(tx2,ty2, 0);
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glVertex2f(-0.5, 0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0);
	glEnd();
	glPopMatrix();


	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}

void display()
{
	switch (qno) {
	case 1: 
		p3Demo();
		break;
	case 2:
		p3Q1();

		break;
	}
	//p3Q1();
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------