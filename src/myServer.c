#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

#include <signal.h>
#include <stdlib.h>

static volatile UA_Boolean running = true;
static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}


int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    //代码显示了服务器生命周期管理的三个部分：创建服务器，运行服务器和删除服务器。
    //创建服务器
    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    //运行服务器
    UA_StatusCode retval = UA_Server_run(server, &running);

   //删除服务器
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
