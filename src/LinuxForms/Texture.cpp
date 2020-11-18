#include "Texture.h"
#include <iostream>
#include <cstring>

LinuxForms::Texture::Texture()
{
	pixels = nullptr;
	buffer = nullptr;
	widget = gtk_fixed_new();
}

LinuxForms::Texture::Texture(const std::string& filepath)
{
	pixels = nullptr;
	buffer = nullptr;
	widget = gtk_fixed_new();	
	LoadFromFile(filepath);
}

LinuxForms::Texture::Texture(int width, int height, bool hasAlpha)
{
	pixels = nullptr;
	buffer = nullptr;
	widget = gtk_fixed_new();	
	LoadFromData(width, height, hasAlpha);
}

LinuxForms::Texture::~Texture()
{
	Dispose();
}

void LinuxForms::Texture::Dispose()
{	
	if(pixels != nullptr)
	{
		g_object_unref(pixels);
		pixels = nullptr;
	}
	if(buffer != nullptr)
	{
		delete[] buffer;
		buffer = nullptr;
	}
}

bool LinuxForms::Texture::LoadFromFile(const std::string& filepath)
{
	Dispose();

	GError* error = NULL;
	pixels = gdk_pixbuf_new_from_file(filepath.c_str(), &error);	
	
	if(error)
	{
		Dispose();
		std::cout << "Couldn't load image " << error->message << "\n";
		return false;
	}

	rectangle.width = gdk_pixbuf_get_width(pixels);
	rectangle.height = gdk_pixbuf_get_height(pixels);
	pixels = gdk_pixbuf_scale_simple(pixels, rectangle.width, rectangle.height, GDK_INTERP_BILINEAR);
	format = ImageFormat::FromPixbuf(pixels);
	gtk_widget_set_size_request(widget, rectangle.width, rectangle.height);
	g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);
	return true;
}

bool LinuxForms::Texture::LoadFromData(int width, int height, bool hasAlpha)
{
	Dispose();

	int bitsPerSample = 24 + hasAlpha ? 8 : 0;
	int size = width * height * bitsPerSample;
	int rowstride = width * bitsPerSample;
	buffer = new guint8[size];
	bzero(buffer, size);

	pixels = gdk_pixbuf_new_from_data(buffer, GdkColorspace::GDK_COLORSPACE_RGB, hasAlpha, bitsPerSample, width, height, rowstride, NULL, NULL);

	if(!pixels)
	{
		Dispose();
		return false;
	}

	rectangle.width = gdk_pixbuf_get_width(pixels);
	rectangle.height = gdk_pixbuf_get_height(pixels);
	pixels = gdk_pixbuf_scale_simple(pixels, rectangle.width, rectangle.height, GDK_INTERP_BILINEAR);
	format = ImageFormat::FromPixbuf(pixels);
	gtk_widget_set_size_request(widget, rectangle.width, rectangle.height);
	g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);
	return true;	
}

void LinuxForms::Texture::SetPosition(int x, int y)
{
	this->rectangle.x = x;
	this->rectangle.y = y;
}

void LinuxForms::Texture::Render(cairo_t* cr, int x, int y)
{
	if(pixels == nullptr)
		return;
		
	rectangle.x = x;
	rectangle.y = y;
	
	gdk_cairo_set_source_pixbuf(cr, pixels, rectangle.x, rectangle.y);
    cairo_paint(cr);
}

GdkPixbuf* LinuxForms::Texture::GetPixelBuffer() const
{
    return pixels;
}

void LinuxForms::Texture::SetPixelBuffer(GdkPixbuf* buffer)
{

}

LinuxForms::Color LinuxForms::Texture::GetPixel(int x, int y)
{
    guchar* pixelbuffer, *p;
    
    pixelbuffer = gdk_pixbuf_get_pixels(pixels);

	p = pixelbuffer + y * format.rowStride + x * format.channels;

	guchar c[4];
    memset(c, 0, 4);

	memcpy(c, p, format.channels);

    Color color;
    color.SetFromInt(c[0], c[1], c[2], c[3]);
    return color;
}

void LinuxForms::Texture::SetPixel(int x, int y, const Color& color)
{
	guchar* pixelbuffer, *p;

	if(format.colorSpace != GDK_COLORSPACE_RGB)
	{
		printf("ColorSpace != RGB\n");
		return;
	}
	if(format.bitsPerSample != 8)
	{
		printf("Bits Per Sample != 8\n");
		return;
	}

	if(x < 0 && x >= format.width)
		return;
	
	if(y < 0 && y >= format.height)
		return;

	pixelbuffer = gdk_pixbuf_get_pixels(pixels);

	p = pixelbuffer + y * format.rowStride + x * format.channels;

	guchar c[4];
	c[0] = static_cast<guchar>(color.r * 255);
	c[1] = static_cast<guchar>(color.g * 255);
	c[2] = static_cast<guchar>(color.b * 255);
	c[3] = static_cast<guchar>(color.a * 255);

	memcpy(p, c, format.channels);
}

void LinuxForms::Texture::Clear(const Color& color)
{
	if(pixels == nullptr)
		return;
	int c = Color::ToHex(color);
	gdk_pixbuf_fill(pixels, c);
}

void LinuxForms::Texture::SetScale(float x, float y)
{
	int newWidth = static_cast<int>(floor(rectangle.width * x));
	int newHeight = static_cast<int>(floor(rectangle.height * y));
	pixels = gdk_pixbuf_scale_simple(pixels, newWidth, newHeight, GDK_INTERP_BILINEAR);
	format = ImageFormat::FromPixbuf(pixels);
	rectangle.width = gdk_pixbuf_get_width(pixels);
	rectangle.height = gdk_pixbuf_get_height(pixels);	
	gtk_widget_set_size_request(widget, rectangle.width, rectangle.height);
}

void LinuxForms::Texture::DrawLine(int x1, int y1, int x2, int y2, const Color& color)
{
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (SetPixel(x1, y1, color), x1 != x2 || y1 != y2) 
	{
        int e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 <  dy) { err += dx; y1 += sy; }
    }
}

void LinuxForms::Texture::DrawRectangle(int x, int y, int width, int height, const Color& color)
{
	int xStart = x;
	int xEnd = xStart + width;
	int yStart = y;
	int yEnd = yStart + height;
	
	for(int i = yStart; i < yEnd; i++)
	{
		for(int j = xStart; j < xEnd; j++)
		{
			SetPixel(j, i, color);
		}
	}
}

void LinuxForms::Texture::DrawFilledCircle(int x, int y, int radius, const Color& color)
{
    if (radius < 0 || x < -radius || y < -radius)
		return;

	if (radius > 0)
	{
		int x0 = 0;
		int y0 = radius;
		int d = 3 - 2 * radius;

		auto drawline = [&](int sx, int ex, int y)
		{
			for (int x = sx; x <= ex; x++)
				SetPixel(x, y, color);
		};

		while (y0 >= x0)
		{
			drawline(x - y0, x + y0, y - x0);
			if (x0 > 0)	drawline(x - y0, x + y0, y + x0);

			if (d < 0)
				d += 4 * x0++ + 6;
			else
			{
				if (x0 != y0)
				{
					drawline(x - x0, x + x0, y - y0);
					drawline(x - x0, x + x0, y + y0);
				}
				d += 4 * (x0++ - y0--) + 10;
			}
		}
	}
	else
		SetPixel(x, y, color);
}



gboolean LinuxForms::Texture::Draw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
	Texture* texture = reinterpret_cast<Texture*>(data);

	if(texture->onDraw != nullptr)
	{
		texture->onDraw(widget, cr, data);
	}
	else
	{		
		if(texture->GetPixels() != nullptr)
		{
			texture->Render(cr, texture->rectangle.x, texture->rectangle.y);
		}
	}	
	
	return false;
}
