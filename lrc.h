#pragma once

//#define LINE
#define LEN 1024
#define DATALEN 128
#define TIMECOUNT 20
#define TIME 3
#define NISNUM(a) (((a) > '9') || ((a) < '0'))
typedef unsigned char u8;

struct lrc_line {
	float time;
	char *lyrics;
};

//int show_lyric(u8 *lrc_buff, size_t size, struct timeval *total, struct timeval *curr);
