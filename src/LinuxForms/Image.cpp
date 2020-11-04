#include "Image.h"
#include <iostream>
#include <cstring>

LinuxForms::Image::Image()
{
	//onDraw = nullptr;
	pixels = nullptr;
	widget = gtk_fixed_new();
}

LinuxForms::Image::Image(const std::string& filepath)
{
	//onDraw = nullptr;
	pixels = nullptr;
	widget = gtk_fixed_new();	
	LoadFromFile(filepath);
}

LinuxForms::Image::~Image()
{
	Dispose();
}

void LinuxForms::Image::Dispose()
{	
	if(pixels != nullptr)
	{
		g_object_unref(pixels);
		pixels = nullptr;
	}
}

bool LinuxForms::Image::LoadFromFile(const std::string& filepath)
{
	Dispose();

	GError* err = NULL;
	pixels = gdk_pixbuf_new_from_file(filepath.c_str(), &err);	
	
	if(err)
	{
		pixels = nullptr;
		std::cout << "Couldn't load image " << err->message << "\n";
		return false;
	}
	else
	{	
		rectangle.width = gdk_pixbuf_get_width(pixels);
		rectangle.height = gdk_pixbuf_get_height(pixels);
		pixels = gdk_pixbuf_scale_simple(pixels, rectangle.width, rectangle.height, GDK_INTERP_BILINEAR);
		format = ImageFormat::FromPixbuf(pixels);
		gtk_widget_set_size_request(widget, rectangle.width, rectangle.height);
		signalID["draw"] = g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);		
		return true;
	}	
}

void LinuxForms::Image::SetPosition(int x, int y)
{
	this->rectangle.x = x;
	this->rectangle.y = y;
}

void LinuxForms::Image::Render(cairo_t* cr, int x, int y)
{
	if(pixels == nullptr)
		return;
		
	rectangle.x = x;
	rectangle.y = y;
	
	gdk_cairo_set_source_pixbuf(cr, pixels, x, y);	
    cairo_paint(cr);
}

void LinuxForms::Image::SetPixel(int x, int y, const Color& color)
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

gboolean LinuxForms::Image::Draw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
	Image* image = reinterpret_cast<Image*>(data);

	if(image->onDraw != nullptr)
	{
		image->onDraw(widget, cr, data);
	}
	else
	{		
		if(image->GetPixels() != nullptr)
		{
			image->Render(cr, image->rectangle.x, image->rectangle.y);
		}
	}	
	
	return false;
}