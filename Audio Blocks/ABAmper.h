//
//  ABAmper.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/28/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

// REBUFFERED

#ifndef __SoniScan_2_0__ABAmper__
#define __SoniScan_2_0__ABAmper__

#include <iostream>
#include "AudioBlockBase.h"

class ABAmper : public AudioBlockBase
{
    float amplitudeFactor;
    
public:
    ABAmper* GetAudioBlock();
    
    float GetAmplitude();
    void SetAmplitude(float);

    void Process();

    ABAmper();
    ABAmper(float);
};

#endif /* defined(__SoniScan_2_0__ABAmper__) */
