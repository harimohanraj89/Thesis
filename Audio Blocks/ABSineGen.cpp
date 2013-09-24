//
//  SineGen.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/10/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "ABSineGen.h"
#include "../Constants.h"
#include <math.h>

//==========================
// Internal functions
//==========================

void ABSineGen::Process()
{
        // Defining the Process() for the SineGen block.
        // The SineGen block ignores any input, and generates a sine wave of
        // specified frequency, and updates the current phase accordingly
    
    currOutputPtr = outputBuffer;

    for(int i=0; i<BUFFER_SIZE; i++)
    {
        *currOutputPtr = amplitude * wavetable[currentIndex];
        
        //std::cout << *currOutputPtr << "\n";
        
        currOutputPtr++;
        
        // Increment the current phase by argPhaseIncrement
        // taking into account the  2Pi phase wraparound
        
        currentIndex += frequency;
        
        while (currentIndex >= SAMPLE_RATE)
            currentIndex -= SAMPLE_RATE;
    }
}

void ABSineGen::GenWavetable()
{
    for (int i=0; i<SAMPLE_RATE; i++)
    {
        wavetable[i] = sin(2*PI*i/SAMPLE_RATE);
    }
}


//==========================
// Getters and Setters
//==========================

ABSineGen* ABSineGen::GetAudioBlock()
{
    return this;
}

int ABSineGen::GetFrequency()
{
    return frequency;
}

void ABSineGen::SetFrequency(int argFrequency)
{
    // Set frequency to argFrequency
    frequency = argFrequency;
}


float ABSineGen::GetAmplitude()
{
    return amplitude;
}

void ABSineGen::SetAmplitude(float argAmplitude)
{
    // Set amplitude to argAmplitude
    amplitude = argAmplitude;
}




//==========================
// Constructors
//==========================

ABSineGen::ABSineGen()
{
        // Default constructor
        // Sets frequency to 440
        //      current phase to 0
        // Sets valid input and output conditions
    
    frequency = 440;
    currentIndex = 0;
    amplitude = 1;
    bMuted = 0;
    
    GenWavetable();
}

ABSineGen::ABSineGen(int argFrequency)
{
    frequency = argFrequency;
    currentIndex = 0;
    amplitude = 1;
    bMuted = 0;
    
    GenWavetable();
}

ABSineGen::ABSineGen(int argFrequency, int bufferSize)
{
    frequency = argFrequency;
    currentIndex = 0;
    amplitude = 1;
    bMuted = 0;
    
    GenWavetable();
}


