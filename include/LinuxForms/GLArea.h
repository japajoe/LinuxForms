#ifndef GLAREA_HPP
#define GLAREA_HPP

#include "Widget.h"

namespace LinuxForms
{
    class GLArea : public Widget
    {
    public:
        GLArea();
        EventHandler<GLAreaRenderEvent> onRender;
        EventHandler<GLAreaRealizeEvent> onRealize;
        EventHandler<GLAreaUnRealizeEvent> onUnRealize;
        EventHandler<MouseMoveEvent> onMouseMove;
        EventHandler<GLAreaResizeEvent> onResize;
        void SwapBuffers();
        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
        void SetSize(int width, int height);
    private:
        int width;
        int height;
        static gboolean OnGLAreaRender(GtkGLArea* area, GdkGLContext* context, gpointer data);
        static void OnGLAreaRealize(GtkGLArea* area, gpointer data);
        static void OnGLAreaUnRealize(GtkGLArea* area, gpointer data);
        static void OnMouseMove(GtkWidget* widget, GdkEventMotion* event, gpointer data);
        static void OnResize(GtkGLArea* area, int width, int height, gpointer data);
    };
}
#endif
