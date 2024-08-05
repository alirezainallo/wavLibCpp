#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <Windows.h>
#include <stdbool.h>

#include "../source/wav.h"

// #pragma warning(disable  : 4996)

char mmWavName[128] = "out.wav";
int16_t wavBufMM[96000 * 2][8] = { 0 };
float  wavBufMM_float[96000 * 2][8] = { 0 };
// int16_t readFileBuffer[96000 * 2 * 8] = { 0 };



// wav_header_t wavHeaderMM;
wav_handle_t  hWav;
int main(void) {
	// wav_handle_t hWav;

	printf("Starting...\n");

	wav_readFile(&hWav, mmWavName, true);
	uint32_t sampleRate   = wav_getDetails(&(hWav.header), WAV_SAMPLE_RATE);
	uint32_t numOfChannel = wav_getDetails(&(hWav.header), WAV_CHANNELS);
	uint32_t numOfSamplePerChannel = wav_getDetails(&(hWav.header), WAV_SAMPLE_PER_CHANNEL);
	// uint8_t neededCh[8];//numOfChannel
	// for(uint8_t ind = 0; ind < numOfChannel; ind++)
	// 	neededCh[ind] = ind;
	uint32_t numOfSamplePerChannelToRead = numOfSamplePerChannel; //numOfSamplePerChannel
	uint32_t startIndexToRead			 = 0;//0
	wav_readSample(&hWav, startIndexToRead, numOfSamplePerChannelToRead, (void**)&wavBufMM[0]);
	// ready wavBufMM
	for (uint32_t sample = 0; sample < numOfSamplePerChannelToRead; sample++) {
		for (uint32_t ch = 0; ch < numOfChannel; ch++) {
			wavBufMM_float[sample][ch] = wav_normalizeInt16ToFloat(wavBufMM[sample][ch]);
		}
	}
	wav_close(&hWav);

	
	//Write 
	wav_readFile(&hWav, (char*)"out.wav", sampleRate, numOfChannel, WAV_PCM_DATA, true);
	wav_WriteSample(&hWav, 0, numOfSamplePerChannel, (void**)wavBufMM);
	wav_close(&hWav);
	return 0;
}

