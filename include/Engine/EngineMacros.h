#ifndef ENGINE_MACROS_H
#define ENGINE_MACROS_H

#define IMPLEMENT_GAME_MODULE(ApplicationClass) namespace GameEngine {\
															Application* GetApplicationInstance() {\
																return new ApplicationClass();\
															}\
												}\

#endif // !ENGINE_MACROS_H
