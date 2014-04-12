#include <iostream>
#include "canvas.h"
#include <lumiererenderer\rendercontext.h>
#include "list.h"
#include "pinhole.h"
#include "pathtracer.h"
#include <lumiererenderer\imagesensor.h>
#include "ccd.h"
#include <lumiererenderer\spectrum.h>
#include "triangle.h"
#include "diffuse.h"
#include "blackbody.h"

using namespace LumiereRenderer;

//RGBA* image;
int canvasWidth = 512;
int canvasHeight = 512;

void Render(RenderContext* rc, Camera* camera)
{
    for (int j = canvasHeight-1; j >= 0; j--)
    {
        for (int i = 0; i < canvasWidth; i++)
        {                                
            rc->clear();
            /*image[j*canvasWidth+i] = */camera->trace(i, j, *rc);
            
            //rc->pop();
            //rc->push();
        }		

		UpdatePixels(camera->getImageSensor()->getData());
        RefreshCanvas();

    }
}

const Point3 position[] =
{
    Point3(-0.24f, 1.98f, 0.16f),  
    Point3( 0.23f, 1.98f, 0.16f),
    Point3( 0.23f, 1.98f,-0.22f),
    Point3(-0.24f, 1.98f,-0.22f),
    Point3(-1.01f, 0.0f,  0.99f),
    Point3( 1.00f, 0.0f,  0.99f),
    Point3( 1.00f, 0.0f, -1.04f),
    Point3(-0.99f, 0.0f, -1.04f),
    Point3( 1.00f, 0.00f,-1.04f),
    Point3( 1.00f, 0.00f, 0.99f),
    Point3( 1.00f, 1.99f, 0.99f),
    Point3( 1.00f, 1.99f,-1.04f),
    Point3(-0.99f, 0.00f,-1.04f), 
    Point3( 1.00f, 0.00f,-1.04f),
    Point3( 1.00f, 1.99f,-1.04f),
    Point3(-1.02f, 1.99f,-1.04f),
    Point3(-1.01f, 0.00f, 0.99f),
    Point3(-0.99f, 0.00f,-1.04f),
    Point3(-1.02f, 1.99f,-1.04f),
    Point3(-1.02f, 1.99f, 0.99f),
    Point3(-1.02f, 1.99f, 0.99f), 
    Point3(-1.02f, 1.99f,-1.04f),
    Point3( 1.00f, 1.99f,-1.04f),
    Point3( 1.00f, 1.99f, 0.99f)
};

const Vector3 normal[] =
{
    Vector3( 0.0f, -1.0f, 0.0f),
    Vector3( 0.0f, -1.0f, 0.0f),
    Vector3( 0.0f, -1.0f, 0.0f),
    Vector3( 0.0f, -1.0f, 0.0f),
    Vector3( 0.0f, 1.0f, 0.0f),
    Vector3( 0.0f, 1.0f, 0.0f),
    Vector3( 0.0f, 1.0f, 0.0f),
    Vector3( 0.0f, 1.0f, 0.0f),
    Vector3( -1.0f, 0.0f, 0.0f),
    Vector3( -1.0f, 0.0f, 0.0f),
    Vector3( -1.0f, 0.0f, 0.0f),
    Vector3( -1.0f, 0.0f, 0.0f),
    Vector3( 0.0f, 0.0f, 1.0f),
    Vector3( 0.0f, 0.0f, 1.0f),
    Vector3( 0.0f, 0.0f, 1.0f),
    Vector3( 0.0f, 0.0f, 1.0f),
    Vector3( 1.0f, 0.0f, 0.0f),
    Vector3( 1.0f, 0.0f, 0.0f),
    Vector3( 1.0f, 0.0f, 0.0f),
    Vector3( 1.0f, 0.0f, 0.0f),
    Vector3( 0.0f, -1.0f, 0.0f),
    Vector3( 0.0f, -1.0f, 0.0f),
    Vector3( 0.0f, -1.0f, 0.0f),
    Vector3( 0.0f, -1.0f, 0.0f)
};

Triangle* CreateTriangle(int i0, int i1, int i2, Shader* shader)
{
    Vertex v[4];
    v[0].position = position[i0];
    v[1].position = position[i1];
    v[2].position = position[i2];
    
    v[0].normal = normal[i0];
    v[1].normal = normal[i1];
    v[2].normal = normal[i2];

    Triangle* triangle = new Triangle(v[0],v[1],v[2]); 
    triangle->SetShader(shader);
    return triangle;
}

void main()
{
    //Setup canvas
    CreateCanvas(canvasWidth, canvasHeight);

    // Setup shaders
    float white[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    float red[] = {0.1012f, 0.0515f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.8325f, 1.0149f, 1.0149f, 1.0149f};
    float green[] = {0.0000f, 0.0000f, 0.0273f, 0.7937f, 1.0000f, 0.9418f, 0.1719f, 0.0000f, 0.0000f, 0.0025f};
    float blue[] = {1.0000f, 1.0000f, 0.8916f, 0.3323f, 0.0000f, 0.0000f, 0.0003f, 0.0369f, 0.0483f, 0.0496f};
    float wavelengths[] = {380, 418, 456, 494, 532, 570, 608, 646, 684, 720};

    Spectrum redSpectrum = Spectrum(wavelengths, red, 10);
    Spectrum greenSpectrum = Spectrum(wavelengths, green, 10);
    Spectrum blueSpectrum = Spectrum(wavelengths, blue, 10);
    Spectrum whiteSpectrum = Spectrum(wavelengths, white, 10);

    Diffuse redShader, greenShader, blueShader, whiteShader;
    redShader["Reflectance"] = redSpectrum["outColor"];
    greenShader["Reflectance"] = greenSpectrum["outColor"];    
    blueShader["Reflectance"] = blueSpectrum["outColor"];     
    whiteShader["Reflectance"] = whiteSpectrum["outColor"];

    BlackBody blackbodyShader;
    //blackbodyShader["Temperature"] = 1200;
    //blackbodyShader["Temperature"].setDefaultValue(1200);

    //Setup scene
    Scene* scene = new List();
     
    // Light 
    scene->addShape(CreateTriangle(0, 1, 2, &blackbodyShader));
    scene->addShape(CreateTriangle(0, 2, 3, &blackbodyShader));
    
    // Floor
    scene->addShape(CreateTriangle(4, 5, 6, &whiteShader));
    scene->addShape(CreateTriangle(4, 6, 7, &whiteShader));

    // Rightwall 
    scene->addShape(CreateTriangle(8, 9, 10, &greenShader));
    scene->addShape(CreateTriangle(8, 10, 11, &greenShader));

    // Backwall
    scene->addShape(CreateTriangle(12, 13, 14, &whiteShader));
    scene->addShape(CreateTriangle(12, 14, 15, &whiteShader));

    // Leftwall 
    scene->addShape(CreateTriangle(16, 17, 18, &redShader));
    scene->addShape(CreateTriangle(16, 18, 19, &redShader));

    // Ceiling
    scene->addShape(CreateTriangle(20, 21, 22, &whiteShader));
    scene->addShape(CreateTriangle(20, 22, 23, &whiteShader));

    // Setup CCD chip
    float ccdWavelengths[] = {390.f, 400.f, 410.f, 420.f, 430.f, 440.f, 450.f, 460.f, 470.f, 480.f, 490.f, 500.f, 510.f, 520.f, 530.f, 540.f, 550.f, 560.f, 570.f, 580.f, 590.f, 600.f, 610.f, 620.f, 630.f, 640.f, 650.f, 660.f, 670.f, 680.f, 690.f, 700.f, 710.f, 720.f, 730.f, 740.f, 750.f};
    float ccdGreen[] = {0.045f, 0.047f, 0.049f, 0.051f, 0.06f, 0.072f, 0.09f, 0.115f, 0.172f, 0.2f, 0.23f, 0.3f, 0.379f, 0.43f, 0.462f, 0.442f, 0.4f, 0.34f, 0.27f, 0.218f, 0.18f, 0.13f, 0.09f, 0.07f, 0.065f, 0.062f, 0.06f, 0.058f, 0.062f, 0.07f, 0.081f, 0.098f, 0.102f, 0.102f, 0.105f, 0.114f, 0.12f};
    float ccdBlue[] = {0.17f, 0.25f, 0.31f, 0.355f, 0.38f, 0.412f, 0.422f, 0.412f, 0.38f, 0.33f, 0.26f, 0.19f, 0.135f, 0.1f, 0.09f, 0.08f, 0.072f, 0.06f, 0.052f, 0.048f, 0.05f, 0.04f, 0.038f, 0.03f, 0.029f, 0.03f, 0.035f, 0.038f, 0.039f, 0.04f, 0.045f, 0.051f, 0.055f, 0.051f, 0.054f, 0.06f, 0.062f};
    float ccdRed[] = {0.06f, 0.04f, 0.03f, 0.022f, 0.018f, 0.012f, 0.01f, 0.011f, 0.019f, 0.02f, 0.022f, 0.03f, 0.045f, 0.052f, 0.07f, 0.07f, 0.068f, 0.052f, 0.079f, 0.18f, 0.325f, 0.352f, 0.332f, 0.305f, 0.297f, 0.282f, 0.26f, 0.222f, 0.208f, 0.195f, 0.19f, 0.19f, 0.189f, 0.188f, 0.191f, 0.199f, 0.198f};
    
    Spectrum ccdRedSpectrum = Spectrum(ccdWavelengths, ccdRed, 37);
    Spectrum ccdGreenSpectrum = Spectrum(ccdWavelengths, ccdGreen, 37);
    Spectrum ccdBlueSpectrum = Spectrum(ccdWavelengths, ccdBlue, 37);
    
    CCD ccd = CCD(0.0512f, 0.0512f, canvasWidth, canvasHeight, 1.0);  //TODO: Changes values


	ccd["Red"] = ccdRedSpectrum["outColor"];
	ccd["Green"] = ccdGreenSpectrum["outColor"];
	ccd["Blue"] = ccdBlueSpectrum["outColor"];

    // Setup camera
    Camera* camera = new Pinhole(0.06f, 0.0001f, 0.3f);	
    camera->setImageSensor(&ccd);     
    camera->setPosition(Point3(0.0f, 1.0f, 3.1f));


    // Setup integrator
    Integrator* integrator = new PathTracer(4);

    // Setup render context
    RenderContext* rc = new RenderContext(scene, camera, integrator);   
        
    
    // Enter the main rendering loop   
    //image = new RGBA[canvasWidth*canvasHeight];

    MSG  msg;
    while(true)
    {
        if ( PeekMessage(&msg,NULL,0,0,0) )
        {
            if ( !GetMessage(&msg,NULL,0,0) ) break;				
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } 
        else
        {				
            Render(rc, camera);
            RefreshCanvas();
        }
    }

}