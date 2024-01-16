
#ifndef __UTILS_H__
#define __UTILS_H__
# include <SDL2/SDL.h>
# include <iostream>
# include <string>
# include <array>
# include <vector>

void logSDLError(std::ostream &os, const std::string &msg);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);



#endif // !__UTILS_H__
