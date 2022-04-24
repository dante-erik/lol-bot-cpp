#include "Robot.hpp"
#include "Pixel.hpp"
#include "DirectInputKeyboardScancodes.hpp"

Robot::Robot() {
    ZeroMemory(&mouseInput, sizeof(mouseInput));
    ZeroMemory(&keyboardInput, sizeof(keyboardInput));
    mouseInput.type = INPUT_MOUSE;
    keyboardInput.type = INPUT_KEYBOARD;

    mallocScreenCapVars();
}

Robot::~Robot() {
    //release ScreenCapturing memory
    delete[] screen;
    ReleaseDC(NULL, hdc);
    DeleteObject(hbitmap);
    DeleteDC(cdc);
}

UINT Robot::mallocScreenCapVars() {
    hdc = GetDC(NULL); // get the desktop device context
    cdc = CreateCompatibleDC(hdc); // create a device context to use yourself
    height = (int)GetSystemMetrics(SM_CYSCREEN); // get the width and height of the screen
    width = (int)GetSystemMetrics(SM_CXSCREEN);
    hbitmap = CreateCompatibleBitmap(hdc, width, height); // create a bitmap
    SelectObject(cdc, hbitmap); // use the previously created device context with the bitmap
    bmi = { 0 };
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;
    bmi.biWidth = width;
    bmi.biHeight = -height; // flip image upright
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 3 * width * height;
    screen = new int[width * height];
    return (UINT)0;
}

// Mouse
/**
 * @brief Set the Cursor to a Position
 *
 * @param p position of the cursor after set
 * @return BOOL success or failure
 */
void Robot::setCursorPos(const POINT& p) {
    mouseInput.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    mouseInput.mi.dx = (LONG)(((double)p.x) / width * 65535);
    mouseInput.mi.dy = (LONG)(((double)p.y) / height * 65535);
    SendInput(1, &mouseInput, sizeof(mouseInput));
    mouseInput.mi.dx = 0;
    mouseInput.mi.dy = 0;
}

/**
 * @brief Moves and Presses the Left Mouse Button
 *
 * @param p position of the cursor for the press
 * @return UINT error code
 */
UINT Robot::leftDown(const POINT& p) {
    setCursorPos(p);
    return leftDown();
}

/**
 * @brief Presses the Left Mouse Button
 *
 * @return UINT error code
 */
UINT Robot::leftDown() {
    mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    return SendInput(1, &mouseInput, sizeof(mouseInput));
}

/**
 * @brief Moves and Releases the Left Mouse Button
 *
 * @param p position of the cursor for the release
 * @return UINT error code
 */
UINT Robot::leftUp(const POINT& p) {
    setCursorPos(p);
    return leftUp();
}

/**
 * @brief Releases the Left Mouse Button
 *
 * @return UINT error code
 */
UINT Robot::leftUp() {
    mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    return SendInput(1, &mouseInput, sizeof(mouseInput));
}

/**
 * @brief Moves and Presses the Right Mouse Button
 *
 * @param p position of the cursor for the press
 * @return UINT error code
 */
UINT Robot::rightDown(const POINT& p) {
    setCursorPos(p);
    return rightDown();
}

/**
 * @brief Presses the Right Mouse Button
 *
 * @return UINT error code
 */
UINT Robot::rightDown() {
    mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    return SendInput(1, &mouseInput, sizeof(mouseInput));
}

/**
 * @brief Moves and Releases the Right Mouse Button
 *
 * @param p position of the cursor for the release
 * @return UINT error code
 */
UINT Robot::rightUp(const POINT& p) {
    setCursorPos(p);
    return rightUp();
}

/**
 * @brief Releases the Right Mouse Button
 *
 * @return UINT error code
 */
UINT Robot::rightUp() {
    mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    return SendInput(1, &mouseInput, sizeof(mouseInput));
}

/**
 * @brief Moves and Clicks the Left Mouse Button
 *
 * @param p position of the cursor for the click
 * @param clickDuration milliseconds
 * @return UINT error code
 */
UINT Robot::leftClick(const POINT& p, DWORD clickDuration) {
    leftDown(p);
    Sleep(clickDuration);
    return leftUp();
}

/**
 * @brief Clicks the Left Mouse Button
 *
 * @param clickDuration milliseconds
 * @return UINT error code
 */
UINT Robot::leftClick(DWORD clickDuration) {
    leftDown();
    Sleep(clickDuration);
    return leftUp();
}

/**
 * @brief Moves and Clicks the Right Mouse Button
 *
 * @param p position of the cursor for the click
 * @param clickDuration milliseconds
 * @return UINT error code
 */
UINT Robot::rightClick(const POINT& p, DWORD clickDuration) {
    rightDown(p);
    Sleep(clickDuration);
    return rightUp();
}

/**
 * @brief Clicks the Right Mouse Button
 *
 * @param clickDuration milliseconds
 * @return UINT error code
 */
UINT Robot::rightClick(DWORD clickDuration) {
    rightDown();
    Sleep(clickDuration);
    return rightUp();
}

// Keyboard
/**
* @brief Returns the keyboard scancode from char value
* 
* @param keyStroke character representing the key to press
*/
WORD Robot::getScancode(char keyStroke) {
    return scancode[((int)keyStroke) - 39];
}

/**
 * @brief Presses the last key set
 */
UINT Robot::keyDown() {
    keyboardInput.ki.dwFlags = KEYEVENTF_SCANCODE;
    return SendInput(1, &keyboardInput, sizeof(keyboardInput));
}

/**
 * @brief Presses the provided key
 *
 * @param keyStroke character representing the key to press
 */
UINT Robot::keyDown(char keyStroke) {
    keyboardInput.ki.wScan = getScancode(keyStroke);
    return keyDown();
}

/**
* @brief Releases the last key set
*/
UINT Robot::keyUp() {
    keyboardInput.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    return SendInput(1, &keyboardInput, sizeof(keyboardInput));
}

/**
 * @brief Releases the provided key
 *
 * @param keyStroke character representing the key to release
 */
UINT Robot::keyUp(char keyStroke) {
    keyboardInput.ki.wScan = getScancode(keyStroke);
    return keyUp();
}

/**
 * @brief Clicks (types) the provided key with the duration between each press and release
 *
 * @param keyStroke character representing the key to type
 * @param clickDuration milliseconds between each action
 */
UINT Robot::keyClick(char keyStroke, DWORD clickDuration) {
    keyDown(keyStroke);
    Sleep(clickDuration);
    return keyUp();
}

/**
 * @brief Clicks (types) the provided keys with the duration between each press and release (no additional duration between subsequent characters)
 *
 * @param keyStrokes characters representing the keys to type
 * @param durationBetweenKeyStrokes milliseconds between each action
 */
UINT Robot::keyClick(const char keyStrokes[], DWORD clickDurationForEachKey) {
    //iterate through each keyStroke, can only press up to 65,536 keys per function call
    for (unsigned short index = 0; *(keyStrokes + index) || index == 65535; index++) {
        keyClick(*(keyStrokes + index), clickDurationForEachKey);
    }
    return (UINT)0;
}

/**
 * @brief Presses Left Control, then the provided keyStroke, waits clickDuration milliseconds, then releases the provided keyStroke, and finally releases Left Control
 *
 * @param keyStroke character representing the key to type
 * @param clickDuration milliseconds between each action
 */
UINT Robot::ctrlPlusKeyClick(char keyStroke, DWORD clickDuration) {
    keyboardInput.ki.wScan = DIK_LCONTROL;
    keyDown();

    keyClick(keyStroke, clickDuration);

    keyboardInput.ki.wScan = DIK_LCONTROL;
    return keyUp();
}

/**
 * @brief Presses Left Control, performs keyClick(keystrokes, clickDurationForEachKey), and finally releases Left Control
 *
 * @param keyStrokes character representing the key to type
 * @param clickDurationForEachKey milliseconds between each action
 */
UINT Robot::ctrlPlusKeyClick(const char keyStrokes[], DWORD clickDurationForEachKey) {
    keyboardInput.ki.wScan = DIK_LCONTROL;
    keyDown();

    keyClick(keyStrokes, clickDurationForEachKey);

    keyboardInput.ki.wScan = DIK_LCONTROL;
    return keyUp();
}

/**
* @brief Presses Shift, then the provided keyStroke, waits clickDuration milliseconds, then releases the provided keyStroke, and finally releases Shift
*
* @param keyStrokes character representing the key to type
* @param clickDurationForEachKey milliseconds between each action
*/
UINT Robot::shiftPlusKeyClick(char keyStroke, DWORD clickDuration) {
    keyboardInput.ki.wScan = DIK_LSHIFT;
    keyDown();

    keyClick(keyStroke, clickDuration);

    //ZeroMemory(&keyboardInput.ki.wScan, sizeof(keyboardInput.ki.wScan));

    keyboardInput.ki.wScan = DIK_LSHIFT;
    return keyUp();

    //ZeroMemory(&keyboardInput, sizeof(keyboardInput));
    //keyboardInput.type = INPUT_KEYBOARD;

    //return (UINT)0;
}

/**
* @brief Presses Shift, performs keyClick(keyStrokes, clickDurationForEachKey), and finally releases Shift
*
* @param keyStrokes character representing the key to type
* @param clickDurationForEachKey milliseconds between each action
*/
UINT Robot::shiftPlusKeyClick(const char keyStrokes[], DWORD clickDurationForEachKey) {
    keyboardInput.ki.wScan = DIK_LSHIFT;
    keyDown();

    keyClick(keyStrokes, clickDurationForEachKey);

    keyboardInput.ki.wScan = DIK_LSHIFT;
    keyDown();
    return keyUp();
}

/**
* @brief int to WORD for specific fKey
*
* @param fKey int representing f1 - f12
*/
WORD Robot::getFKey(int fKey) {
    switch (fKey) {
    case 1:
        return DIK_F1;
        break;
    case 2:
        return DIK_F2;
        break;
    case 3:
        return DIK_F3;
        break;
    case 4:
        return DIK_F4;
        break;
    case 5:
        return DIK_F5;
        break;
    case 6:
        return DIK_F6;
        break;
    case 7:
        return DIK_F7;
        break;
    case 8:
        return DIK_F8;
        break;
    case 9:
        return DIK_F9;
        break;
    case 10:
        return DIK_F10;
        break;
    case 11:
        return DIK_F11;
        break;
    case 12:
        return DIK_F12;
        break;
    }
}

/**
* @brief Clicks f1 - f12 based on params
*
* @param fKey f#
* @param clickDuration
*/
UINT Robot::fKeyClick(int fKey, DWORD clickDuration) {
    keyboardInput.ki.wScan = getFKey(fKey);
    keyDown();
    Sleep(clickDuration);
    return keyUp();
}

/**
* @brief Presses down f1 - f12 based on params
*
* @param fKey f#
* @param clickDuration
*/
UINT Robot::fKeyDown(int fKey) {
    keyboardInput.ki.wScan = getFKey(fKey);
    return keyDown();
}

/**
* @brief Releases f1 - f12 based on params
*
* @param fKey f#
* @param clickDuration
*/
UINT Robot::fKeyUp(int fKey) {
    keyboardInput.ki.wScan = getFKey(fKey);
    return keyUp();
}

/**
 * @brief Clicks the Enter Key
 *
 * @param clickDuration milliseconds
 */
UINT Robot::enterKeyClick(DWORD clickDuration) {
    keyboardInput.ki.wScan = DIK_RETURN;
    keyDown();
    Sleep(clickDuration);
    return keyUp();
}

/**
 * @brief Clicks the Escape Key
 *
 * @param clickDuration milliseconds
 */
UINT Robot::escapeKeyClick(DWORD clickDuration) {
    keyboardInput.ki.wScan = DIK_ESCAPE;
    keyDown();
    Sleep(clickDuration);
    return keyUp();
}

UINT Robot::backspaceKeyClick(DWORD clickDuration) {
    keyboardInput.ki.wScan = DIK_BACK;
    keyDown();
    Sleep(clickDuration);
    return keyUp();
}

int Robot::updateScreenBuffer() {
    BitBlt(cdc, 0, 0, width, height, hdc, 0, 0, SRCCOPY | CAPTUREBLT);

    return GetDIBits(cdc, hbitmap, 0, height, screen, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
}

BYTE Robot::getRed(const POINT& p) {
    return (BYTE)((screen[p.x + p.y * width] >> 16) & 255);
}

BYTE Robot::getGreen(const POINT& p) {
    return (BYTE)((screen[p.x + p.y * width] >> 8) & 255);
}

BYTE Robot::getBlue(const POINT& p) {
    return (BYTE)(screen[p.x + p.y * width] & 255);
}

/**
 * @brief Get absolute difference of two unsigned chars
 *
 * @param x byte
 * @param y byte
 * @return difference between x and y
 */
BYTE abs_diff(BYTE x, BYTE y) {
    return x < y ? y - x : x - y;
}

/**
 * @brief Compares the Euclidean Color Distance between the provided Pixel and the Screen Buffer
 *
 * @param pix Pixel to compare to the screen buffer
 * @param tolerance Value at which (or below) the difference is negligible
 * @return BOOL true - close enough; false - different
 */
BOOL Robot::isPixelSimilar(const Pixel& pix, unsigned short tolerance) {
    return (abs_diff(getRed(pix.p), pix.r) + abs_diff(getGreen(pix.p), pix.g) + abs_diff(getBlue(pix.p), pix.b)) <= 3 * tolerance;
}

/**
 * @brief Determines if the provided Pixel matches the Screen Buffer
 *
 * @param pix Pixel to compare to the screen buffer
 * @return BOOL true - equivalent; false - not equivalent
 */
BOOL Robot::isPixelEqual(const Pixel& pix) {
    return (getRed(pix.p) == pix.r) && (getGreen(pix.p) == pix.g) && (getBlue(pix.p) == pix.b);
}