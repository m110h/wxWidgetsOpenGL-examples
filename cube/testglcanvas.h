#ifndef _TEST_GL_CANVAS_H_
#define _TEST_GL_CANVAS_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/glcanvas.h"

class TestGLCanvas : public wxGLCanvas
{
public:
    TestGLCanvas(wxWindow *parent);

private:
    void OnPaint(wxPaintEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnSpinTimer(wxTimerEvent& WXUNUSED(event));

    void Spin(float xSpin, float ySpin);

    // angles of rotation around x- and y- axis
    float m_xangle;
    float m_yangle;

    wxTimer m_spinTimer;

    wxDECLARE_EVENT_TABLE();
};

#endif
