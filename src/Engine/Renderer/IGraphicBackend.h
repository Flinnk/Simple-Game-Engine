#pragma once 

namespace GameEngine 
{

	class GraphicBackend
	{
	public:
		virtual ~GraphicBackend() {}
		virtual bool Init() = 0;
		virtual void Clear() = 0;
		virtual void Resize(int Width, int Height) = 0;
		virtual void Display() = 0;
		virtual void Release() = 0;
	};
}

