#ifndef ANDROID_OPENGLES2_CONTEXT_H
#define ANDROID_OPENGLES2_CONTEXT_H

#include <Engine\Renderer\IGraphicBackend.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

class AndroidOpenGLES2Context : public GraphicBackend
{
public:
	AndroidOpenGLES2Context();
	bool Init() override;
	void Clear() override;
	void Display() override;
	void Release() override;
private:
	EGLDisplay GLDisplay;
	EGLSurface Surface;
	EGLContext Context;
	bool Initialized = false;
};

#endif // !ANDROID_OPENGLES2_CONTEXT_H
