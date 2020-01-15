#ifndef _DATA_H_
#define _DATA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SDL.h"

#define GO_TO_FIRST_COORDINATE 1
#define TWO_POINT_XY 2

class Data{
public:
//	Data(FILE *fp, char *line = NULL, char *value = NULL, size_t len = 0, ssize_t read, int arr[2][2], SDL_Point **coord, int *size, int numObj, int figuresView, unsigned coordN);
	Data(FILE *fp);
	~Data();

	void setFiguresView(int angle);
	void validateCoordinates();
	int getNumObj() { return m_numObj; }
	int getFiguresView() { return m_figuresView; }
	
	int arr[2][2];
	SDL_Point **coord;
	int *size;

private:
//	Data(const Data &data);
	void init(FILE *fp);
	int m_figuresView;	
	int m_numObj;
	unsigned coordN;
	size_t len;
	ssize_t read;
	
	char *line = NULL;
	char *value = NULL;

	unsigned numCount(const char *str);
};
#endif
