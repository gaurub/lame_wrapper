#include <stdio.h>
#include "encode.h"
#include <stdlib.h>
#include <string.h>

void print_error(const char *format, va_list ap) {
	printf(format, ap);
}

lame_t setup() {
	lame_t lame = lame_init();
	lame_set_VBR(lame, vbr_default);
	lame_set_in_samplerate(lame, 8000);
	lame_set_num_channels(lame, 1);
	lame_set_out_samplerate(lame, 8000);
	lame_set_mode(lame, 3);
	lame_init_params(lame);
	lame_set_errorf(lame, print_error);
	return lame;
}

audio_buffer *encode(lame_t lcfg, short int ldata[], short int rdata[], unsigned int length) {

	unsigned char *mp3_buffer = malloc(length * 2 * sizeof(unsigned char));
	
	memset(mp3_buffer, 0, length * 2);

	int write;

	if(sizeof(short) == sizeof(short int)) {
		write = lame_encode_buffer(lcfg, ldata, rdata, length, mp3_buffer, 
																															length * 2);
		//lame_encode_flush(lcfg, mp3_buffer, (length * 2 - write));
	} 
	audio_buffer *buffer = malloc(sizeof(audio_buffer));
	buffer->data = mp3_buffer;
	buffer->length = write;
	
	return buffer;

}

int encode_file(lame_t lcfg, char *in_file, char *out_file) {

	int read, write;
	FILE *pcm = fopen(in_file, "rb");
	FILE *mp3 = fopen(out_file, "wb");

	const int PCM_SIZE = 8192;
	const int MP3_SIZE = 8192;
	short int pcm_buffer[PCM_SIZE];
	unsigned char mp3_buffer[MP3_SIZE];

	do {
		read = fread(pcm_buffer, sizeof(short int), PCM_SIZE, pcm);
		if(read == 0) {
			lame_encode_flush(lcfg, mp3_buffer, MP3_SIZE);
		} else {
			short int pcm_buffer2[PCM_SIZE];
			memcpy(pcm_buffer2, pcm_buffer, PCM_SIZE * sizeof(short int));
			write = lame_encode_buffer(lcfg, pcm_buffer, pcm_buffer, PCM_SIZE, mp3_buffer, MP3_SIZE);
			fwrite(mp3_buffer, write, 1, mp3);
		}
	} while (read != 0);

	lame_close(lcfg);
	fclose(mp3);
	fclose(pcm);

	return 0;

}

