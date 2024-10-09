#ifndef SYSTEM2_HPP
#define SYSTEM2_HPP

#include <string>
#include <vector>

#if SYSTEM2_CPP_USE_SOURCE
    #define SYSTEM2_DECLARATION_ONLY 1
#endif

#include "System2.h"

//Wrapper for System2Run
SYSTEM2_RESULT System2CppRun(const std::string& command, System2CommandInfo& inOutCommandInfo);

//Wrapper for System2RunSubprocess
SYSTEM2_RESULT System2CppRunSubprocess( const std::string& executable,
                                        const std::vector<std::string>& args,
                                        System2CommandInfo& inOutCommandInfo);

//Wrapper for System2ReadFromOutput
SYSTEM2_RESULT System2CppReadFromOutput(const System2CommandInfo& info, 
                                        std::string& outputBuffer);

//Wrapper for System2WriteToInput
SYSTEM2_RESULT System2CppWriteToInput(  const System2CommandInfo& info, 
                                        const std::string& inputBuffer);

//Wrapper for System2GetCommandReturnValueAsync
SYSTEM2_RESULT System2CppGetCommandReturnValueAsync(const System2CommandInfo& info, 
                                                    int& outReturnCode);

//Wrapper for System2GetCommandReturnValueSync
SYSTEM2_RESULT System2CppGetCommandReturnValueSync( const System2CommandInfo& info, 
                                                    int& outReturnCode);

//If we are header only, then include all the implementations here. 
#if !SYSTEM2_CPP_USE_SOURCE || !defined(SYSTEM2_CPP_USE_SOURCE)
    #define INTERNAL_SYSTEM2_INCLUDED_IN_HEADER 1
    #include "System2.cpp"
#endif


#endif

