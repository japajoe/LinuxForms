#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <vector>

namespace LinuxForms
{
    struct Rectangle
    {
        double x;
        double y;
        double width;
        double height;

        bool Contains(double x, double y)
        {
	        if(x >= this->x && x <= (this->x+width))
	        {
		        if(y >= this->y && y <= (this->y+height))
		        {
			        return true;
		        }
	        }
	        return false;
        }

        static std::vector<std::vector<Rectangle>> GetRectangle2D(double leftIndent, double topIndent, double width, double height, int rows, int cols, double offsetX, double offsetY)
        {
	        std::vector<std::vector<Rectangle>> rectangles;

	        for (int i = 0; i < rows; i++)
	        {
		        std::vector<Rectangle> rects;
		        for (int j = 0; j < cols; j++)
		        {
			        double x = leftIndent + (j * (width + offsetX));
			        double y = topIndent + (i * (height + offsetY));
                    Rectangle rect = { x, y, width, height };
			        rects.push_back(rect);
		        }
		        rectangles.push_back(rects);
	        }

	        return rectangles;
        }
    };
}

#endif
