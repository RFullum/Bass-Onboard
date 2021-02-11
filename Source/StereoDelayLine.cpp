/*
  ==============================================================================

    StereoDelayLine.cpp
    Created: 10 Feb 2021 4:50:38pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "StereoDelayLine.h"

//========================Public==============================

StereoDelayLine::StereoDelayLine() : bufferLSizeSamples(0), bufferRSizeSamples(0),
                                     writeHeadPosLeft(0), writeHeadPosRight(0),
                                     readHeadPosLeft(0.0f), readHeadPosRight(0.0f),
                                     delayTimeSamplesLeft(0.0f), delayTimeSamplesRight(0.0f),
                                     feedbackAmt(0.0f), delayOutputLeft(0.0f), delayOutputRight(0.0f)
{}

StereoDelayLine::~StereoDelayLine()
{
    delete delayBufferLeft;
    delete delayBufferRight;
}


/// Sets feedbackAmt and ensures it's between 0.0 and 1.0
void StereoDelayLine::setFeedbackAmt(float fdbk)
{
    feedbackAmt = fdbk;
    if (feedbackAmt < 0.0f)
        feedbackAmt = 0.0f;
    if (feedbackAmt > 1.0f)
        feedbackAmt = 1.0f;
}

/// Sets bufferSizeSamples, creates delayBuffer that length, and initializes values to 0.0f
void StereoDelayLine::setBufferSize(int size)
{
    bufferLSizeSamples = size;
    bufferRSizeSamples = size;
    
    delayBufferLeft  = new float[bufferLSizeSamples];
    delayBufferRight = new float[bufferRSizeSamples];
    
    for (int i = 0; i < bufferLSizeSamples; i++)
        delayBufferLeft[i] = 0.0f;
    
    for (int i = 0; i < bufferRSizeSamples; i++)
        delayBufferRight[i] = 0.0f;
}


void StereoDelayLine::setDelayTime(float setDelayL, float setDelayR)
{
    delayTimeSamplesLeft  = setDelayL;
    delayTimeSamplesRight = setDelayR;
    
    readHeadPosLeft  = writeHeadPosLeft  - delayTimeSamplesLeft;
    readHeadPosRight = writeHeadPosRight - delayTimeSamplesRight;
    
    while (readHeadPosLeft < 0)
        readHeadPosLeft += bufferLSizeSamples;
    
    while (readHeadPosRight < 0)
        readHeadPosRight += bufferRSizeSamples;
}

void StereoDelayLine::processDelay(float sampleInLeft, float sampleInRight)
{
    delayOutputLeft  = readBufferLeft();
    delayOutputRight = readBufferRight();
    
    writeToBuffer( sampleInLeft + (delayOutputLeft * feedbackAmt), sampleInRight + (delayOutputRight * feedbackAmt) );
}

float StereoDelayLine::getDelayOutputLeft()
{
    return delayOutputLeft;
}

float StereoDelayLine::getDelayOutputRight()
{
    return delayOutputRight;
}

//=========================Private==========================



/// Interpolation algorithm
float StereoDelayLine::lagrangeInterpolation(float readHeadPos, int bufferSizeSamples, float* delayBuffer)
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
void StereoDelayLine::writeToBuffer(float sampleInL, float sampleInR)
{
    delayBufferLeft[writeHeadPosLeft]   = sampleInL;
    delayBufferRight[writeHeadPosRight] = sampleInR;
    
    writeHeadPosLeft++;
    writeHeadPosRight++;
    
    writeHeadPosLeft  %= bufferLSizeSamples;
    writeHeadPosRight %= bufferRSizeSamples;
}


/**
Reads from the delayBuffer at the readHeadPos and increments readheadPos
(wrapped between 0 and bufferSizeSamples)
*/
float StereoDelayLine::readBufferLeft()
{
    float leftOutput = lagrangeInterpolation(readHeadPosLeft, bufferLSizeSamples, delayBufferLeft);
    
    readHeadPosLeft++;
    
    if (readHeadPosLeft > bufferLSizeSamples)
        readHeadPosLeft -= bufferLSizeSamples;
    
    return leftOutput;
}

/**
Reads from the delayBuffer at the readHeadPos and increments readheadPos
(wrapped between 0 and bufferSizeSamples)
*/
float StereoDelayLine::readBufferRight()
{
    float rightOutput = lagrangeInterpolation(readHeadPosRight, bufferRSizeSamples, delayBufferRight);
    
    readHeadPosRight++;
    
    if (readHeadPosRight > bufferRSizeSamples)
        readHeadPosRight -= bufferRSizeSamples;
    
    return rightOutput;
}
