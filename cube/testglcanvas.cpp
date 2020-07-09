#include "testglcanvas.h"
#include "testglcontext_singleton.h"

TestGLCanvas::TestGLCanvas(wxWindow *parent)
    // With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
    // flag should always be set, because even making the canvas smaller should
    // be followed by a paint event that updates the entire canvas with new
    // viewport settings.
    : wxGLCanvas(parent, wxID_ANY, NULL, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    this->Bind(wxEVT_PAINT, [&](wxPaintEvent& event){
        OnPaint(event);
    });

    this->Bind(wxEVT_KEY_DOWN, [&](wxKeyEvent& event){
        OnKeyDown(event);
    });

    m_spinTimer.Bind(wxEVT_TIMER, [&](wxTimerEvent& event) {
        OnSpinTimer(event);
    });
}

void TestGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    // This is required even though dc is not used otherwise.
    wxPaintDC dc(this);

    // Set the OpenGL viewport according to the client size of this canvas.
    // This is done here rather than in a wxSizeEvent handler because our
    // OpenGL rendering context (and thus viewport setting) is used with
    // multiple canvases: If we updated the viewport in the wxSizeEvent
    // handler, changing the size of one canvas causes a viewport setting that
    // is wrong when next another canvas is repainted.
    const wxSize ClientSize = GetClientSize() * GetContentScaleFactor();

    glViewport(0, 0, ClientSize.x, ClientSize.y);

    TestGLContext& canvas = TestGLContextSingleton::GetInstance().GetContext(this);
    canvas.DrawRotatedCube(m_xangle, m_yangle);

    SwapBuffers();
}

void TestGLCanvas::OnKeyDown(wxKeyEvent& event)
{
    float angle = 5.0;

    switch ( event.GetKeyCode() )
    {
        case WXK_RIGHT:
            Spin( 0.0, -angle );
            //wxLogError("KEY_RIGHT");
            break;

        case WXK_LEFT:
            Spin( 0.0, angle );
            //wxLogError("KEY_LEFT");
            break;

        case WXK_DOWN:
            Spin( -angle, 0.0 );
            break;

        case WXK_UP:
            Spin( angle, 0.0 );
            break;

        case WXK_SPACE:
            if ( m_spinTimer.IsRunning() )
                m_spinTimer.Stop();
            else
                m_spinTimer.Start( 30 );
            break;

        default:
            event.Skip();
            return;
    }
}

void TestGLCanvas::OnSpinTimer(wxTimerEvent& WXUNUSED(event))
{
    Spin(0.0, 4.0);
}

void TestGLCanvas::Spin(float xSpin, float ySpin)
{
    m_xangle += xSpin;
    m_yangle += ySpin;

    Refresh(false);
}
