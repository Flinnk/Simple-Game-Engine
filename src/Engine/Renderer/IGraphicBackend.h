#ifndef IGRAPHIC_BACKEND_H
#define IGRAPHIC_BACKEND_H

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

#endif // !IGRAPHIC_BACKEND_H
