/*
  ==============================================================================

    OSampler.cpp
    Created: 11 Jun 2020 10:09:44pm
    Author:  UrThysis

  ==============================================================================
*/

#include "OSampler.h"


void OSampler::setup()
{
    mCarpetaSamples = File::getSpecialLocation(File::userDesktopDirectory).getChildFile("Samples");
    mTiposDeGolpe = { "Agudo","Grave" };

    x =  rand();

    // Añadir voces 

    for (int i = 0; i < NRO_VOCES;i++) {
        auto* voz = new OSamplerVoice();

        switch (i)
        {
        case AGUDO:
            voz->configurarNotaMidi(62);
            break;
        case GRAVE:
            voz->configurarNotaMidi(60);
            break;
        default:
            break;
        }
        addVoice(voz);
    }

    mFormatosAudio.registerBasicFormats();
    cargarSamples();   

    roundRobin = 1;
    
} 

void OSampler::cargarSamples()
{
    //Limpiar sonidos del sampler
    if (getNumSounds() != 0) {
        for (int i = 0; i < getNumSounds(); i++) {
            removeSound(i);
        }
    }

    // Cargar todos los sonidos   
    for (int i = 0; i < mTiposDeGolpe.size(); i++) {
        agregarSonidoOSampler(mTiposDeGolpe[i], mTiposDeGolpe[i] + "V1Rr1.wav");
        agregarSonidoOSampler(mTiposDeGolpe[i], mTiposDeGolpe[i] + "V1Rr2.wav");
        agregarSonidoOSampler(mTiposDeGolpe[i], mTiposDeGolpe[i] + "V1Rr3.wav");
        agregarSonidoOSampler(mTiposDeGolpe[i], mTiposDeGolpe[i] + "V2Rr1.wav");
        agregarSonidoOSampler(mTiposDeGolpe[i], mTiposDeGolpe[i] + "V2Rr2.wav");
        agregarSonidoOSampler(mTiposDeGolpe[i], mTiposDeGolpe[i] + "V2Rr3.wav");
        agregarSonidoOSampler(mTiposDeGolpe[i], mTiposDeGolpe[i] + "V3Rr1.wav");
        agregarSonidoOSampler(mTiposDeGolpe[i], mTiposDeGolpe[i] + "V3Rr2.wav");
        agregarSonidoOSampler(mTiposDeGolpe[i], mTiposDeGolpe[i] + "V3Rr3.wav");
    }
   
}

void OSampler::agregarSonidoOSampler(String tipoDeGolpe, String nombre)
{
    int midiN;

    
    if (tipoDeGolpe == String("Agudo")) {
        midiN = 62; 
    }
    else if (tipoDeGolpe == String("Grave")) {
        midiN = 60;
    }
    else { midiN = -1; };
 
    File* sample = new File(mCarpetaSamples.getChildFile(nombre));

    std::unique_ptr<AudioFormatReader> lectorArchivos(mFormatosAudio.createReaderFor(*sample));
    BigInteger n;
    n.setBit(midiN);

    addSound(new OSamplerSound(tipoDeGolpe, *lectorArchivos, n, midiN, 0.01f, 0.5f, 1.0f));

    lectorArchivos = nullptr;
    delete sample;
}

void OSampler::noteOn(int midiChannel, int midiNoteNumber, float velocity)
{
    // interpolar y truncar velocity ( 0 , 1 , 2 == 127 )
    velocityInt = (3 * velocity);
    velocityInt = min(velocityInt,2);
    // AJUSTAR CURVA DE VELOCITY



    //elegir el sonido
    // AGREGAR UNA OCTAVA MÁS PARA DOS MANOS
    switch (midiNoteNumber)
    {
    case 60:
        sampleSelector = 9;
        break;
    case 62:
        sampleSelector = 0;
        break;
    case 72:
        midiNoteNumber = 60;
        sampleSelector = 9;
        break;
    case 74:
        midiNoteNumber = 62;
        sampleSelector = 0;
        break;
    default:
        sampleSelector = 0;
        break;
    }

    //roundRobin = rand() % 2;

    roundRobin += x > (RAND_MAX / 2) ? 1 : -1;

    if (roundRobin < 0)
        roundRobin = 2;
    else if (roundRobin > 2)
        roundRobin = 0;
        
    // Asignar el sonido tocado a la variable
    sonido = getSound(sampleSelector+velocityInt+roundRobin).get();

    /// 
    ///  Acá sucede la magia
    /// 
    
    for (int i = 0; i < getNumVoices(); i++) {
        voz = dynamic_cast<OSamplerVoice*>(getVoice(i));
        if (sonido->appliesToNote(midiNoteNumber) && sonido->appliesToChannel(midiChannel)) {
            if (voz->puedeTocarOSound(midiNoteNumber)) {
                stopVoice(voz, 0.0f, true);
            }
        }

        if (voz->puedeTocarOSound(midiNoteNumber)) {
            startVoice(findFreeVoice(sonido, midiChannel, midiNoteNumber, true), sonido, midiChannel, midiNoteNumber, velocity);
        }
    }
}   