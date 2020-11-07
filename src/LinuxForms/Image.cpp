#include "Image.h"

LinuxForms::Image::Image()
{
    widget = nullptr;
}

LinuxForms::Image::Image(const std::string& filename)
{
    LoadFromFile(filename);
}

LinuxForms::Image::Image(Texture* texture)
{
    LoadFromTexture(texture);
}

bool LinuxForms::Image::LoadFromFile(const std::string& filename)
{
    widget = gtk_image_new_from_file(filename.c_str());
    
    if(widget == nullptr)
        return false;
    return true;    
}

bool LinuxForms::Image::LoadFromTexture(Texture* texture)
{
    widget = gtk_image_new_from_pixbuf(texture->GetPixels());

    if(widget == nullptr)
        return false;
    return true;
}

