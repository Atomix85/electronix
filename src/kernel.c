#include "kernel.h"

void initConf(char * confFilename){

    FILE * file = NULL;

    file = fopen(confFilename,"r");

    if(file != NULL){

        //fscanf(file,"%d %d\n%d %d %d\n",scoreX,scoreY,size,player,mode);

        fclose(file);
    }

}
SDL_Window* initWindow(){
     if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stderr,"Window Initialisation Error :/ -> %s\n",SDL_GetError());
        return NULL;
    }

    SDL_Window* windowP = SDL_CreateWindow("Electronix",SDL_WINDOWPOS_UNDEFINED,
                                                            SDL_WINDOWPOS_UNDEFINED,
                                                            640,
                                                            480,
                                                            SDL_WINDOW_MAXIMIZED);
    SDL_SetWindowResizable(windowP, SDL_TRUE);
    if(windowP == NULL){
        fprintf(stderr,"Window Creation Error :/ -> %s\n",SDL_GetError());
    }

    return windowP;
}
SDL_Renderer* initRenderer(SDL_Window* windowP){

    SDL_Renderer* rendererP = SDL_CreateRenderer(windowP,-1,SDL_RENDERER_ACCELERATED);

    if(rendererP == NULL){
        fprintf(stderr,"Renderer Creation Error :/ -> %s\n", SDL_GetError());
    }
    return rendererP;

}
int initImg()
{
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int codeInit = IMG_Init(flags);
    if((codeInit&flags) != flags){
        fprintf(stderr,"Image Initialisation Error :/ -> %s\n", IMG_GetError());
        return 0;
    }
    return 1;
}
int init(SDL_Window** windowP, SDL_Renderer** rendererP){

    *windowP = initWindow();
    if(*windowP != NULL){
        *rendererP = initRenderer(*windowP);
        if(*rendererP == NULL){
            return 0;
        }
    }
    else{
        return 0;
    }

    if(!initImg()){
        return 0;
    }

    return 1;

}
int postInit(SDL_Renderer* rendererP,SDL_Surface** surfaceP){

    int i;
    *surfaceP = IMG_Load("./img/test.jpg");
    if(!*surfaceP){
        fprintf(stderr,"Image Loading Error :/ -> %s\n", IMG_GetError());
        return 0;
    }



    initLayout(rendererP,*surfaceP);
    return 1;
}
void freeRessources(SDL_Surface* surfaceP){

    destroyTextures();
    SDL_FreeSurface(surfaceP);
}
void endApp(SDL_Window* windowP, SDL_Renderer* rendererP,SDL_Surface* surfaceP){

    freeRessources(surfaceP);
    IMG_Quit();
    SDL_DestroyRenderer(rendererP);

    SDL_DestroyWindow(windowP);
    SDL_Quit();
}
int updateApp(SDL_Renderer* rendererP, SDL_Surface* surfaceP){
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        update(rendererP, surfaceP);

        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                continuer = 0;
            case SDL_QUIT:
                continuer = 0;
        }
    }
    return 0;

}

