#ifndef SYSTEM2_IMPLEMENTATION_ONLY
    #define SYSTEM2_IMPLEMENTATION_ONLY 1
#endif
#include "System2.h"

#include "System2.hpp"

#if INTERNAL_SYSTEM2_INCLUDED_IN_HEADER
    #define SYSTEM2_CPP_PREFIX inline
#else
    #define SYSTEM2_CPP_PREFIX
#endif

SYSTEM2_CPP_PREFIX
SYSTEM2_RESULT System2CppRun(const std::string& command, System2CommandInfo& inOutCommandInfo)
{
    return System2Run(command.c_str(), &inOutCommandInfo);
}

SYSTEM2_CPP_PREFIX
SYSTEM2_RESULT System2CppRunSubprocess( const std::string& executable,
                                        const std::vector<std::string>& args,
                                        System2CommandInfo& inOutCommandInfo)
{
    std::vector<const char*> argsPointers;
    for(uint32_t i = 0; i < args.size(); ++i)
        argsPointers.push_back(args.at(i).c_str());
    
    return System2RunSubprocess(executable.c_str(), 
                                argsPointers.data(), 
                                static_cast<int>(args.size()), 
                                &inOutCommandInfo);
}

SYSTEM2_CPP_PREFIX
SYSTEM2_RESULT System2CppReadFromOutput(const System2CommandInfo& info, 
                                        std::string& outputBuffer)
{
    SYSTEM2_RESULT sys2Result;
    do
    {
        uint32_t byteRead = 0;
        outputBuffer.resize(outputBuffer.size() + 4096);
        sys2Result = 
            System2ReadFromOutput(  &info, 
                                    const_cast<char*>(outputBuffer.data()) + outputBuffer.size() - 4096,
                                    4096, 
                                    &byteRead);
        outputBuffer.resize(outputBuffer.size() + byteRead);
    }
    while(sys2Result == SYSTEM2_RESULT_READ_NOT_FINISHED);
    
    return sys2Result;
}

SYSTEM2_CPP_PREFIX
SYSTEM2_RESULT System2CppWriteToInput(  const System2CommandInfo& info, 
                                        const std::string& inputBuffer)
{
    return System2WriteToInput( &info, inputBuffer.c_str(), static_cast<int>(inputBuffer.size()));
}

SYSTEM2_CPP_PREFIX
SYSTEM2_RESULT System2CppCleanupCommand(const System2CommandInfo& info)
{
    return System2CleanupCommand(&info);
}

SYSTEM2_CPP_PREFIX
SYSTEM2_RESULT System2CppGetCommandReturnValueAsync(const System2CommandInfo& info, 
                                                    int& outReturnCode,
                                                    bool manualCleanup)
{
    return System2GetCommandReturnValueAsync(&info, &outReturnCode, manualCleanup);
}

SYSTEM2_CPP_PREFIX
SYSTEM2_RESULT System2CppGetCommandReturnValueSync( const System2CommandInfo& info, 
                                                    int& outReturnCode,
                                                    bool manualCleanup)
{
    return System2GetCommandReturnValueSync(&info, &outReturnCode, manualCleanup);
}

