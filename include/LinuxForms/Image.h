#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Widget.h"
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <cairo.h>
#include <string>

namespace LinuxForms
{
	struct ImageFormat
	{
		GdkColorspace colorSpace;
		int channels;
		int bitsPerSample;
		bool hasAlpha;
		int width;
		int height;
		int rowStride;

		static ImageFormat FromPixbuf(const GdkPixbuf* pixels)
		{
			GdkColorspace colorSpace = gdk_pixbuf_get_colorspace(pixels);
			int channels = gdk_pixbuf_get_n_channels(pixels);
			int bitsPerSample = gdk_pixbuf_get_bits_per_sample(pixels);
			bool hasAlpha = gdk_pixbuf_get_has_alpha(pixels);			
			int width = gdk_pixbuf_get_width(pixels);
			int height = gdk_pixbuf_get_height(pixels);
			int rowStride = gdk_pixbuf_get_rowstride(pixels);

			return { colorSpace, channels, bitsPerSample, hasAlpha, width, height, rowStride };
		}
	};

	class Image : public Widget
	{
	public:
		Image();
		Image(const std::string& filepath);
		~Image();
		void Dispose();
		bool LoadFromFile(const std::string& filepath);
		void SetPosition(int x, int y);
		void Render(cairo_t* cr, int x, int y);
		void SetPixel(int x, int y, const Color& color);
		void Clear(const Color& color = { 0.0f, 0.0f, 0.0f, 1.0f });
		GdkPixbuf* GetPixels() const { return pixels; }
		ImageFormat format;
		EventHandler<DrawEvent> onDraw;
	private:
		GdkPixbuf* pixels;
		static gboolean Draw(GtkWidget* widget, cairo_t* cr, gpointer data);
	};
}
#endif