/*
  ==============================================================================

    OSamplerVoice.h
    Created: 15 Jun 2020 1:35:23am
    Author:  UrThysis

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "OSamplerSound.h"

class OSamplerVoice : public SamplerVoice {

    BigInteger notaMidi;
    
    //Override para casting del OSamplerSound a SamplerSound(JUCE)
    bool canPlaySound(SynthesiserSound* sampSound) override;
public:   
    void configurarNotaMidi(int nota);
    //==============REVISAR SI NECESITA INTERACTUAR CON NOTE ON EN SAMPLER MASTER =======TAL VEZ NO ES NECESARIO
    bool puedeTocarOSound(int nota) const;
    
    
   



};


