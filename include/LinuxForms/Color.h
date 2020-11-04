#ifndef COLOR_HPP
#define COLOR_HPP

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
    };
}

#endif