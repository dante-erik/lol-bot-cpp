#include <iostream>
#include <limits>
#include <string>
#include <Windows.h>

// Defines to make code pretty
#define seconds *1000
#define forever for(;;)

// Generic function to run in thread
// create a struct to pass to the function or use a single builtin type because LPVOID = void*
DWORD WINAPI foo(LPVOID);

int main() {
    // Input from User
    std::string input;
    std::cout << "String to print: ";
    std::getline(std::cin, input);
    DOUBLE sleep;
    std::cout << "Number of seconds to wait: ";
    std::cin >> sleep;
    // Multithreading
    DWORD threadId;
    HANDLE thread = CreateThread(
        NULL, // Default Security
        0, // Default Size
        foo, // Function to Run
        const_cast<char*>(input.c_str()), // Argument to Function
        0, // Creation Flags
        &threadId // ID of thread to reference later
    );
    // Wait for a fixed time
    Sleep(static_cast<DWORD>(sleep seconds));
    // // Wait until the thread finishes
    // WaitForSingleObject(thread, INFINITE);
    // Cleanup of thread resources
    CloseHandle(thread);
    // Flush buffer
    std::cout << std::flush;
    // :)
    return 0;
}

// Definition of Thread Function
DWORD WINAPI foo(LPVOID args) {
    char* word = reinterpret_cast<char*>(args);
    forever std::cout << word << std::endl;
    // // We should return but this function runs for forever
    // return 0;
}