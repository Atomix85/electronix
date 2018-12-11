#include "mResistor.h"

void resistor_drawComponent(SDL_Rect currentRect,Component currentComponent, int idTex,SDL_Renderer * rendererP,
                        Datas datas){

    int state = currentComponent.stateModule;
    int angle = 0;

    switch(state){
        case 1: angle = 90;
            break;
        default:
            break;
    }

    SDL_RenderCopyEx(rendererP,
                     datas.textures->images[idTex],
                     NULL,
                     &currentRect,
                     angle,
                     NULL,
                     SDL_FLIP_HORIZONTAL);

}
