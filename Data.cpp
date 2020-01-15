#include "Data.h"

#define START_COORD 3

Data::Data(FILE *fp):
	m_figuresView(0),
	m_numObj(0),
	coordN(0),
	len(0),
	read(0)
{
	init(fp);
}

Data::~Data(){
	for(int i = 0; i < (size[i]/2 + GO_TO_FIRST_COORDINATE); i++)
	    delete [] coord[i];
	delete [] coord;
	
	delete [] size;
}

void Data::init(FILE *fp){
	int i = 0, j = 0;
//	fp = fopen("ini.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
//		printf("Retrieved line of length %zu :\n", read);
		if(i < 2){
//			printf("%s, %d", line, i);
			value = strtok(line, " ,");
			arr[i][0] = atoi(value);
		
			value = strtok(NULL, " ,");
			arr[i][1] = atoi(value);
		}else if(i == 2){
//			printf("%s, %d\n", line, i);
			m_numObj = atoi(line);
			coord = new SDL_Point*[m_numObj]; 
			size = new int[m_numObj];
		}else if(i>2 && i < START_COORD + m_numObj){
	               printf("i = %d %s\n", i - START_COORD, line);
			coordN = numCount(line);
			printf("coordN = %u\n", coordN);
			coord[i - START_COORD] = new SDL_Point[coordN/2 + GO_TO_FIRST_COORDINATE];
			size[i - START_COORD] = coordN;
/*
			for(j = 0; j < coordN; ++j){
				coord[i-3][j] = i;
			}
*/
			for(j = 0; j < coordN/2; ++j){
				value = strsep(&line, " ,");
				coord[i - START_COORD][j].x = atoi(value);
				value = strsep(&line, " ,");
				coord[i - START_COORD][j].y = atoi(value);
			}

			
		}
		++i;
	}

	for(i = 0; i < m_numObj; ++i){
		printf("size[%d] = %d\n", i, size[i]/TWO_POINT_XY + GO_TO_FIRST_COORDINATE);
		//add last line to first coordinate.
		coord[i][size[i]/TWO_POINT_XY].x = coord[i][0].x;
		coord[i][size[i]/TWO_POINT_XY].y = coord[i][0].y;
	}
}

void Data::setFiguresView(int angle){
	/*find how many figure observer can see*/
	int flag = 0;
	int i = 0, j = 0;
	if(angle){
		m_figuresView = 0;
		for(i = 0; i < m_numObj; ++i){
			for(j = 0; j < size[i]/TWO_POINT_XY + GO_TO_FIRST_COORDINATE; ++j){
				if(coord[i][j].x > arr[1][0] && coord[i][j].y > arr[1][1]){
/*					printf("coord[%d][%d].x = %d", i, j,coord[i][j].x);
					printf("coord[%d][%d].y = %d\n",i, j,coord[i][j].y);*/
					flag = 1;
				}else{
/*					printf("coord[%d][%d].x = %d", i, j,coord[i][j].x);
					printf("coord[%d][%d].y = %d\n",i, j,coord[i][j].y);*/
					flag = 0;
				}
//				printf("flag = %d\n", flag);

			}
				if(!flag)
					++m_figuresView;
		}
	}else{
		m_figuresView = 0;
		for(i = 0; i < m_numObj; ++i){
			for(j = 0; j < size[i]/TWO_POINT_XY + GO_TO_FIRST_COORDINATE; ++j){
				if(coord[i][j].x < arr[1][0] && coord[i][j].y < arr[1][1]){
/*					printf("coord[%d][%d].x = %d", i, j,coord[i][j].x);
					printf("coord[%d][%d].y = %d\n",i, j,coord[i][j].y);*/
					flag = 1;
				}else{
/*					printf("coord[%d][%d].x = %d", i, j,coord[i][j].x);
					printf("coord[%d][%d].y = %d\n",i, j,coord[i][j].y);*/
					flag = 0;
				}
//				printf("flag = %d\n", flag);

			}
				if(!flag)
					++m_figuresView;
		}
	}
	

//printf("figuresView = %d\n", figuresView);

}

void Data::validateCoordinates(){
	/*Wrong cordinates ini file line cross*/
	int i = 0, j = 0;
	for(i = 0; i< m_numObj; ++i){		
		for(j = 0; j < size[i]/2; ++j){
			if(i>0)
				if(coord[i][j].x > coord[i-1][j].x && coord[i][size[i]/2 - 1].x < coord[i-1][size[i-1]/2 - 1].x){
					printf("XXX coord[%d][%d].x = %d", i, j,coord[i][j].x);
					printf("XXX coord[%d][%d].y = %d\n",i, j,coord[i][j].y);
					perror("Wrong cordinates ini file line cross wrong");

					for(int i = 0; i < (size[i]/2 + GO_TO_FIRST_COORDINATE); i++)
						    delete [] coord[i];
						delete [] coord;
					exit(1);
				}
		}
	}
}

unsigned Data::numCount(const char *str){
	unsigned count = *str == ' '? 0 : 1;
	int i, len;
	len = strlen(str);
	for(i = 1;i < len; ++i){
		if((*(str + i -1) == ' ' && isdigit(*(str + i))) || (*(str + i -1) == ',' && isdigit(*(str + i))))
			count++;
		
	}
	return count;
}
