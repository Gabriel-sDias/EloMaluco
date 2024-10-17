#include "textureManager.hpp"

TextureManager::TextureManager(){
}

uint TextureManager::setTexture(const string& path){
    uint textureID;
    
    textureID = SOIL_load_OGL_texture(
        path.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if (textureID == 0) {
        std::cout << "SOIL loading error: " << SOIL_last_result() << std::endl;
    } else {
        std::cout << "Texture loaded: " << path << std::endl;
    }
    
    return textureID;
}