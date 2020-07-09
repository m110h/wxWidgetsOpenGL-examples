// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if !wxUSE_GLCANVAS
    #error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include "cube.h"
#include "testglcanvas.h"

// ----------------------------------------------------------------------------
// MyApp: the application object
// ----------------------------------------------------------------------------

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    new MyFrame();

    return true;
}

int MyApp::OnExit()
{
    return wxApp::OnExit();
}

/*
wxString glGetwxString(GLenum name)
{
    const GLubyte *v = glGetString(name);
    if ( v == 0 )
    {
        // The error is not important. It is GL_INVALID_ENUM.
        // We just want to clear the error stack.
        glGetError();

        return wxString();
    }

    return wxString((const char*)v);
}
*/

// ----------------------------------------------------------------------------
// MyFrame: main application window
// ----------------------------------------------------------------------------

MyFrame::MyFrame(): wxFrame(NULL, wxID_ANY, "wxWidgets OpenGL Cube Sample")
{
    new TestGLCanvas(this);

    MakeMenu();
    CreateStatusBar();

    SetClientSize(400, 400);
    Show();

    // test IsDisplaySupported() function:
    static const int attribs[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };

    wxLogStatus("Double-buffered display %s supported", wxGLCanvas::IsDisplaySupported(attribs) ? "is" : "not");
}

void MyFrame::MakeMenu()
{
    wxMenu *menu = new wxMenu;

    menu->Append(MY_ID_NEW, wxT("&New\tCtrl+n"));
    menu->AppendSeparator();
    menu->Append(MY_ID_CLOSE, wxT("&Close\tCtrl+w"));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menu, "&Cube");

    SetMenuBar(menuBar);

    menuBar->Bind(wxEVT_MENU, [&](wxCommandEvent& event) {
        switch (event.GetId())
        {
            case MY_ID_NEW:
                OnNewWindow(event);
                break;
            case MY_ID_CLOSE:
                OnClose(event);
                break;
            default:
                break;
        }
    });
}

void MyFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnNewWindow( wxCommandEvent& WXUNUSED(event) )
{
    new MyFrame();
}
