#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

namespace GameEngine {
	class SoundManager {

	public:

		static SoundManager& GetInstance();

		void Init();

		void PlaySound(const char* FilePath, bool Loop);

		void StopAll();

		void Release();

	private:
		SoundManager(){}
	};
}

#endif // !SOUND_MANAGER_H
