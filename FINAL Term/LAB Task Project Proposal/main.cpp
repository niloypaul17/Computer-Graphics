#include <windows.h>

// ---------------------------
// Utility Functions
// ---------------------------

// Draw circle
void drawCircle(HDC hdc, int x, int y, int r, COLORREF color)
{
    HBRUSH brush = CreateSolidBrush(color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

    Ellipse(hdc, x - r, y - r, x + r, y + r);

    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}

// Draw cloud
void drawCloud(HDC hdc, int x, int y)
{
    drawCircle(hdc, x, y, 28, RGB(255, 255, 255));
    drawCircle(hdc, x + 32, y + 12, 24, RGB(255, 255, 255));
    drawCircle(hdc, x - 32, y + 12, 24, RGB(255, 255, 255));
}

// Draw a bird (simple V shape)
void drawBird(HDC hdc, int x, int y)
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(30, 30, 30));
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + 15, y + 5);
    MoveToEx(hdc, x + 15, y + 5, NULL);
    LineTo(hdc, x + 30, y);

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

// Draw a simple airplane
void drawAirplane(HDC hdc, int x, int y)
{
    HBRUSH planeBody = CreateSolidBrush(RGB(120, 180, 255));
    HBRUSH old = (HBRUSH)SelectObject(hdc, planeBody);

    Rectangle(hdc, x - 50, y - 10, x + 20, y + 10);  // body
    Rectangle(hdc, x - 20, y - 25, x - 5, y - 10);  // top wing
    Rectangle(hdc, x - 20, y + 10, x - 5, y + 25);  // bottom wing

    SelectObject(hdc, old);
    DeleteObject(planeBody);

    drawCircle(hdc, x + 20, y, 10, RGB(255, 80, 80)); // nose
}

// Draw a simple tree
void drawTree(HDC hdc, int x, int y)
{
    // trunk
    HBRUSH trunk = CreateSolidBrush(RGB(120, 70, 30));
    RECT r1 = { x - 10, y, x + 10, y + 40 };
    FillRect(hdc, &r1, trunk);
    DeleteObject(trunk);

    // leaves
    drawCircle(hdc, x, y - 20, 25, RGB(34, 139, 34));
}

// Draw house
void drawHouse(HDC hdc, int x, int y)
{
    // house base
    HBRUSH wall = CreateSolidBrush(RGB(210, 180, 140));
    RECT r = { x, y, x + 90, y + 60 };
    FillRect(hdc, &r, wall);
    DeleteObject(wall);

    // roof
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(150, 50, 50));
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    HBRUSH roof = CreateSolidBrush(RGB(150, 50, 50));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, roof);

    POINT pts[3] = { {x, y}, {x + 45, y - 35}, {x + 90, y} };
    Polygon(hdc, pts, 3);

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    DeleteObject(roof);
}

// Draw building with windows
void drawBuilding(HDC hdc, int x, int w, int h)
{
    // building
    HBRUSH b = CreateSolidBrush(RGB(60, 60, 90));
    RECT rect = { x, 400 - h, x + w, 400 };
    FillRect(hdc, &rect, b);
    DeleteObject(b);

    // windows
    HBRUSH winOn = CreateSolidBrush(RGB(255, 255, 120));
    int row, col;

    for (row = 400 - h + 10; row < 400 - 10; row += 25)
    {
        for (col = x + 8; col < x + w - 10; col += 22)
        {
            RECT wRect = { col, row, col + 15, row + 15 };
            FillRect(hdc, &wRect, winOn);
        }
    }

    DeleteObject(winOn);
}

// Draw full background
void drawScene(HDC hdc)
{
    // Sky
    RECT sky = { 0, 0, 800, 400 };
    HBRUSH skyB = CreateSolidBrush(RGB(135, 206, 250));
    FillRect(hdc, &sky, skyB);
    DeleteObject(skyB);

    // Sun
    drawCircle(hdc, 700, 80, 40, RGB(255, 220, 0));

    // Clouds
    drawCloud(hdc, 150, 120);
    drawCloud(hdc, 350, 90);
    drawCloud(hdc, 550, 130);

    // Birds
    drawBird(hdc, 200, 160);
    drawBird(hdc, 250, 180);
    drawBird(hdc, 480, 150);

    // Airplane
    drawAirplane(hdc, 300, 250);

    // Buildings
    drawBuilding(hdc, 50, 80, 140);
    drawBuilding(hdc, 150, 100, 180);
    drawBuilding(hdc, 280, 70, 160);
    drawBuilding(hdc, 380, 90, 200);
    drawBuilding(hdc, 500, 110, 170);
    drawBuilding(hdc, 640, 90, 150);

    // Houses
    drawHouse(hdc, 70, 420);
    drawHouse(hdc, 200, 420);

    // Trees
    drawTree(hdc, 350, 420);
    drawTree(hdc, 430, 420);
    drawTree(hdc, 520, 420);

    // Road base
    RECT road = { 0, 480, 800, 600 };
    HBRUSH roadBrush = CreateSolidBrush(RGB(40, 40, 40));
    FillRect(hdc, &road, roadBrush);
    DeleteObject(roadBrush);

    // Road lane stripes
    HPEN stripePen = CreatePen(PS_SOLID, 6, RGB(255, 255, 255));
    HPEN oldP = (HPEN)SelectObject(hdc, stripePen);

    int i;
    for (i = 0; i < 800; i += 80)
    {
        MoveToEx(hdc, i, 540, NULL);
        LineTo(hdc, i + 40, 540);
    }

    SelectObject(hdc, oldP);
    DeleteObject(stripePen);
}

// ---------------------------
// Win32 Boilerplate
// ---------------------------

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        drawScene(hdc);

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    const char CLASS_NAME[] = "BGWindow";

    WNDCLASS wc = { };
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = WindowProcedure;

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        CLASS_NAME,
        "Flight Dash Static Background",
        WS_OVERLAPPEDWINDOW,
        200, 80, 800, 600,
        NULL, NULL, hInst, NULL
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
