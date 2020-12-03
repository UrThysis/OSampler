/*
  ==============================================================================

    OSamplerSound.h
    Guarda un Objeto "SamplerSound" de un archivo de audio
    Created: 15 Jun 2020 1:35:15am
    Author:  UrThysis

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class OSamplerSound : public SamplerSound {
private:
    double sampleRateFuente;
    long long  longitud;
    int notaMidiRoot;

public:
    friend class OSamplerVoice;
    OSamplerSound(const String& nombre, AudioFormatReader& fuente, const BigInteger& notasMidi, int notaMidiPitchNormal, double tiempoAtaqueSeg, double tiempoReleaseSeg, double maxLongitudSampleSeg) : SamplerSound(nombre, fuente, notasMidi, notaMidiPitchNormal, tiempoAtaqueSeg, tiempoReleaseSeg, maxLongitudSampleSeg),
        sampleRateFuente(fuente.sampleRate), longitud(fuente.lengthInSamples), notaMidiRoot(notaMidiPitchNormal) {}


};