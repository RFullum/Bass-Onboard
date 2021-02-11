/*
  ==============================================================================

    DelayLine.cpp
    Created: 9 Feb 2021 4:26:33pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "DelayLine.h"

/// Constructor
DelayLine::DelayLine() : bufferSizeSamples(0), writeHeadPos(0),
                         readHeadPos(0.0f), delayTimeSamples(0.0f),
                         feedbackAmt(0.0f)
{}

/// Destructor! Clean up, nay, destroy that buffer!
DelayLine::~DelayLine()
{
    delete delayBuffer;
}

/**
Sets bufferSizeSamples in samples.
Creates the delayBuffer (bufferSizeSamples) long.
Initializes values to 0.0f
*/
void DelayLine::setBufferSize(int size)
{
    bufferSizeSamples = size;
    delayBuffer       = new float[bufferSizeSamples];
    
    for (int i=0; i<bufferSizeSamples; i++)
        delayBuffer[i] = 0.0f;
}

/**
sets delay time in samples and sets readHeadPos delayTimeSamples behind writeHeadPos,
wrapped 0 <= X < bufferSizeSamples
*/
void DelayLine::setDelayTime(float setDelay)
{
    delayTimeSamples = setDelay;
    readHeadPos      = writeHeadPos - delayTimeSamples;
    
    while (readHeadPos < 0)
        readHeadPos += bufferSizeSamples;
}
float DelayLine::getDelayTime()
{
    return delayTimeSamples;
}

/**
sets feedbackAmt and ensures between 0.0 and 1.0
*/
void DelayLine::setFeedbackAmt(float fdbk)
{
    feedbackAmt = fdbk;
    if (feedbackAmt < 0.0f)
        feedbackAmt = 0.0f;
    if (feedbackAmt > 1.0f)
        feedbackAmt = 1.0f;
}

/// Interpolation Method
float DelayLine::lagrangeInterpolation()
{
    float frac = readHeadPos - floor(readHeadPos);  // Position between indexes
    float sum  = 0.0f;                              // initialize sum to 0.0f
    
    for (int i = -2; i < 2; i++)
    {
        int index =  floor( readHeadPos + (i + 1) );   // index after readHeadPos in time
        
        index %= bufferSizeSamples;                    // wrap index to bufferSizeSamples
        
        if (index < 0.0f)
        {
            index += bufferSizeSamples;
        }
        
        float outVal      =  delayBuffer[index];               // value at [index] to outVal
        float denominator = 1.0f;                         // initialize denominator to 1.0f
        
        for (int j = -2; j < 2; j++)
        {
            if (j != i)
            {
                outVal      *= (frac - j);
                denominator *= (i - j);
            }
        }
        sum += outVal / denominator;
    }
    return sum;
}


/**
Gets sampleIn from DSP signal, writes it to the current writeHeadPos, and increments writeHeadPos
(wrapping between 0 and bufferSizeSamples)
*/
void DelayLine::writeToBuffer(float sampleIn)
{
    delayBuffer[writeHeadPos] = sampleIn;
    writeHeadPos++;
    writeHeadPos %= bufferSizeSamples;
}

/**
Reads from the delayBuffer at the readHeadPos and increments readheadPos
(wrapped between 0 and bufferSizeSamples)
*/
float DelayLine::readBuffer()
{
    float delayOutput = lagrangeInterpolation();
    
    readHeadPos++;
    
    if (readHeadPos > bufferSizeSamples)
        readHeadPos -= bufferSizeSamples;
    
    return delayOutput;
}

/**
Outputs readBuffer( ) value.
Writes value of input signal sample to buffer writeToBuffer(sampleIn)
returns delayOutput
*/
float DelayLine::processDelay(float sampleIn)
{
    float delayOutput = readBuffer();
    
    writeToBuffer( sampleIn + (delayOutput * feedbackAmt) );
    
    return delayOutput;
}
