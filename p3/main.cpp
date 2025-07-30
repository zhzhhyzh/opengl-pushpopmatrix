#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"
#define MIN_BLADES 4
#define MAX_BLADES 7
int qno = 1;
float tx1 = 0;
float ty1 = 0;
float tx2 = 0;
float ty2 = 0;
float tSpeed = 0.1;
float r = 1, g = 1, b = 1;
float PI = 3.1415926;
float radius = 0.2;

float wangle = 0.0f;
float wspeed = 0.001f;
int direction = 1; // 1 = clockwise, -1 = anticlockwise
bool spinning = true;
int bladeCount = MIN_BLADES;


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_LEFT) {
			tx1 -= tSpeed;
			tx2 += tSpeed;
		}

		else if (wParam == VK_RIGHT) {
			tx1 += tSpeed;
			tx2 -= tSpeed;
		}

		else if (wParam == VK_DOWN) {
			ty1 -= tSpeed;
			ty2 += tSpeed;
		}
		else if (wParam == VK_UP) {
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
		// Changed to lowercase 'k', 'd', 'a', 's' for consistency with common usage
		// but kept uppercase in case you specifically intended that.
		// If you want case-insensitive, you'd convert to upper or lower first.
		else if (wParam == 'k' || wParam == 'K') { wspeed = 0; } // Toggle spinning
		else if (wParam == 'd' || wParam == 'D') { wspeed += 0.01f; } // Accelerate
		else if (wParam == 'a' || wParam == 'A') { wspeed -= 0.01f; if (wspeed < 0) wspeed = 0; } // Decelerate
		else if (wParam == 's' || wParam == 'S') {
		
		if (wspeed == 0.01f) {
			direction *= -1;
		}
		else {
			wspeed -= 0.01f;
			if (wspeed < 0) wspeed = 0;
		}
		} // Reverse
		else if (wParam == 'Z' || wParam == 'z') {
			if (bladeCount < MAX_BLADES) {
				bladeCount++;
			}
		}
		else if (wParam == 'X' || wParam == 'x') {
			if (bladeCount > MIN_BLADES) {
				bladeCount--;
			}
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

	glTranslatef(tx1, ty1, 0);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, 0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(tx2, ty2, 0);
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
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
void drawCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);
	for (int i = 0; i <= num_segments; i++) {
		float angle = 2 * PI * i / num_segments;
		glVertex2f(cx + cos(angle) * r, cy + sin(angle) * r);
	}
	glEnd();
}

void drawBlade() { // Original, unused. Keeping for reference if needed.
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0.06, -0.03);
	glVertex2f(0.5, -0.05);
	glVertex2f(0.5, 0.05);
	glVertex2f(0.06, 0.03);
	glEnd();
}

void drawAxis() { // Original, unused. Keeping for reference if needed.
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.01, -0.5);
	glVertex2f(0.01, -0.5);
	glVertex2f(0.01, 0.5);
	glVertex2f(-0.01, 0.5);
	glEnd();
}

void drawBlade2() { // Original blade shape, will be modified below for a new style.
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.5, 0);
	glVertex2f(0.5, 0.02);
	glVertex2f(0, 0.02);
	glVertex2f(0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0.5, 0);
	glVertex2f(0.5, -0.1);
	glVertex2f(0.1, -0.1);
	glVertex2f(0.05, 0);
	glEnd();

}
	
// NEW FUNCTION: Draws a stylized windmill blade
void drawStylizedBlade() {
	// Main part of the blade
	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.8f, 0.8f); // Lighter gray for main blade
	glVertex2f(0.05f, 0.0f);
	glVertex2f(0.4f, 0.1f);
	glVertex2f(0.4f, -0.1f);
	glEnd();

	// Darker tip for contrast
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.6f, 0.6f); // Darker gray for tip
	glVertex2f(0.4f, 0.1f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}


void p3Q2() {
	// Sunset/Sunrise Sky
	glClearColor(0.9f, 0.5f, 0.3f, 1.0f); // Warm orange
	glClear(GL_COLOR_BUFFER_BIT);

	// Sun (or Moon if you adjust colors)
	glColor3f(1.0f, 0.8f, 0.0f); // Bright yellow/orange sun
	drawCircle(-0.7f, 0.8f, 0.15f, 30); // Larger, more prominent sun

	// Ground - Multiple layers for depth
	glBegin(GL_QUADS);
	glColor3f(0.15f, 0.45f, 0.15f); // Darker green for foreground
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(1.0f, -0.5f);
	glVertex2f(-1.0f, -0.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.55f, 0.2f); // Slightly lighter green for mid-ground
	glVertex2f(-1.0f, -0.5f);
	glVertex2f(1.0f, -0.5f);
	glVertex2f(1.0f, -0.3f);
	glVertex2f(-1.0f, -0.3f);
	glEnd();

	// Stylized Clouds (using multiple circles with slight color variations)
	// Cloud 1
	glColor3f(0.95f, 0.95f, 0.95f); // Off-white
	drawCircle(0.6f, 0.7f, 0.1f, 25);
	glColor3f(0.9f, 0.9f, 0.9f); // Slightly darker
	drawCircle(0.7f, 0.75f, 0.09f, 25);
	glColor3f(0.85f, 0.85f, 0.85f); // Even darker
	drawCircle(0.5f, 0.73f, 0.08f, 25);

	// Cloud 2
	glColor3f(0.95f, 0.95f, 0.95f);
	drawCircle(-0.4f, 0.8f, 0.08f, 25);
	glColor3f(0.9f, 0.9f, 0.9f);
	drawCircle(-0.3f, 0.82f, 0.07f, 25);
	glColor3f(0.85f, 0.85f, 0.85f);
	drawCircle(-0.5f, 0.78f, 0.06f, 25);


	// --- WINDMILL TOWER ---
	glColor3f(0.4f, 0.3f, 0.2f); // Brownish color for the tower

	glBegin(GL_QUADS); // Base of the tower (more blocky)
	glVertex2f(-0.25, -0.7f);
	glVertex2f(0.25, -0.7f);
	glVertex2f(0.2f, 0.4f);
	glVertex2f(-0.2f, 0.4f);
	glEnd();

	// Adding some "planks" to the tower for texture
	glColor3f(0.3f, 0.25f, 0.15f); // Darker brown for lines
	glLineWidth(1.5f); // Make lines slightly thicker
	glBegin(GL_LINES);
	glVertex2f(-0.15f, -0.5f); glVertex2f(0.15f, -0.5f);
	glVertex2f(-0.17f, -0.3f); glVertex2f(0.17f, -0.3f);
	glVertex2f(-0.19f, -0.1f); glVertex2f(0.19f, -0.1f);
	glVertex2f(-0.21f, 0.1f); glVertex2f(0.21f, 0.1f);
	glVertex2f(-0.23f, 0.3f); glVertex2f(0.23f, 0.3f);
	glEnd();
	glLineWidth(1.0f); // Reset line width


	// --- WINDMILL HEAD + BLADES ---
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glRotatef(wangle, 0, 0, 1);

	if (bladeCount > 0) { // Avoid division by zero if bladeCount somehow becomes 0
		float angleIncrement = 360.0f / bladeCount;
		for (int i = 0; i < bladeCount; ++i) {
			glPushMatrix();
			glRotatef(angleIncrement * i, 0, 0, 1);
			drawStylizedBlade();
			glPopMatrix();
		}
	}
	glPopMatrix();

	// --- (center of windmill) ---
	glColor3f(0.15f, 0.15f, 0.15f); // Very dark gray for hub
	drawCircle(0.0f, 0.5f, 0.04f, 25); // Slightly larger hub

	if (spinning) {
		wangle += direction * wspeed;
		if (wangle >= 360) wangle -= 360;
		if (wangle < 0) wangle += 360;
	}
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
	case 3:
		p3Q2(); // This will now display the changed style
		break;
	}
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