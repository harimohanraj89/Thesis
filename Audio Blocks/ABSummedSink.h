//
//  ABSummedSink.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/18/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#ifndef __SoniScan_2_0__ABSummedSink__
#define __SoniScan_2_0__ABSummedSink__

#include <iostream>
#include "AudioBlockBase.h"

// This class successively adds input buffers it receives into a member variable.
// It contains functions to return the current value of the member variable, and
// to clear the member variable back to zero.

// This class is intended to work together with a callback system such as portaudio
// to serve as a final summing engine for multiple tracks or channels. Hence, the
// ClearSink() function must be called manually every callback to flush the buffer
// before performing the next buffer iteration.

// NOT REQUIRED FOR NOW!!!

class ABSummedSink : public AudioBlockBase
{
    std::vector<Buffer> sinkBuffers;
    int sinkBufferSize;
    
public:
    std::vector<Buffer> GetSink();
    Buffer GetSink(int);
    void ClearSink();
    
    void AddInputBuffer();
    void RemoveInputBuffer();
    
    void FlowSignal(std::vector<Buffer>&);
    
    ABSummedSink();
    ABSummedSink(int);
    ABSummedSink(int,int);
};


#endif /* defined(__SoniScan_2_0__ABSummedSink__) */
