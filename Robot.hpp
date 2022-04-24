#pragma once
#include <Windows.h>
#include "Pixel.hpp"
#include <d3d9.h>

class Robot
{
private:
    //for mouse and keybord simulation using SendInput()
    INPUT mouseInput;
    INPUT keyboardInput;

    //for screen capturing using BitBlt()
    HDC hdc; // get the desktop device context
    HDC cdc; // create a device context to use yourself
    int height; // get the width and height of the screen
    int width; // only capture left monitor for dual screen setups, for both screens use (int)GetSystemMetrics(SM_CXVIRTUALSCREEN);
    HBITMAP hbitmap; // create a bitmap
    BITMAPINFOHEADER bmi;
    int* screen;

public:
    Robot();
    ~Robot();

    UINT mallocScreenCapVars();

    /**
     * @brief Get scancode from char
     *
     * @param char keyStroke translated to scancode
     * @return WORD scancode
     */
    WORD getScancode(char keyStroke);

    // Mouse
    /**
     * @brief Set the Cursor to a Position
     *
     * @param p position of the cursor after set
     * @return BOOL success or failure
     */
    void setCursorPos(const POINT& p);

    /**
     * @brief Moves and Presses the Left Mouse Button
     *
     * @param p position of the cursor for the press
     * @return UINT error code
     */
    UINT leftDown(const POINT& p);

    /**
     * @brief Presses the Left Mouse Button
     *
     * @return UINT error code
     */
    UINT leftDown();

    /**
     * @brief Moves and Releases the Left Mouse Button
     *
     * @param p position of the cursor for the release
     * @return UINT error code
     */
    UINT leftUp(const POINT& p);

    /**
     * @brief Releases the Left Mouse Button
     *
     * @return UINT error code
     */
    UINT leftUp();

    /**
     * @brief Moves and Presses the Right Mouse Button
     *
     * @param p position of the cursor for the press
     * @return UINT error code
     */
    UINT rightDown(const POINT& p);

    /**
     * @brief Presses the Right Mouse Button
     *
     * @return UINT error code
     */
    UINT rightDown();

    /**
     * @brief Moves and Releases the Right Mouse Button
     *
     * @param p position of the cursor for the release
     * @return UINT error code
     */
    UINT rightUp(const POINT& p);

    /**
     * @brief Releases the Right Mouse Button
     *
     * @return UINT error code
     */
    UINT rightUp();

    /**
     * @brief Moves and Clicks the Left Mouse Button
     *
     * @param p position of the cursor for the click
     * @param clickDuration milliseconds
     * @return UINT error code
     */
    UINT leftClick(const POINT& p, DWORD clickDuration = 0);

    /**
     * @brief Clicks the Left Mouse Button
     *
     * @param clickDuration milliseconds
     * @return UINT error code
     */
    UINT leftClick(DWORD clickDuration = 0);

    /**
     * @brief Moves and Clicks the Right Mouse Button
     *
     * @param p position of the cursor for the click
     * @param clickDuration milliseconds
     * @return UINT error code
     */
    UINT rightClick(const POINT& p, DWORD clickDuration = 0);

    /**
     * @brief Clicks the Right Mouse Button
     *
     * @param clickDuration milliseconds
     * @return UINT error code
     */
    UINT rightClick(DWORD clickDuration = 0);

    // Keyboard
    /**
    * @brief Presses down the last key set
    */
    UINT keyDown();

    /**
     * @brief Presses the provided key
     *
     * @param keyStroke character representing the key to press
     */
    UINT keyDown(char keyStroke);

    /**
    * @brief Releases the last key set
    */
    UINT keyUp();

    /**
     * @brief Releases the provided key
     *
     * @param keyStroke character representing the key to release
     */
    UINT keyUp(char keyStroke);

    /**
     * @brief Clicks (types) the provided key with the duration between each press and release
     *
     * @param keyStroke character representing the key to type
     * @param clickDuration milliseconds between each action
     */
    UINT keyClick(char keyStroke, DWORD clickDuration = 0);

    /**
     * @brief Clicks (types) the provided keys with the duration between each press and release (no additional duration between subsequent characters)
     *
     * @param keyStrokes characters representing the keys to type
     * @param durationBetweenKeyStrokes milliseconds between each action
     */
    UINT keyClick(const char keyStrokes[], DWORD clickDurationForEachKey = 0);

    /**
     * @brief Presses Left Control, then the provided keyStroke, waits clickDuration milliseconds, then releases the provided keyStroke, and finally releases Left Control
     *
     * @param keyStroke character representing the key to type
     * @param clickDuration milliseconds between each action
     */
    UINT ctrlPlusKeyClick(char keyStroke, DWORD clickDuration = 0);

    /**
     * @brief Presses Left Control, performs keyClick(keyStrokes, clickDurationForEachKey), and finally releases Left Control
     *
     * @param keyStrokes character representing the key to type
     * @param clickDurationForEachKey milliseconds between each action
     */
    UINT ctrlPlusKeyClick(const char keyStrokes[], DWORD clickDurationForEachKey = 0);

    /**
    * @brief Presses Shift, then the provided keyStroke, waits clickDuration milliseconds, then releases the provided keyStroke, and finally releases Shift
    *
    * @param keyStrokes character representing the key to type
    * @param clickDurationForEachKey milliseconds between each action
    */
    UINT shiftPlusKeyClick(char keyStroke, DWORD clickDuration = 0);

    /**
    * @brief Presses Shift, performs keyClick(keyStrokes, clickDurationForEachKey), and finally releases Shift
    *
    * @param keyStrokes character representing the key to type
    * @param clickDurationForEachKey milliseconds between each action
    */
    UINT shiftPlusKeyClick(const char keyStrokes[], DWORD clickDurationForEachKey = 0);

    /**
    * @brief int to WORD for specific fKey
    *
    * @param fKey int representing f1 - f12
    */
    WORD getFKey(int fKey);

    /**
    * @brief Clicks f1, f2, f3, f4, f5 based on params
    *
    * @param fKey f#
    * @param clickDuration
    */
    UINT fKeyClick(int fKey, DWORD clickDuration = 0);

    /**
    * @brief Presses down f1 - f12 based on params
    *
    * @param fKey f#
    * @param clickDuration
    */
    UINT fKeyDown(int fKey);

    /**
    * @brief Releases f1 - f12 based on params
    *
    * @param fKey f#
    * @param clickDuration
    */
    UINT fKeyUp(int fKey);

    /**
     * @brief Clicks the Enter Key
     *
     * @param clickDuration milliseconds
     */
    UINT enterKeyClick(DWORD clickDuration = 0);

    /**
     * @brief Clicks the Escape Key
     *
     * @param clickDuration milliseconds
     */
    UINT escapeKeyClick(DWORD clickDuration = 0);

    UINT backspaceKeyClick(DWORD clickDuration = 0);


    // Reader

    int updateScreenBuffer();

    BYTE getRed(const POINT& p);

    BYTE getGreen(const POINT& p);

    BYTE getBlue(const POINT& p);

    /**
     * @brief Compares the Euclidean Color Distance between the provided Pixel and the Screen Buffer
     *
     * @param pix Pixel to compare to the screen buffer
     * @param tolerance Value at which (or below) the difference is negligible
     * @return BOOL true - close enough; false - different
     */
    BOOL isPixelSimilar(const Pixel& pix, unsigned short tolerance = 0.1);

    /**
     * @brief Determines if the provided Pixel matches the Screen Buffer
     *
     * @param pix Pixel to compare to the screen buffer
     * @return BOOL true - equivalent; false - not equivalent
     */
    BOOL isPixelEqual(const Pixel& pix);
};