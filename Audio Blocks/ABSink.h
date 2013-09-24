//
//  ABSink.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 2/20/13.
//  Copyright (c) 2013 Hariharan Mohanraj. All rights reserved.
//

// NOT REQUIRED FOR NOW!!!

#ifndef __SoniScan_2_0__ABSink__
#define __SoniScan_2_0__ABSink__

#include <iostream>
#include "AudioBlockBase.h"

#endif /* defined(__SoniScan_2_0__ABSink__) */

class ABSink : public AudioBlockBase
{

public:
    
    Buffer ReturnOutputBuffer();
    void Process(std::vector<Buffer>&);
    
    ABSink();
    ABSink(int);
    
    ~ABSink();
};