//
//  SineGen.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/10/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

// REBUFFERED

#ifndef __SoniScan_2_0__ABSineGen__
#define __SoniScan_2_0__ABSineGen__

#include <iostream>
#include "AudioBlockBase.h"

class ABSineGen : public AudioBlockBase
{
    int currentIndex;
    int frequency;
    float amplitude;
    
    float wavetable[SAMPLE_RATE];
    
    int bMuted;
    
    
    
public:
    void Process();
    
    void GenWavetable();
    
    ABSineGen* GetAudioBlock();
    
    int GetFrequency();
    void SetFrequency(int);
    
    float GetAmplitude();
    void SetAmplitude(float);
    
    
    void Mute();
    void Unmute();
    void ToggleMute();
    
    ABSineGen();
    ABSineGen(int);
    ABSineGen(int,int);
    
};



#endif /* defined(__SoniScan_2_0__SineGen__) */
