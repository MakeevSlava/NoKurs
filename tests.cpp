#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/TestReporterStdout.h>

#include <vector>

#include <Server.h>
#include <Logger.h>
#include <UsersParser.h>
#include <CmdLine.h>
#include <ServerError.h>

auto RunTest (const char* SuiteName)
{ 
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(),
                                SuiteName,
                                UnitTest::True(),0);
}

SUITE(CmdLine){
    TEST(cmdLine_invalid_type){
        CmdLine cmd;

        cmd.addParam("--port", "-p", "<port> , port must be less than 65536", param_type::integer);
        cmd.addParam("--file", "-f", "<users File>");
        cmd.addParam("--logs", "-l", "<logs File>");
        
        std::vector<char*> arguments= {"server","-p","test","-l","logs","-f","users"};
        
        CHECK_THROW(cmd.parse(arguments.size(),arguments.data()),ServerError);
    }

    TEST(cmdLine_invalid_param){
        CmdLine cmd;

        cmd.addParam("--port", "-p", "<port> , port must be less than 65536", param_type::integer);
        cmd.addParam("--file", "-f", "<users File>");
        cmd.addParam("--logs", "-l", "<logs File>");
        
        std::vector<char*> arguments= {"server","invalid","-p","33333","-l","logs","-f","users"};
        
        CHECK_THROW(cmd.parse(arguments.size(),arguments.data()),ServerError);
    }
}

SUITE(UsersParser){

    TEST(users_empty){
        
        UsersParser parser;
        CHECK_THROW(parser.parse("users_empty"),ServerError);
    }

    TEST(users_nonReadable){
        
        UsersParser parser;
        CHECK_THROW(parser.parse("users_nonReadable"),ServerError);
    }

    TEST(users_invalidFormat){
        
        UsersParser parser;
        CHECK_THROW(parser.parse("users_invalidFormat"),ServerError);
    }
}
  

int main() {
    RunTest("CmdLine");
    RunTest("UsersParser");
    RunTest("Logger");
    RunTest("Communication");
    return 0;
    
}
