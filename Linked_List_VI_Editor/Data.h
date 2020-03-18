#ifndef __Data_H__
#define __Data_H__

typedef struct _Line {
	char *string;
	struct _Line *L_Next;
	struct _Line *R_Next;
}Line;



#endif

#define TRUE 1
#define FALSE 0
#define FAIL -1
