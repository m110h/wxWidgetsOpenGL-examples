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

    enum {
        MY_ID_NEW,
        MY_ID_CLOSE
    };

private:
    void MakeMenu();

    void OnClose(wxCommandEvent& event);
    void OnNewWindow(wxCommandEvent& event);
};

#endif // _WX_CUBE_H_
