//
//  Buffer.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/6/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#ifndef __SoniScan_2_0__Buffer__
#define __SoniScan_2_0__Buffer__

#include <iostream>
#include "../Constants.h"

class Buffer
{
private:
    sample* bufferContents;
    int bufferSize;
    
public:
    // Functions to get values from buffer
    sample* Get();
    void Get(sample[],int);
    sample Get(int);
    int Size();
    
    // Functions to set values of buffer
    void Set(sample[],int);
    void Set(sample, int);
    
    // Utility functions for buffer
    void Clear();
    void Clear(int);
    void Copy(Buffer&);
    void Copy(Buffer&, int);
    
    void Add(Buffer&);
    void Add(Buffer&, int);
    void Add(Buffer&, float, int);
    
    void Subtract(Buffer&);
    void Multiply(Buffer&);
    void Multiply(float);
    void Reverse();
    void Invert();
    
    // Constructors and Destructors
    Buffer();
    Buffer(int);
    Buffer(const Buffer&);
    Buffer& operator=(Buffer);
    ~Buffer();
};

#endif /* defined(__SoniScan_2_0__Buffer__) */
