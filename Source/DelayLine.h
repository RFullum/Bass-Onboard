/*
  ==============================================================================

    DelayLine.h
    Created: 2 Mar 2020 7:40:12pm
    Author:  B150987

  ==============================================================================
*/

#pragma once

#import <cmath>

class DelayLine
{
public:
    /// Constructor
    DelayLine();
    
    /// Destructor! Clean up, nay, destroy that buffer!
    ~DelayLine();
    
    // Setters
    /**
     Sets bufferSizeSamples in samples.
     Creates the delayBuffer (bufferSizeSamples) long.
     Initializes values to 0.0f
     */
    void setBufferSize(int size);
    
    /**
     sets delay time in samples and sets readHeadPos delayTimeSamples behind writeHeadPos,
     wrapped 0 <= X < bufferSizeSamples
     */
    void setDelayTime(float setDelay);
    
    /**
     sets feedbackAmt and ensures between 0.0 and 1.0
     */
    void setFeedbackAmt(float fdbk);
    
    /**
     lagrangeInterpolation method
     */
    float lagrangeInterpolation();
    
    /**
     Gets sampleIn from DSP signal, writes it to the current writeHeadPos, and increments writeHeadPos
     (wrapping between 0 and bufferSizeSamples)
     */
    void writeToBuffer(float sampleIn);
    
    /**
     Reads from the delayBuffer at the readHeadPos and increments readheadPos
     (wrapped between 0 and bufferSizeSamples)
     */
    float readBuffer();
    
    /**
     Outputs readBuffer( ) value.
     Writes value of input signal sample to buffer writeToBuffer(sampleIn)
     returns delayOutput
     */
    float processDelay(float sampleIn);
    
private:
    float* delayBuffer;         // Buffer DelayLine writes to
    int bufferSizeSamples;      // Buffer size in samples
    
    // These must be wrapped between 0 and bufferSizeSamples
    int writeHeadPos;           // Position of delay's write head, initalized at zero
    float readHeadPos;          // Position of delay's read head, initialized at zero
    
    float delayTimeSamples;     // Length of delay in samples
    
    float feedbackAmt;          // Sets feedback amout 0 <= X <= 1
};
