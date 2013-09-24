//
//  AudioBlockBase.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/5/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

// REBUFFERED

#ifndef __SoniScan_2_0__AudioBlockBase__
#define __SoniScan_2_0__AudioBlockBase__

#include <iostream>
#include <vector>
#include "../ParentHeader.h"

// Class that serves as parent to all audio blocks (signal generator blocks and effects blocks)
// Class handles basic input and output buffers, and provides a virtual function for children to program
// the working of the block (ie, to specify the processing from input to output buffers)

class AudioBlockBase
{
protected:
    // Input and output buffers
    sample* inputBuffer;
    sample* internalBuffer;
    sample* outputBuffer;
    sample* nextInputBuffer;
    std::vector<sample*> nextInputBuffers;
    
    // Iterators
    sample* currInputPtr;
    sample* currInternalPtr;
    sample* currOutputPtr;
    sample* currNextPtr;
    int counter;

    
    // "Connectors": Pointers to audio blocks that are connected to input and output of this block
    
    
public:
    // Function to return pointers
    sample* GetInputBuffer();
    virtual AudioBlockBase* GetAudioBlock();
    
    
    // Functions to set connections
    void SetNextBuffer(sample* argBuffer);
    void PushNextBuffer(sample* argBuffer);
    void PopNextBuffer();
    void ClearNextBuffers();
    
    
    // Audio Block Functionality
    virtual void BufferFlush();
    virtual void InternalCopy();
    virtual void Process();
    virtual void OutputCopy();
    
    
    //Constructors and Destructors
    AudioBlockBase();
    ~AudioBlockBase();
};

#endif /* defined(__SoniScan_2_0__AudioBlockBase__) */
