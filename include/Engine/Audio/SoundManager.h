#pragma once

namespace GameEngine {
	class SoundManager {

	public:

		static SoundManager& GetInstance();

		bool Init();

		void PlaySound(const char* FilePath, bool Loop);

		void StopAll();

		void Release();

	private:
		SoundManager(){}
	};
}

