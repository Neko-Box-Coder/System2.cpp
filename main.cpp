#include "System2.hpp"

#include <iostream>

#define EXIT_IF_FAILED(result) \
if(result != SYSTEM2_RESULT_SUCCESS) \
{\
    printf("Error at %d: %d", __LINE__, result);\
    return -1;\
}

int main(...) 
{
    {
        System2CommandInfo commandInfo = {};
        commandInfo.RedirectInput = true;
        commandInfo.RedirectOutput = true;
        SYSTEM2_RESULT result;

        #if defined(__unix__) || defined(__APPLE__)
            result = System2CppRun("read testVar && echo testVar is \\\"$testVar\\\"", commandInfo);
        #endif
        
        #if defined(_WIN32)
            result = System2CppRun("set /p testVar= && echo testVar is \"!testVar!\"", commandInfo);
        #endif
        
        EXIT_IF_FAILED(result);
        
        std::string input = "test content\n";
        result = System2CppWriteToInput(commandInfo, input);
        EXIT_IF_FAILED(result);
        
        //Waiting here simulates the child process has "finished" and we read the output of it
        //Sleep(2000);
        
        std::string output;
        result = System2CppReadFromOutput(commandInfo, output);
        
        EXIT_IF_FAILED(result);
        
        int returnCode = -1;
        result = System2CppGetCommandReturnValueSync(commandInfo, returnCode, false);
        EXIT_IF_FAILED(result);
        
        std::cout << output << std::endl;
        std::cout << "Command has executed with return value: " << returnCode << std::endl;
    }
    
    //Output: Command has executed with return value: : 0
    //Output: testVar is "test content"
    
    std::cout << "Using stdin now, enter the value of testVar: " << std::flush;
    
    {
        System2CommandInfo commandInfo = {};
        SYSTEM2_RESULT result;

        #if defined(__unix__) || defined(__APPLE__)
            result = System2CppRun("read testVar && echo testVar is \\\"$testVar\\\"", commandInfo);
        #endif
        
        #if defined(_WIN32)
            result = System2CppRun("set /p testVar= && echo testVar is \"!testVar!\"", commandInfo);
        #endif
        
        EXIT_IF_FAILED(result);
        
        int returnCode = -1;
        result = System2CppGetCommandReturnValueSync(commandInfo, returnCode, false);
        EXIT_IF_FAILED(result);
        
        std::cout << "Command has executed with return value: " << returnCode << std::endl;
    }
    
    return 0;
}
