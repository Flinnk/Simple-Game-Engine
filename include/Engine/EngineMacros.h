#pragma once

#define IMPLEMENT_GAME_MODULE(ApplicationClass) namespace GameEngine {\
															Application* GetApplicationInstance() {\
																return new ApplicationClass();\
															}\
												}\

