#include <Engine\Platform\Android\AndroidOpenGLES2Context.h>
#include <android_native_app_glue.h>
#include <SGL\System\Log.h>


AndroidOpenGLES2Context::AndroidOpenGLES2Context()
{

}

bool AndroidOpenGLES2Context::Init()
{
	
	Log::Output("Start Rendering Context Creation");
const EGLint attribs[] = {
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, //important
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_NONE
	};

	EGLint attribList[] =
	{
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
	};

	EGLint w, h, dummy, format;
	EGLint numConfigs;
	EGLConfig config;

	GLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(GLDisplay, 0, 0);

	/* Here, the application chooses the configuration it desires. In this
	 * sample, we have a very simplified selection process, where we pick
	 * the first EGLConfig that matches our criteria */
	eglChooseConfig(GLDisplay, attribs, &config, 1, &numConfigs);

	/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
	 * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
	 * As soon as we picked a EGLConfig, we can safely reconfigure the
	 * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
	eglGetConfigAttrib(GLDisplay, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(DroidVars.App->window, 0, 0, format);

	Surface = eglCreateWindowSurface(GLDisplay, config, DroidVars.App->window, NULL);

	Context = eglCreateContext(GLDisplay, config, NULL, attribList);

	if (eglMakeCurrent(GLDisplay, Surface, Surface, Context) == EGL_FALSE) {
		Log::Output("Unable to eglMakeCurrent");
		return false;
	}

	// Grab the width and height of the surface
	eglQuerySurface(GLDisplay, Surface, EGL_WIDTH, &w);
	eglQuerySurface(GLDisplay, Surface, EGL_HEIGHT, &h);

	/**engine->width = w;
	engine->height = h;*/

	// Initialize GL state.
	glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, w, h);

	Log::Output("Context Created");
	Initialized = true;
	return Initialized;
}

void AndroidOpenGLES2Context::Clear()
{
	if(Initialized)
	{
		glClearColor(0.3, 0.5, 0.25, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void AndroidOpenGLES2Context::Display()
{
	if(Initialized)
	{
		eglSwapBuffers(GLDisplay, Surface);
	}

}

void AndroidOpenGLES2Context::Release()
{
	if( GLDisplay )
    {
            if(Context != EGL_NO_CONTEXT)
                eglDestroyContext(GLDisplay, Context);

            if(Surface != EGL_NO_SURFACE)
                eglDestroySurface(GLDisplay, Surface);

            if(GLDisplay != EGL_NO_DISPLAY)
            {
                eglMakeCurrent(GLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
                eglTerminate(GLDisplay);
            }
            GLDisplay    = EGL_NO_DISPLAY;
            Surface    = EGL_NO_SURFACE;
            Context    = EGL_NO_CONTEXT;
            /*Width      = 0;
            Height     = 0;*/
			Initialized=false;
    }
}