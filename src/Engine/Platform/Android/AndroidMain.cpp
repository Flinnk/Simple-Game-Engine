#include <jni.h>
#include <errno.h>
#include <math.h>
#include <dlfcn.h>

#include <android_native_app_glue.h>
#include <Engine\Core\Engine.h>

void android_main(struct android_app* state) 
{
	GameEngine::Engine::GetInstance().Run();
}
