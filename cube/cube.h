#ifndef _WX_CUBE_H_
#define _WX_CUBE_H_

class MyApp : public wxApp
{
public:
    MyApp() {}

    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;
};

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnClose(wxCommandEvent& event);
    void OnNewWindow(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // _WX_CUBE_H_
