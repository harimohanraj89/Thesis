//
//  ABTrigger.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/17/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

// NOT REQUIRED FOR NOW!!!

#ifndef __SoniScan_2_0__ABTrigger__
#define __SoniScan_2_0__ABTrigger__

#include <iostream>
#include "AudioBlockBase.h"

// Class ABTrigger acts as a dummy block that is connected to several other AudioBlocks to
// provide a convenient way to trigger FlowSignal() calls of several blocks simultaneously

// It is advised to connect trigger blocks to blocks that do not require an input buffer, as
// the trigger block houses an empty OutputBuffers vector.


class ABTrigger : public AudioBlockBase
{
public:
    void Process(std::vector<Buffer> &);
    
    ABTrigger();
    ABTrigger(int);
};


#endif /* defined(__SoniScan_2_0__ABTrigger__) */

