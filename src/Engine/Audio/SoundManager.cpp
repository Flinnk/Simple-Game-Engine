#include <Engine\Audio\SoundManager.h>
#include <irrKlang.h>

using namespace irrklang;
ISoundEngine *SoundEngine = nullptr;

namespace GameEngine {

	SoundManager& SoundManager::GetInstance()
	{
		static SoundManager Instance;

		return Instance;
	}

	bool SoundManager::Init()
	{
		SoundEngine = createIrrKlangDevice();
		return SoundEngine != nullptr;
	}

	void SoundManager::PlaySound(const char* FilePath, bool Loop)
	{
		if (SoundEngine)
			SoundEngine->play2D(FilePath, Loop);
	}

	void SoundManager::Release()
	{
		if (SoundEngine)
			SoundEngine->drop();

		SoundEngine = nullptr;
	}

	void SoundManager::StopAll()
	{
		SoundEngine->stopAllSounds();
	}


}