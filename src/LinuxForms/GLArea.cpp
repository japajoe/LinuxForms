#include "GLArea.h"
#include "LinuxForms/Utility/Console.h"

namespace LinuxForms
{
    GLArea::GLArea()
    {
        widget = gtk_gl_area_new();

        GdkGLContext* context = gtk_gl_area_get_context(GTK_GL_AREA(widget));

        if(gtk_gl_area_get_error(GTK_GL_AREA(widget)) != NULL)
        {            
            Console::WriteLine("Couldn't create GLArea");
        }
        else
        {
	        gtk_widget_add_events(widget, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);
            g_signal_connect(widget, "realize", G_CALLBACK(OnGLAreaRealize), this);
            g_signal_connect(widget, "unrealize", G_CALLBACK(OnGLAreaUnRealize), this);
            g_signal_connect(widget, "render", G_CALLBACK(OnGLAreaRender), this);
            g_signal_connect(widget, "motion-notify-event", G_CALLBACK(OnMouseMove), this);
            g_signal_connect(widget, "resize", G_CALLBACK(OnResize), this);
        }
    }  

    void GLArea::SwapBuffers()
    {
        gtk_gl_area_queue_render(GTK_GL_AREA(widget));
    }

    void GLArea::SetSize(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    gboolean GLArea::OnGLAreaRender(GtkGLArea* area, GdkGLContext* context, gpointer data)
    {
        GLArea* glArea = reinterpret_cast<GLArea*>(data);

        if(glArea->onRender != nullptr)
            glArea->onRender(area, context, data);
        return true;
    }

    void GLArea::OnGLAreaRealize(GtkGLArea* area, gpointer data)
    {
        GLArea* glArea = reinterpret_cast<GLArea*>(data);
        if(glArea->onRealize != nullptr)
            glArea->onRealize(area, data);
    }
    
    void GLArea::OnGLAreaUnRealize(GtkGLArea* area, gpointer data)
    {
        GLArea* glArea = reinterpret_cast<GLArea*>(data);
        if(glArea->onUnRealize != nullptr)
            glArea->onUnRealize(area, data);
    }
    
    void GLArea::OnMouseMove(GtkWidget* widget, GdkEventMotion* event, gpointer data)
    {
        GLArea* glArea = reinterpret_cast<GLArea*>(data);
        if(glArea->onMouseMove != nullptr)
            glArea->onMouseMove(widget, event, data);
    }
    
    void GLArea::OnResize(GtkGLArea* area, int width, int height, gpointer data)
    {
        GLArea* glArea = reinterpret_cast<GLArea*>(data);
        glArea->SetSize(width, height);
         if(glArea->onResize != nullptr)
             glArea->onResize(area, width, height, data);
    }
}
