#ifndef __ENCODE_H__
#define __ENCODE_H__

#include <lame/lame.h>

typedef struct audio_buffer_t {
	unsigned char *data;
	int length;
} audio_buffer;

lame_t setup();
audio_buffer* encode(lame_t lcfg, short int ldata[], short int rdata[], unsigned int len);
int encode_file(lame_t lcfg, char *in_file, char *outfile);

#endif // __ENCODE_H__
