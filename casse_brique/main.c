#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "level.c" 






char str_score[10];

void menu();		// FAIT PAR RACHID
void timer(); 		// FAIT PAR RACHID


int main(int argc, char *argv[])
{
	SDL_Window *window  = NULL;
	SDL_Renderer *renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
  	{
      	 

      if(TTF_Init() != 0){
      SDL_Log("ERROR \n");
      SDL_Quit();
      exit(EXIT_FAILURE);
  	  }

 
  	 window = SDL_CreateWindow("CASSE BRIQUE",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800,600, 0);
  	 renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	 SDL_Surface* logo= IMG_Load("img/logo.png");
  	 SDL_SetWindowIcon(window,logo);
	// BACKGROUND
      SDL_Surface* background= IMG_Load("img/menu/press_enter.bmp");
      SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);
      SDL_Rect coord_background = {.x =0, .y = 0, .w = 800, .h = 600};
      SDL_RenderCopy(renderer, background_texture, 0, &coord_background);

      SDL_Color blanc={245,255,250};
      TTF_Font* font1 = TTF_OpenFont("fonts/8_bit.ttf", 40);
      
      SDL_Surface* enter = TTF_RenderText_Blended(font1,"PRESS ENTER",blanc);
      SDL_Texture* texture_enter = SDL_CreateTextureFromSurface(renderer, enter);
      SDL_Rect pos_enter = {.x = 180, .y = 370};
     SDL_QueryTexture(texture_enter, NULL, NULL, &pos_enter.w, &pos_enter.h);
     SDL_RenderCopy(renderer, texture_enter, NULL, &pos_enter);

      
     SDL_RenderPresent(renderer);

     TTF_CloseFont(font1);
     SDL_bool program_launched = SDL_TRUE;

	    while(program_launched)   	
	    {
	      timer();
	      SDL_Event event;
		    while(SDL_PollEvent(&event))
		    {
		          
		        switch(event.type)
		        {
		            case SDL_KEYDOWN:
		              
		                  switch(event.key.keysym.sym)
		                  {
		                
		                      case SDLK_RETURN:                                   
		                          SDL_Quit();
		                          menu();                          
		                      break;

		                      default:                      
		                      continue;
		                  }

		            case SDL_QUIT:
		                program_launched = SDL_FALSE;
		            break;
		                       
		        }
		    }
	  	}
	}
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
TTF_Quit();
SDL_Quit();
return EXIT_SUCCESS;
}


void menu()
{
  	SDL_Renderer *renderer = NULL;
  	SDL_Window *window = NULL;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
  {
		  window = SDL_CreateWindow("CASSE BRIQUE",
		                             SDL_WINDOWPOS_UNDEFINED, 
		                             SDL_WINDOWPOS_UNDEFINED, 800,600, 0); 
		  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		  
  if(TTF_Init() != 0)
  {
			SDL_Log("ERROR\n");
  }
		 


		  /*--------------------------------------------------------------*/
		  SDL_Surface* background= IMG_Load("img/menu/brickwall.bmp");;
		  SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);
		  SDL_Rect pos_background = {.x = 0, .y = 18, .w = 800, .h = 600};
		  SDL_RenderCopy(renderer, background_texture, NULL, &pos_background);


		// MUSIC LOADER grâce à lib mixer qui alloue un canal à la musique et la joue en loop grâce à la valeur -1 
			if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
		  	{    
		    	printf("%s", Mix_GetError());  
		  	}

		  
		    Mix_Music* musique; // Pointeur musique dans lequel on stocke la musique en .ogg 
		    musique = Mix_LoadMUS("sounds/funk.ogg");  
		    Mix_AllocateChannels(5);
		    Mix_PlayMusic(musique, -1); //Musique à l'infini avec -1


		//GENERATEUR DE COULEURS RGB
		    SDL_Color jaune = {204, 204, 0}, orange = {255, 128, 0}, blanc = {255, 255, 255}, 
		    rouge = {204, 0, 0}, red = {255, 0, 0}, noir = {0, 0, 0}, bleu = {0, 102, 204}, lightgrey = {192,192,192}, grey = {224,224,224};
			


		//CHARGE LES FONTS
		  	TTF_Font *font1, *font2, *font3, *font4, *font6;
		    	font1 = TTF_OpenFont("fonts/gums.ttf", 40);
		    	font2 = TTF_OpenFont("fonts/arcade.ttf", 33);
		    	font3 = TTF_OpenFont("fonts/letters.ttf", 14);
		    	font4 = TTF_OpenFont("fonts/grobold.ttf", 11);
		    	font6 = TTF_OpenFont("fonts/8_bit.ttf", 8);



		//BANDEAU OPTIONS
		    SDL_Surface* bandeau = TTF_RenderText_Blended(font4,"Echap=Quitter                          "
		    	"J=Jouer                       "
		    	"S=Score                                    "
		    	"M=Couper/Mettre la musique                                  "
		    	"C=Credits                                                                        "
		    	"P=Jouer", grey);
		  	
		//MENU COMPLET
		  	SDL_Surface* titre = TTF_RenderText_Blended(font1,"CASSEBRIQUE", orange);
		  	SDL_Surface* play = TTF_RenderText_Blended(font2,"Jouer", blanc);
		  	SDL_Surface* credits = TTF_RenderUTF8_Blended(font2, "Credits", blanc); 	
		  	SDL_Surface *copyright = TTF_RenderText_Blended(font3, "Copyright Ed & RNL", blanc);
		  	SDL_Surface* click_1 = TTF_RenderText_Blended(font6,"click", grey);
		     
		     SDL_Texture* bandeau_texture = SDL_CreateTextureFromSurface(renderer, bandeau);
		  	 SDL_Texture* titre_texture = SDL_CreateTextureFromSurface(renderer, titre);
		  	 SDL_Texture* play_texture = SDL_CreateTextureFromSurface(renderer, play);
		  	 SDL_Texture* credits_texture = SDL_CreateTextureFromSurface(renderer, credits);  	 
		  	 SDL_Texture* copy_texture = SDL_CreateTextureFromSurface(renderer, copyright);
		  	 SDL_Texture* click_1_texture = SDL_CreateTextureFromSurface(renderer, click_1);
			
			SDL_FreeSurface(bandeau);
		  	SDL_FreeSurface(titre);
		  	SDL_FreeSurface(play); 
		    SDL_FreeSurface(credits);    
		    SDL_FreeSurface(copyright);
		    SDL_FreeSurface(click_1);
		  	
		  	SDL_Rect pos_bandeau = {.x = 5, .y = 4};
		  	SDL_Rect pos_titre = {.x = 180, .y = 60};
		  	SDL_Rect pos_play = {.x = 325, .y = 250};
		  	SDL_Rect pos_credits = {.x = 315, .y = 350};   
		  	SDL_Rect pos_copy = {.x = 690, .y = 580};
		  	SDL_Rect pos_click_1 = {.x = 380, .y = 290};
		    
		    SDL_QueryTexture(bandeau_texture, NULL, NULL, &pos_bandeau.w, &pos_bandeau.h);
		    SDL_QueryTexture(titre_texture, NULL, NULL, &pos_titre.w, &pos_titre.h);
		    SDL_QueryTexture(play_texture, NULL, NULL, &pos_play.w, &pos_play.h);
		    SDL_QueryTexture(credits_texture, NULL, NULL, &pos_credits.w, &pos_credits.h);   
		    SDL_QueryTexture(copy_texture, NULL, NULL, &pos_copy.w, &pos_copy.h);
		    SDL_QueryTexture(click_1_texture, NULL, NULL, &pos_click_1.w, &pos_click_1.h);
		     
		     SDL_RenderCopy(renderer, bandeau_texture, NULL, &pos_bandeau);
		     SDL_RenderCopy(renderer, titre_texture, NULL, &pos_titre);
		     SDL_RenderCopy(renderer, play_texture, NULL, &pos_play);
		     SDL_RenderCopy(renderer, credits_texture, NULL, &pos_credits);     
		     SDL_RenderCopy(renderer, copy_texture, NULL, &pos_copy);
		     SDL_RenderCopy(renderer, click_1_texture, NULL, &pos_click_1);

		    SDL_RenderPresent(renderer);

	
    // LIBERATION MEMOIRE DES TTF CHARGES
		    TTF_CloseFont(font1);
		    TTF_CloseFont(font2);
		    TTF_CloseFont(font3);
		    TTF_CloseFont(font4);
		    TTF_CloseFont(font6);
		    

		 /*--------------------------------------------------------------*/
			SDL_bool program_launched = SDL_TRUE;
			while(program_launched)
		  	{
		  		timer();
		    	SDL_Event event;

		    	while(SDL_PollEvent(&event))
		    	{
		          
		     		switch(event.type)
		        	{
		           
		            	case SDL_KEYDOWN:   										// TYPE 1 SDL KEYDOWN
		              
		                	switch(event.key.keysym.sym)
		              		{
		                
		                    	case SDLK_ESCAPE:                 	    						
		                      		program_launched = SDL_FALSE;		                      		
		            			break;
		                    	/*
		            			case SDLK_s:                 	    						
		                      		score(points);
                                         SDL_Surface* score_1 = TTF_RenderText_Blended(font6,"LAST SCORE", noir);
                                            SDL_Texture* score_1_texture = SDL_CreateTextureFromSurface(renderer, score_1);
                                            SDL_FreeSurface(score_1);
                                            SDL_Rect pos_score_1 = {.x = 450, .y = 550};
                                            SDL_QueryTexture(score_1_texture, NULL, NULL, &pos_score_1.w, &pos_score_1.h);
                                            SDL_RenderCopy(renderer, score_1_texture, NULL, &pos_score_1);

                                         SDL_Surface* score_2 = TTF_RenderText_Blended(font6,str_score, noir);
                                            SDL_Texture* score_2_texture = SDL_CreateTextureFromSurface(renderer, score_2);
                                            SDL_FreeSurface(score_2);
                                            SDL_Rect pos_score_2 = {.x = 600, .y = 550};
                                            SDL_QueryTexture(score_2_texture, NULL, NULL, &pos_score_2.w, &pos_score_2.h);
                                            SDL_RenderCopy(renderer, score_2_texture, NULL, &pos_score_2);
                                            SDL_RenderPresent(renderer);
                                        sleep(5);	
                                        SDL_DestroyRenderer(renderer);	                      		
		            			break;
								*/
		            			case SDLK_j:		       
		                      		Mix_CloseAudio();
		                      		program_launched = SDL_FALSE;
		                          	SDL_Quit();
		                          	level();
								break;

		                    	case SDLK_m:    
		      						// MUSIQUE PLAY / PAUSE
		                  			if(Mix_PausedMusic() == 1)
		                  			{
		                     			Mix_ResumeMusic();                   		 
		                  			}
		                  	    
		                  	    	else
		                  			{
		     							Mix_PauseMusic();                  		                  	
		                 			}
		                  		continue;

		                    	default:                    	
		                   		continue;                                   // END TYPE SDL KEYDOWN
		                	}

		            	case SDL_QUIT:										// TYPE 2 SDL QUIT
		            		program_launched = SDL_FALSE;
		            	break;
		            	          									// END TYPE 2 SDL QUIT              	
		              	case SDL_MOUSEBUTTONUP:
		              		if(event.button.button == SDL_BUTTON_LEFT){

		                        

		                        if(event.button.x > 290 && event.button.x < 520 && event.button.y > 230 && event.button.y < 310){
		                        	
		              				Mix_CloseAudio();
		              				program_launched = SDL_FALSE;
		                          	SDL_Quit();
		                          	level();		                      		
		                        	break;

		                        }
		                    }

		              		continue;
		              		
		              	default:
		              	break;       	
		    	}
			}
		}
	}
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
TTF_Quit();
Mix_CloseAudio();
SDL_Quit(); 
}   
  
 void timer(){                                           //FAIT PAR RACHID                   // Détecteur d'inactivité
 	int compteur;
 	SDL_bool program_launched = SDL_TRUE;
 	if(SDL_GetTicks() > 300000){
 		for(compteur = 3; compteur >= 0; --compteur){
              	printf("Inactivité détéctée : le jeu va se fermer automatiquement dans %d...\n", compteur);
              	sleep(2);              
          	  }          	
              program_launched = SDL_FALSE;
              SDL_Quit();
              exit(-1);
    }
}
 
