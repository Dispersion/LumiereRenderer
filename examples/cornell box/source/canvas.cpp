#include "canvas.h"
#include <gl\gl.h>
#include <gl\glu.h>

int gWidth;
int gHeight;
GLuint gTextureHandle;
HDC	 hdc;

void Resize( int width, int height )
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width/2, width/2, -height/2, height/2);
    glMatrixMode(GL_MODELVIEW);

    RefreshCanvas();
}

LRESULT CALLBACK process(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
    switch(uiMsg) {
        case WM_CLOSE:
                PostQuitMessage(0);
                return 0;

        case WM_SIZE:           
            Resize(LOWORD(lParam), HIWORD(lParam));
            return 0;
    }

    return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

void CreateCanvas( unsigned int width, unsigned int height )
{
    WNDCLASS	wc;			
    RECT		WindowRect;	
    HWND hwnd;

    HGLRC hrc;

    WindowRect.left=(long)0;
    WindowRect.right=(long)width+20;
    WindowRect.top=(long)0;
    WindowRect.bottom=(long)height+20;

    HINSTANCE instance	= GetModuleHandle(NULL);
    wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc		= (WNDPROC) process;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= instance;
    wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground	= NULL;
    wc.lpszMenuName		= NULL;
    wc.lpszClassName	= L"OpenGL";

    RegisterClass(&wc);

    AdjustWindowRectEx(&WindowRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

    if (!(hwnd=CreateWindowEx(	WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,							// Extended Style For The Window
                                L"OpenGL",							// Class Name
                                L"LumiereRenderer",								// Window Title
                                WS_OVERLAPPEDWINDOW |							// Defined Window Style
                                WS_CLIPSIBLINGS |					// Required Window Style
                                WS_CLIPCHILDREN,					// Required Window Style
                                0, 0,								// Window Position
                                WindowRect.right-WindowRect.left,	// Calculate Window Width
                                WindowRect.bottom-WindowRect.top,	// Calculate Window Height
                                NULL,								// No Parent Window
                                NULL,								// No Menu
                                instance,							// Instance
                                NULL)))								// Dont Pass Anything To WM_CREATE
    {
       // KillGLWindow();								// Reset The Display
       // MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
       // return FALSE;								// Return FALSE
    }


    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType   = PFD_TYPE_RGBA;
    pfd.cColorBits   = 32;
    pfd.cDepthBits   = 24;
    pfd.cStencilBits = 8;

    hdc = GetDC( hwnd );
    int pixelFormat = ChoosePixelFormat( hdc, &pfd );
    
    if(!SetPixelFormat(hdc,pixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
    {
        //KillGLWindow();								// Reset The Display
        //MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
       // return false;								// Return FALSE
    }

    hrc=wglCreateContext(hdc);
    wglMakeCurrent(hdc,hrc);

    ShowWindow(hwnd,SW_SHOW);						// Show The Window
    SetForegroundWindow(hwnd);						// Slightly Higher Priority
    SetFocus(hwnd);									// Sets Keyboard Focus To The Window
    //ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

    
    // Setup OpenGL texture
    gWidth = width;
    gHeight = height;

    glGenTextures(1, &gTextureHandle);
    glBindTexture( GL_TEXTURE_2D, gTextureHandle );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glEnable( GL_TEXTURE_2D );   

    glClearColor(0.3, 0.3, 0.3, 1.0);

    Resize( width+20, height+20 );
}

void UpdatePixels(/*unsigned int left, unsigned int right, unsigned int bottom, unsigned int top,*/ LumiereRenderer::RGBA* pixels)
{
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, gWidth, gHeight, 0, GL_RGBA, GL_FLOAT, pixels );
}

void RefreshCanvas()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   
    glBegin(GL_QUADS);    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( gWidth/2.f,  gHeight/2.f, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( gWidth/2.f, -gHeight/2.f, 0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-gWidth/2.f, -gHeight/2.f, 0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-gWidth/2.f,  gHeight/2.f, 0);
    glEnd();

    SwapBuffers(hdc);
}