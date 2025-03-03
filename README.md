# System2 C++ Wrapper

This is a thin C++ wrapper for the [System2](https://github.com/Neko-Box-Coder/System2) library, a cross-platform C library for executing shell commands and subprocesses with input/output redirection capabilities.

## Features

- Provides a C++ interface to the System2 library
- Uses `std::string` and `std::vector` for easier memory management
- Maintains all functionality of the original C library
- Cross-platform support (POSIX and Windows)

## Usage

1. Clone this repository recursively.
2. This wrapper can be included as header only or be linked as library
    - CMake: Set `SYSTEM2_CPP_USE_SOURCE` accordingly and link it by doing `target_link_libraries(YourTarget System2Cpp)`
    - Header Only: Add `External/System2` and this directory to your project include paths and include `System2.hpp` in your code.
    - Link As Library Manually: Same as Header only, then add `System2.cpp` to your project, define `SYSTEM2_CPP_USE_SOURCE=1` either in your project or before `#include "System2.hpp"`

## API

The C++ wrapper provides the following functions:
```cpp
SYSTEM2_RESULT System2CppRun(const std::string& command, System2CommandInfo& inOutCommandInfo);
SYSTEM2_RESULT System2CppRunSubprocess(const std::string& executable, 
                                       const std::vector<std::string>& args, 
                                       System2CommandInfo& inOutCommandInfo);
SYSTEM2_RESULT System2CppReadFromOutput(const System2CommandInfo& info,
                                        std::string& outputBuffer);
SYSTEM2_RESULT System2CppWriteToInput(const System2CommandInfo& info,
                                      const std::string& inputBuffer);
SYSTEM2_RESULT System2CppCleanupCommand(const System2CommandInfo& info);
SYSTEM2_RESULT System2CppGetCommandReturnValueAsync(const System2CommandInfo& info,
                                                    int& outReturnCode,
                                                    bool manualCleanup);
SYSTEM2_RESULT System2CppGetCommandReturnValueSync(const System2CommandInfo& info,
                                                   int& outReturnCode,
                                                   bool manualCleanup);
```

These functions correspond directly to their C counterparts in the System2 library, with the main differences being the use of `std::string` for command and input/output buffers, and `std::vector<std::string>` for command arguments.

## Example

Here's a basic example of how to use the System2 C++ wrapper:

```cpp
#include "System2.hpp"
#include <iostream>
int main() 
{
    System2CommandInfo commandInfo = {};
    commandInfo.RedirectOutput = true;
    std::string command = "echo Hello, World!";
    SYSTEM2_RESULT result = System2CppRun(command, commandInfo);
    if(result == SYSTEM2_RESULT_SUCCESS) 
    {
        std::string output;
        System2CppReadFromOutput(commandInfo, output);
        std::cout << "Command output: " << output << std::endl;
        
        int returnCode;
        System2CppGetCommandReturnValueSync(commandInfo, returnCode, false);
        std::cout << "Command return code: " << returnCode << std::endl;
    } 
    else 
    {
        std::cerr << "Failed to run command" << std::endl;
    }
    return 0;
}
```

## Notes

- This wrapper maintains the same behavior and return values as the original C library.
- For detailed information about the `System2CommandInfo` structure and `SYSTEM2_RESULT` enum, please refer to the original System2 library documentation.
- The wrapper does not add any additional error handling or resource management beyond what the C library provides.
