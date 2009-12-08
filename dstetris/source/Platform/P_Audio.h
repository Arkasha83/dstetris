#pragma once

#include <nds.h>
#include <maxmod9.h>

#include "soundbank.h"
#include "soundbank_bin.h"

enum eSFX
{
	eSFX_CLUNK,
	eSFX_SWISH,
	TOTAL,
};

void Audio_Init()
{
	mmInitDefaultMem((mm_addr)soundbank_bin);
	
	// load the module
	mmLoad( MOD_FLATOUTLIES );

	// load sound effects
	mmLoadEffect( SFX_CLUNK );
	mmLoadEffect( SFX_SWISH );

	return;
}

void Audio_PlaySoundEX( int i )
{
	mm_sound_effect sound;
	int id = 0;
	switch( i )
	{
		case eSFX_CLUNK : id = SFX_CLUNK; break;
		case eSFX_SWISH : id = SFX_SWISH; break;
	}

	sound.id      = id;			 // sample ID (make sure it is loaded)
	sound.rate    = 0x400/2;     // playback rate, 1024 = original sound
	sound.handle  = 0;           // 0 = allocate new handle
	sound.volume  = 200;         // 200/255 volume level
	sound.panning = 128;         // centered panning

	mmEffectEx( &sound );
}

void Audio_PlaySound( int sound )
{
	int id = 0;
	switch( sound )
	{
		case eSFX_CLUNK : id = SFX_CLUNK; break;
		case eSFX_SWISH : id = SFX_SWISH; break;
	}
	mmEffect( id );
}

void Audio_PlayMusic()
{
	// Start playing module
	mmStart( MOD_FLATOUTLIES, MM_PLAY_LOOP );
}
