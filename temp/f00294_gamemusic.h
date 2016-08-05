// f00294_gamemusic.h
//

#include "f00294_gamemusic.e"
#define LZZ_INLINE inline
GameMusic::GameMusic ()
                            {
			
		}
void GameMusic::init (string path)
                                       {
			if ( !sound.openFromFile(path) ) {
				cout << "error loading music";
				return;
			}
			
		}
void GameMusic::setLoop (bool val)
                                       {
			sound.setLoop(val);
		}
void GameMusic::stop ()
                            {
			sound.stop();
		}
void GameMusic::setVolume (float _volume)
                                                   {
			volume = _volume;
			int intVol = _volume*100.0f;
			sound.setVolume(intVol);
		}
void GameMusic::play (float _volume)
                {
			setVolume(_volume);
			sound.play();
		}
#undef LZZ_INLINE
 
