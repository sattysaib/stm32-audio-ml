#ifndef FEATURE_ENERGY_H
#define FEATURE_ENERGY_H

#include <stdint.h>
#include "arm_math.h"

float32_t* RMSEng(float32_t* audio, float32_t* output, uint32_t audioSize, uint32_t hop_size, uint32_t winLen);
void pad_audio(float32_t *audioBuffer, uint32_t original_len, uint32_t padding_needed);
float32_t* FRAMINGANDWINDOW(float32_t* audio, float32_t* output, uint32_t audioSize, uint32_t hop_size, uint32_t winLen);



#endif
