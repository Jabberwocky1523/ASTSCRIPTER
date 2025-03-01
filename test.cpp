#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

// 从文件读取数据到内存
unsigned char *loadFileToMemory(const char *path, size_t *fileSize)
{
    FILE *file = fopen(path, "rb");
    if (!file)
    {
        printf("Failed to open file: %s\n", path);
        return NULL;
    }

    // 获取文件大小
    fseek(file, 0, SEEK_END);
    *fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 分配内存
    unsigned char *buffer = (unsigned char *)malloc(*fileSize);
    if (!buffer)
    {
        printf("Failed to allocate memory for file data\n");
        fclose(file);
        return NULL;
    }

    // 读取文件数据到内存
    fread(buffer, 1, *fileSize, file);
    fclose(file);

    return buffer;
}

int main2(int argc, char *argv[])
{
    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // 初始化SDL_image
    if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
    {
        printf("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // 图片路径
    const char *imagePath = "../zy.jpg";

    // 将图片文件加载到内存
    size_t fileSize;
    unsigned char *fileData = loadFileToMemory(imagePath, &fileSize);
    if (!fileData)
    {
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 从内存创建SDL_RWops
    SDL_RWops *rwops = SDL_RWFromMem(fileData, fileSize);
    if (!rwops)
    {
        printf("Failed to create SDL_RWops from memory: %s\n", SDL_GetError());
        free(fileData);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 加载JPG图片
    SDL_Surface *imageSurface = IMG_LoadJPG_RW(rwops);
    if (!imageSurface)
    {
        printf("Failed to load image: %s\n", IMG_GetError());
        SDL_RWclose(rwops);
        free(fileData);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 关闭SDL_RWops
    SDL_RWclose(rwops);

    // 在这里你可以使用imageSurface进行其他操作，比如显示图片等

    // 释放表面
    SDL_FreeSurface(imageSurface);

    // 释放内存数据
    free(fileData);

    // 退出SDL_image
    IMG_Quit();

    // 退出SDL
    SDL_Quit();

    return 0;
}