# SoundChopper
A little C++ tool that chops up wav files. Originally inspired by Tu2 by BramBros [SoftPedia Link](http://www.softpedia.com/get/Multimedia/Audio/Other-AUDIO-Tools/Tu2.shtml)

Uses [Libsndfile](http://brewformulas.org/Libsndfile)
```bash
  brew install libsndfile
```

Harp loop sample credit to BaltesA on [Looperman.com](http://www.looperman.com/loops/detail/101133/blues-harp-loop-groove-120pbm-by-baltesa-free-120bpm-acoustic-harmonica-loop)

# Running
This code is pretty old but still works. Your input file should be a 16 bit 44.1k mono wav file. In Xcode run the **SndChop** scheme to chop up a drum loop. Run the **BluesLoop SndChop** to chop up the Harp Loop. It will write the results to **output.wav** in the location of the executable. 
