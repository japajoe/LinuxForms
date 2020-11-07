#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Widget.h"
#include "Texture.h"

namespace LinuxForms
{
    class Image : public Widget
    {
    public:
        Image();
        Image(const std::string& filename);
        Image(Texture* texture);
        bool LoadFromFile(const std::string& filename);
        bool LoadFromTexture(Texture* texture);
        void SetScale(float x, float y);
    };
}
#endif