/*
 * Лабораторная работа №1 - Базовое OpenGL приложение
 * Демонстрация создания окна Win32 и отрисовки примитивов с помощью OpenGL
 */

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

// Глобальные переменные
HGLRC hRC = NULL;       // Rendering Context
HDC hDC = NULL;         // Device Context
HWND hWnd = NULL;       // Handle окна
HINSTANCE hInstance;    // Instance приложения

bool keys[256];         // Массив для хранения состояния клавиш
bool active = TRUE;     // Флаг активности окна
bool fullscreen = FALSE; // Режим полного экрана

// Прототипы функций
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
 * Функция изменения размера окна OpenGL
 */
GLvoid ResizeGLScene(GLsizei width, GLsizei height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Установка перспективы
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Инициализация OpenGL
 */
int InitGL(GLvoid)
{
    glShadeModel(GL_SMOOTH);                    // Включение плавного закрашивания
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);      // Черный фон
    glClearDepth(1.0f);                         // Установка буфера глубины
    glEnable(GL_DEPTH_TEST);                    // Включение теста глубины
    glDepthFunc(GL_LEQUAL);                     // Тип теста глубины
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Улучшенные вычисления перспективы

    return TRUE;
}

/*
 * Функция отрисовки сцены
 */
int DrawGLScene(GLvoid)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Очистка экрана и буфера глубины
    glLoadIdentity();                                    // Сброс матрицы

    // ===== Рисуем треугольник =====
    glTranslatef(-1.5f, 0.0f, -6.0f);  // Сдвиг влево и вглубь экрана

    glBegin(GL_TRIANGLES);             // Начало рисования треугольника
        // Верхняя вершина (красная)
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        
        // Левая нижняя вершина (зеленая)
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        
        // Правая нижняя вершина (синяя)
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();                           // Конец рисования треугольника

    // ===== Рисуем квадрат =====
    glTranslatef(3.0f, 0.0f, 0.0f);    // Сдвиг вправо (относительно текущей позиции)

    glColor3f(0.5f, 0.5f, 1.0f);       // Голубой цвет для квадрата
    glBegin(GL_QUADS);                 // Начало рисования квадрата
        glVertex3f(-1.0f, 1.0f, 0.0f);  // Верхняя левая вершина
        glVertex3f(1.0f, 1.0f, 0.0f);   // Верхняя правая вершина
        glVertex3f(1.0f, -1.0f, 0.0f);  // Нижняя правая вершина
        glVertex3f(-1.0f, -1.0f, 0.0f); // Нижняя левая вершина
    glEnd();                            // Конец рисования квадрата

    return TRUE;
}

/*
 * Освобождение ресурсов OpenGL
 */
GLvoid KillGLWindow(GLvoid)
{
    if (fullscreen)
    {
        ChangeDisplaySettings(NULL, 0);
        ShowCursor(TRUE);
    }

    if (hRC)
    {
        if (!wglMakeCurrent(NULL, NULL))
        {
            MessageBox(NULL, "Ошибка освобождения DC и RC.", "Ошибка", MB_OK | MB_ICONINFORMATION);
        }

        if (!wglDeleteContext(hRC))
        {
            MessageBox(NULL, "Ошибка освобождения Rendering Context.", "Ошибка", MB_OK | MB_ICONINFORMATION);
        }
        hRC = NULL;
    }

    if (hDC && !ReleaseDC(hWnd, hDC))
    {
        MessageBox(NULL, "Ошибка освобождения Device Context.", "Ошибка", MB_OK | MB_ICONINFORMATION);
        hDC = NULL;
    }

    if (hWnd && !DestroyWindow(hWnd))
    {
        MessageBox(NULL, "Ошибка уничтожения окна.", "Ошибка", MB_OK | MB_ICONINFORMATION);
        hWnd = NULL;
    }

    if (!UnregisterClass("OpenGL", hInstance))
    {
        MessageBox(NULL, "Ошибка отмены регистрации класса.", "Ошибка", MB_OK | MB_ICONINFORMATION);
        hInstance = NULL;
    }
}

/*
 * Создание окна OpenGL
 */
BOOL CreateGLWindow(const char* title, int width, int height, int bits, bool fullscreenflag)
{
    GLuint PixelFormat;
    WNDCLASS wc;
    DWORD dwExStyle;
    DWORD dwStyle;

    RECT WindowRect;
    WindowRect.left = (long)0;
    WindowRect.right = (long)width;
    WindowRect.top = (long)0;
    WindowRect.bottom = (long)height;

    fullscreen = fullscreenflag;

    hInstance = GetModuleHandle(NULL);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "OpenGL";

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Ошибка регистрации класса окна.", "Ошибка", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (fullscreen)
    {
        DEVMODE dmScreenSettings;
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = width;
        dmScreenSettings.dmPelsHeight = height;
        dmScreenSettings.dmBitsPerPel = bits;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            if (MessageBox(NULL, "Полноэкранный режим не поддерживается.\nИспользовать оконный режим?", "Ошибка", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
            {
                fullscreen = FALSE;
            }
            else
            {
                MessageBox(NULL, "Программа будет закрыта.", "Ошибка", MB_OK | MB_ICONSTOP);
                return FALSE;
            }
        }
    }

    if (fullscreen)
    {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP;
        ShowCursor(FALSE);
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle = WS_OVERLAPPEDWINDOW;
    }

    AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

    if (!(hWnd = CreateWindowEx(dwExStyle,
        "OpenGL",
        title,
        dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        0, 0,
        WindowRect.right - WindowRect.left,
        WindowRect.bottom - WindowRect.top,
        NULL,
        NULL,
        hInstance,
        NULL)))
    {
        KillGLWindow();
        MessageBox(NULL, "Ошибка создания окна.", "Ошибка", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        bits,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        16,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    if (!(hDC = GetDC(hWnd)))
    {
        KillGLWindow();
        MessageBox(NULL, "Ошибка создания Device Context.", "Ошибка", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
    {
        KillGLWindow();
        MessageBox(NULL, "Ошибка выбора формата пикселя.", "Ошибка", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!SetPixelFormat(hDC, PixelFormat, &pfd))
    {
        KillGLWindow();
        MessageBox(NULL, "Ошибка установки формата пикселя.", "Ошибка", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!(hRC = wglCreateContext(hDC)))
    {
        KillGLWindow();
        MessageBox(NULL, "Ошибка создания Rendering Context.", "Ошибка", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!wglMakeCurrent(hDC, hRC))
    {
        KillGLWindow();
        MessageBox(NULL, "Ошибка активации Rendering Context.", "Ошибка", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    ShowWindow(hWnd, SW_SHOW);
    SetForegroundWindow(hWnd);
    SetFocus(hWnd);
    ResizeGLScene(width, height);

    if (!InitGL())
    {
        KillGLWindow();
        MessageBox(NULL, "Ошибка инициализации OpenGL.", "Ошибка", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    return TRUE;
}

/*
 * Обработчик сообщений Windows
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_ACTIVATE:
        {
            if (!HIWORD(wParam))
            {
                active = TRUE;
            }
            else
            {
                active = FALSE;
            }
            return 0;
        }

        case WM_SYSCOMMAND:
        {
            switch (wParam)
            {
                case SC_SCREENSAVE:
                case SC_MONITORPOWER:
                    return 0;
            }
            break;
        }

        case WM_CLOSE:
        {
            PostQuitMessage(0);
            return 0;
        }

        case WM_KEYDOWN:
        {
            keys[wParam] = TRUE;
            return 0;
        }

        case WM_KEYUP:
        {
            keys[wParam] = FALSE;
            return 0;
        }

        case WM_SIZE:
        {
            ResizeGLScene(LOWORD(lParam), HIWORD(lParam));
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*
 * Главная функция программы
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL done = FALSE;

    // Создание окна OpenGL
    if (!CreateGLWindow("Лабораторная работа №1 - OpenGL", 800, 600, 32, fullscreen))
    {
        return 0;
    }

    // Главный цикл программы
    while (!done)
    {
        // Обработка сообщений
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                done = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // Отрисовка сцены
            if (active)
            {
                if (keys[VK_ESCAPE])
                {
                    done = TRUE;
                }
                else
                {
                    DrawGLScene();
                    SwapBuffers(hDC);
                }
            }
        }
    }

    // Завершение работы
    KillGLWindow();
    return (msg.wParam);
}
