#pragma once
#include <windows.h>
#include <lumiererenderer\imagesensor.h>

void CreateCanvas( unsigned int width, unsigned int height );
void UpdatePixels(/*unsigned int left, unsigned int right, unsigned int bottom, unsigned int top,*/ LumiereRenderer::RGBA* pixels);
void RefreshCanvas();

