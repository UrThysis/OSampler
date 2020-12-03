/*
  ==============================================================================

    OSamplerVoice.cpp
    Created: 15 Jun 2020 1:35:23am
    Author:  UrThysis

  ==============================================================================
*/

#include "OSamplerVoice.h"

bool OSamplerVoice::canPlaySound(SynthesiserSound* sampSound)
{
    return ((dynamic_cast<OSamplerSound*>(sampSound)) != nullptr);
}

//=============================Configurar nota midi a la voz --- revisar doble
void OSamplerVoice::configurarNotaMidi(int nota) { notaMidi.setBit(nota); };

//==============REVISAR SI NECESITA INTERACTUAR CON NOTE ON EN SAMPLER MASTER =======TAL VEZ NO ES NECESARIO
bool OSamplerVoice::puedeTocarOSound(int nota) const { return notaMidi[nota]; };