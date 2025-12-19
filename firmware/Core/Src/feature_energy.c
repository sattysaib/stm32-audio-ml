#include "feature_energy.h"
#include "arm_math.h"


float32_t* RMSEng(float32_t* audio, float32_t* output_eng, uint32_t audioSize, uint32_t hop_size, uint32_t winLen)
{
	float32_t* windowedMat = FRAMINGANDWINDOW(audio, output_eng, audioSize, hop_size, winLen);
	uint32_t N = ((audioSize) - winLen)/(hop_size) + 1;

	for (uint32_t i = 0; i < N; i++) {
	    // This one line replaces the power, division, and sqrt
	    arm_rms_f32(&windowedMat[i * winLen], winLen, &output_eng[i]);
	}

	return output_eng;

}


float32_t* FRAMINGANDWINDOW(float32_t* audio, float32_t* output, uint32_t audioSize, uint32_t hop_size, uint32_t winLen)
{
	uint32_t N = ((audioSize) - winLen)/(hop_size) + 1;
	float32_t window[winLen];
	uint32_t TOTAL_SAMPLES = N * winLen;
	arm_fill_f32(0.0f, output, TOTAL_SAMPLES);

	arm_hamming_f32(window,winLen);

	uint32_t last_frame_end = (N-1)* hop_size + winLen;
	if (last_frame_end > audioSize)
		{
		uint32_t padding_needed = last_frame_end - audioSize;
		pad_audio(audio, audioSize, padding_needed);
		}
	for(uint32_t i=0; i<N; i++)
	{
		float32_t *current_audio_frame = &audio[i * hop_size];

		    // Pointer to where this frame's results go in VecFrames
		    float32_t *dest_row = &output[i * winLen];

		    /* arm_mult_f32(srcA, srcB, dst, blockSize)
		       This does: dest_row[j] = current_audio_frame[j] * window[j]
		       for all samples in the window length.
		    */
		    arm_mult_f32(current_audio_frame, window, dest_row, winLen);
		}

	return output;
}

// Assume audioBuffer is large enough to hold (original_len + padding_needed)
void pad_audio(float32_t *audioBuffer, uint32_t original_len, uint32_t padding_needed) {

    // Pointer to the start of the padding area:
    // audioBuffer[original_len] is the first sample after your real data
    float32_t *padding_start = &audioBuffer[original_len];

    // Equivalent to mode='constant' (padding with 0.0)
    arm_fill_f32(0.0f, padding_start, padding_needed);
}
