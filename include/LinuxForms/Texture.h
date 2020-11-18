#ifndef TEXTURE_HPP
#define TEXTURE_HPP

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

	class Texture : public Widget
	{
	public:
		Texture();
		Texture(const std::string& filepath);
		Texture(int width, int height, bool hasAlpha = true);
		~Texture();
		void Dispose();
		bool LoadFromFile(const std::string& filepath);
		bool LoadFromData(int width, int height, bool hasAlpha = true);
		void SetPosition(int x, int y);
		void Render(cairo_t* cr, int x, int y);
        GdkPixbuf* GetPixelBuffer() const;
        void SetPixelBuffer(GdkPixbuf* buffer);
        Color GetPixel(int x, int y);
		void SetPixel(int x, int y, const Color& color);
		void Clear(const Color& color = { 0.0f, 0.0f, 0.0f, 1.0f });
		void SetScale(float x, float y);
		void DrawLine(int x1, int y1, int x2, int y2, const Color& color);
		void DrawRectangle(int x, int y, int width, int height, const Color& color);
        void DrawFilledCircle(int x, int y, int radius, const Color& color);
		GdkPixbuf* GetPixels() const { return pixels; }
		ImageFormat format;
		EventHandler<DrawEvent> onDraw;
	private:
		GdkPixbuf* pixels;
		guint8* buffer;
		static gboolean Draw(GtkWidget* widget, cairo_t* cr, gpointer data);
	};
}
#endif
