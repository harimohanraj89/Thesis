//
//  Panner.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/11/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#ifndef __SoniScan_2_0__ABPanner__
#define __SoniScan_2_0__ABPanner__

#include <iostream>
#include "AudioBlockBase.h"

// Class that inputs a single audio stream, and outputs
// two audio streams that are stereo panned according to
// a pan angle, private member of Panner

// This class employs equal power circular panning


class ABStereoPanner : public AudioBlockBase
{
    float panAngle; // Takes values from -1 to 1  =>  -1 = hard left
                    //                                 1 = hard right
                    //                                 0 = center

    float lFactor;  // Amplitude multiplication factors for L and R channels
    float rFactor;  // based on value of panAngle. Updated every time panAngle
                    // is modified.
    
    // Extra R channel buffers
    sample* internalBufferR;
    sample* outputBufferR;
    sample* nextInputBufferR;
    
    // Extra R channel iterators
    sample* currInternalPtrR;
    sample* currOutputPtrR;
    sample* currNextPtrR;
    
    

public:
    // Getters and Setters
    ABStereoPanner* GetAudioBlock();
    float GetPanAngle();
    void SetPanAngle(float);
    void SetNextBufferR(sample*);
    
    // L and R amplitude factor calculation
    void FactorCalc();

    // Process() definition
    void InternalCopy();
    void Process();
    void OutputCopy();

    // Constructors
    ABStereoPanner();           // Default constructor
    ABStereoPanner(float);      // Constructor specifying: float-initial pan angle
    
    ~ABStereoPanner();
};


#endif /* defined(__SoniScan_2_0__Panner__) */
