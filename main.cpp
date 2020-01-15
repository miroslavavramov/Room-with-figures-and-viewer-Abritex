#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "Data.h"
#define VIEWER_LOOK_TO_ZERO 1
#define VIEWER_ROTATE	180

/* ./room in.txt  */
int main(int argc, char* argv[])
{
	FILE *fp = fopen(argv[1], "r");
//	Data d{fp};
	Data d(fp);

	fclose(fp);
	int angle;
/*	
	int i, j;
	for(i = 0; i < 2; ++i){
		for(j = 0; j<2; ++j){
			printf("arr[%d][%d] = %d\n", i, j, d.arr[i][j]);
			
		}
	}

	for(i = 0; i < d.getNumObj(); ++i){
		for(j = 0; j < d.size[i]/2 + 1; ++j){
			printf("coord[%d][%d].x = %d", i, j,d.coord[i][j].x);
			printf("coord[%d][%d].y = %d\n",i, j,d.coord[i][j].y);
		}
		printf("\n");
	}
	printf("numobj = %d\n",d.getNumObj());
*/
	angle = VIEWER_LOOK_TO_ZERO;
	d.setFiguresView(angle);
	printf("observer can see - %d figures\n", d.getFiguresView());
	d.validateCoordinates();
	
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(d.arr[0][0], d.arr[0][1], 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

		//picture---
		SDL_Texture* m_pTexture; // the new SDL_Texture variable
		SDL_Rect m_sourceRectangle; // the first rectangle
		SDL_Rect m_destinationRectangle; // another rectangle
		SDL_Surface* pTempSurface = IMG_Load("bee.png");
		m_pTexture = SDL_CreateTextureFromSurface(renderer,pTempSurface);
		SDL_FreeSurface(pTempSurface);
		SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
		m_destinationRectangle.x = d.arr[1][0];
		m_destinationRectangle.y = d.arr[1][1];
		m_destinationRectangle.w = m_sourceRectangle.w;
		m_destinationRectangle.h = m_sourceRectangle.h;
		SDL_Point center;

		// Calculate center pos by setting
		center.x = m_destinationRectangle.w / 2;
		center.y = m_destinationRectangle.h / 2;
		//Main loop flag
		bool quit = false;

                //Event handler
                SDL_Event e;

                //Angle of rotation
                double degrees = 0;

                //Flip type
                SDL_RendererFlip flipType = SDL_FLIP_NONE;

                //While application is running
                while( !quit )
                {
                        //Handle events on queue
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if( e.type == SDL_MOUSEBUTTONDOWN )
                                {
                                        switch( e.button.button )
                                        {
                                                case SDL_BUTTON_LEFT:
                                                degrees -= VIEWER_ROTATE;
						angle = !angle;
						d.setFiguresView(angle);
                                                break;

                                                case SDL_BUTTON_RIGHT:
                                                degrees += VIEWER_ROTATE;
						angle = !angle;
						d.setFiguresView(angle);
                                                break;

                                        }
                                }
                        }

                printf("observer can see - %d figures\n", d.getFiguresView());
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

//                SDL_RenderCopy(renderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);

                //Render to screen
                SDL_RenderCopyEx( renderer, m_pTexture, NULL, &m_destinationRectangle, degrees, &center, flipType );


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
//                SDL_RenderDrawLines(renderer, points, POINTS_COUNT);

                for(int i = 0; i < d.getNumObj(); ++i)
                        SDL_RenderDrawLines(renderer, d.coord[i], d.size[i]/TWO_POINT_XY + GO_TO_FIRST_COORDINATE);

                SDL_RenderPresent(renderer);

            }

        }
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}

