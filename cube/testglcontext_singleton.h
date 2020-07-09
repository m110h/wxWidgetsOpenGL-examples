#ifndef _TEST_GL_CONTEXT_SINGLETON_H_
#define _TEST_GL_CONTEXT_SINGLETON_H_

#include "testglcontext.h"

class TestGLContextSingleton
{
public:
    TestGLContextSingleton(const TestGLContextSingleton& src) = delete;

    ~TestGLContextSingleton()
    {
        if (m_glContext)
            delete m_glContext;
    }

    // Returns the shared context used by all frames and sets it as current for
    // the given canvas.
    TestGLContext& GetContext(wxGLCanvas *canvas)
    {
        TestGLContext *glContext;

        if ( !m_glContext )
        {
            // Create the OpenGL context for the first mono window which needs it:
            // subsequently created windows will all share the same context.
            m_glContext = new TestGLContext(canvas);
        }

        glContext = m_glContext;

        glContext->SetCurrent(*canvas);

        return *glContext;
    }

    // Singleton Мэйерса
    static TestGLContextSingleton& GetInstance()
    {
        static TestGLContextSingleton _instance;
        return _instance;
    }

private:
    TestGLContextSingleton() {}

private:
    // the GL context we use for all our mono rendering windows
    TestGLContext *m_glContext {NULL};
};


#endif
