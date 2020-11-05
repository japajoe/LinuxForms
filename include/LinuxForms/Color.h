#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>
#include <math.h>

namespace LinuxForms
{
    struct Color
    {
        float r;
        float g;
        float b;
        float a;
        
        Color()
        {
            r = 0;
            g = 0;
            b = 0;
            b = 0;            
        }

        Color(float r, float g, float b, float a)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        Color(int r, int g, int b, int a)
        {
            SetFromInt(r, g, b, a);
        }

        void SetFromInt(int r, int g, int b, int a)
        {
            this->r = (1.0/255) * r;
            this->g = (1.0/255) * g;
            this->b = (1.0/255) * b;
            this->a = (1.0/255) * a;
        }

        Color GetGrayscale()
        {
            float v = (float)((r + g + b) / 3);            
            return {v, v, v, this->a };
        }

        static Color Lerp(const Color& color1, const Color& color2, float t)
        {
            float r = color1.r + (color2.r - color1.r) * t;
            float g = color1.g + (color2.g - color1.g) * t;
            float b = color1.b + (color2.b - color1.b) * t;
            float a = color1.a;
            return { r, g, b, a };
        }

        static unsigned long ToHex(const Color& color)
        {
            int r = static_cast<int>(floor(color.r * 255));
            int g = static_cast<int>(floor(color.g * 255));
            int b = static_cast<int>(floor(color.b * 255));
            int a = static_cast<int>(floor(color.a * 255));
            return ToHex(r, g, b, a);
        }

        static unsigned long ToHex(int r, int g, int b, int a)
        {   
            return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
                + (a & 0xff);
        }        
    };
}

#endif