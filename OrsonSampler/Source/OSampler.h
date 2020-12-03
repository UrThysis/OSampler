    /*
  ==============================================================================

    OSampler.h
    Created: 11 Jun 2020 10:09:44pm
    Author:  UrThysis


  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "OSamplerSound.h"
#include "OSamplerVoice.h"


#define min(a,b) ((a)<(b)?(a):(b))

class OSampler : public Synthesiser {

    AudioFormatManager mFormatosAudio;//Maneja el reconocimiento de archivos de audio
    File mCarpetaSamples;//Permite seleccionar archivos hijo con .getChildFile("nombre");
    StringArray mTiposDeGolpe;//Permita iterar entre los samples dependiendo del tipo de golpe

    const int NRO_VOCES = 2;
    
  

    void agregarSonidoOSampler(String tipoDeGolpe, String nombre);//

    //Override el noteOn para agregar capas de velocity

    void noteOn(int midiChannel, int midiNoteNumber, float velocity) override;

    //================================================


    void cargarSamples();//carga los samples al sampler

    typedef enum Sonidos { AGUDO = 0, GRAVE } Sonidos_t;
    

    int roundRobin;
    int sampleSelector;
    int velocityInt;

    SynthesiserSound* sonido = nullptr;
    OSamplerVoice* voz = nullptr;
public:
    int x; 
    void setup();// Asignar las notas midi a cada sample



};
