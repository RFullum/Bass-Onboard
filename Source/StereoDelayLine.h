/*
  ==============================================================================

    StereoDelayLine.h
    Created: 10 Feb 2021 4:50:38pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#import <cmath>

class StereoDelayLine
{
public:
    /// Constructor
    StereoDelayLine();
    
    /// Destructor
    ~StereoDelayLine();
    
    /// Sets feedback amount and ensures it's between 0.0 and 1.0
    void setFeedbackAmt(float fdbk);
    
    /// Sets bufferSizeSamples, creates delayBuffer that length, and initializes values to 0.0f
    void setBufferSize(int size);
    
    /**
    sets delay time in samples and sets readHeadPos delayTimeSamples behind writeHeadPos,
    wrapped 0 <= X < bufferSizeSamples
    */
    void setDelayTime(float setDelayL, float setDelayR);
    
    /**
    Outputs readBuffer( ) value.
    Writes value of input signal sample to buffer writeToBuffer(sampleIn)
    returns delayOutput
    */
    void processDelay(float sampleInLeft, float sampleInRight);
    
    float getDelayOutputLeft();
    float getDelayOutputRight();
    
private:
    /// Interpolation algorithm
    float lagrangeInterpolation(float readHeadPos, int bufferSizeSamples, float* delayBuffer);
    
    /**
    Gets sampleIn from DSP signal, writes it to the current writeHeadPos, and increments writeHeadPos
    (wrapping between 0 and bufferSizeSamples)
    */
    void writeToBuffer(float sampleInL, float sampleInR);
    
    /**
    Reads from the delayBuffer at the readHeadPos and increments readheadPos
    (wrapped between 0 and bufferSizeSamples)
    */
    float readBufferLeft();
    
    /**
    Reads from the delayBuffer at the readHeadPos and increments readheadPos
    (wrapped between 0 and bufferSizeSamples)
    */
    float readBufferRight();
    
    // Member Variables
    
    // Delay Buffers
    float* delayBufferLeft;
    float* delayBufferRight;
    
    int bufferLSizeSamples;
    int bufferRSizeSamples;
    
    int writeHeadPosLeft;
    int writeHeadPosRight;
    float readHeadPosLeft;
    float readHeadPosRight;
    
    float delayTimeSamplesLeft;
    float delayTimeSamplesRight;
    float feedbackAmt;
    
    float delayOutputLeft;
    float delayOutputRight;
};
