#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "lrc.h"
#include "list.h"

static int head_parse(const u8 *buff, int *offset)
{
	char *c;
	const u8 *p = buff;
	char lyric_buff[DATALEN];

	c = strchr(p, ']');
	*c = '\0';

	c = strchr(p, ':');
	*c = '\0';

	if (!(strncmp(p, "ti", 2)))
		sprintf(lyric_buff, "song:%s", p + 3);

	if (!(strncmp(p, "ar", 2)))
		sprintf(lyric_buff, "singer:%s", p + 3);

	if (!(strncmp(p, "al", 2)))
		sprintf(lyric_buff, "album:%s", p + 3);

	if (!(strncmp(p, "by", 2)))
		sprintf(lyric_buff, "Manufacture:%s", p + 3);

	if (!(strncmp(p, "offset", 6))) {
		sprintf(lyric_buff, "%s", p + 7);
		*offset = atoi(lyric_buff);
		memset(lyric_buff, 0, DATALEN);
		}

	//show_text(int x, int y, char *text, int color);
	//printf("line %d %s\n", __LINE__, lyric_buff);

	return 0;

}



static struct _ListNode *Transfer_lyric(const u8 *lrc_buff, size_t size, Node *first)
//int Transfer_lyric()
{
	LrcData data[DATALEN];
	LrcData *p_data = data;
	char lyric_buff[DATALEN];
	char *q = lyric_buff;
	int offset;
	float time[TIMECOUNT][TIME];
//	Node *first = NULL;

	char test[1000] = "   [ti:Shape Of My Heart]\n"
			"[ar:Backstreet Boys]\n"
			"[al:Black And Blue]\n"
			"[by:qjxzbz@sohu.com]\n"
			"[offset:500]\n"
//			"[00:03.00]\n"
//			"\n"
			"  [00:04.10]Hmm, yeah, yeah\n"
			"[00:09.80]Baby, please try to forgive me\n"
			"[00:19.50]Stay here don't put out the glow\n"
			"[00:29.17]Hold me now don't bother\n"
//			"[03:11.45][02:51.90][01:48.00][00:47.29]Lookin' back on the things I've done\n"
//			"[03:14.70][02:55.50][01:52.70][00:52.04]I was tryin' to be someone\n"
//			"[03:19.15][02:59.70][01:57.00][00:56.44]I played my part, kept you in the dark\n"
			"[03:24.53][03:05.40][02:47.29][02:02.33][01:01.74]Now let me show you the shape of my heart";
	u8 *p = test;



	while (*p) {
		int flag = 0;
		memset(time, 0, TIMECOUNT * TIME);
		q = lyric_buff;

		while (*p != '\n' && *p) {
			if (*p == '[') {
				p++;
				if (NISNUM(*p)) {
					head_parse(p, &offset);
					continue;
				} else {
					flag += 1;
					while (*p != ':')
						time[flag - 1][0] = time[flag - 1][0] * 10  + (*p++ - '0');

					while (*++p != '.')
						time[flag - 1][1] = time[flag - 1][1] * 10 + (*p - '0');

					while (*++p != ']')
						time[flag - 1][2] = time[flag - 1][2] * 10 + (*p - '0');
				}
			}

			if (*++p != '[' && *p != ' ') {
				while (*p) {
					if (*p == '\n')
						break;
					*q++ = *p++;
				}
				*q = '\0';

				while (flag--) {
					//p_data->str = malloc(512);

					strcpy(p_data->str, lyric_buff);
					p_data->time = time[flag][0] * 60 + time[flag][1] + (time[flag][2] + offset) / 1000 ;

//					printf("%f  ",p_data->time);
//					printf("%s\n",p_data->str);
					first = InsertList(first, *p_data);
					//p_data++;
				}
			}
		}
		p++;
	}

	traverselist(first);
	return first;
}

int show_lyric(const u8 *lrc_buff, size_t size, struct timeval *total, struct timeval *curr)
{
	Node *first = NULL;
	float timeData;
	char buff[512];
	int offset;
	char *temp;
	char *p = lrc_buff;
	static int flag = 0;

//	timeData = curr->tv_sec + curr->tv_usec;
	timeData =185.04;

	if (lrc_buff == NULL)
		return -1;

	if (flag == 0) {
		first = InitList(first);
		first = Transfer_lyric(lrc_buff, size, first);
		flag = 1;
	}
	if (flag == 1) {
		//first = DeleteNode(first, timeData, buff); //fixme
		//show_text(int x, int y, char *text, int color);
	}

//	printf("%s\n", buff);
	//DestroyNode(first);

	return 0;
}


int main()
{
	struct timeval *curr;
	struct timeval *total;
	u8 *lrc_buff;
	size_t size;

	show_lyric(lrc_buff, size, total, curr);
	//Transfer_lyric();
//	Node *first;
//
//	first = InitList();
//	LrcData *lrc;
//
//	lrc = malloc(sizeof(*lrc));
//
//	lrc->time = 11.10;
//	lrc->str = "jjcc";
//
//	first = InsertList(first, lrc);
//
//	lrc->time = 68.10;
//	lrc->str = "9987";
//
//	first = InsertList(first, lrc);
//	showlist(first);
//
////	printf("%f, %s", first->next->Data.time, first->next->Data.str);
//
	return 0;
}

