
#include "open62541.h"
#include <signal.h>
#include <stdlib.h>

static volatile UA_Boolean running = true;

//创建结束ctrl-c的处理函数
static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

static void addVariable(UA_Server *server)
{
        /*Define the attribute of the myInteger variable node*/
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Int32 myInteger = 43;
    UA_Variant_setScalar(&attr.value,&myInteger,&UA_TYPES[UA_TYPES_INT32]);
    attr.description = UA_LOCALIZEDTEXT("en-US","the answer");
    attr.displayName = UA_LOCALIZEDTEXT("en-US","the answer");
    attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

        /*Add the variable node to the information model*/
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1,"the.answer");
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1,"the answer");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0,UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0,UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server,myIntegerNodeId,parentNodeId,\
                              parentReferenceNodeId,myIntegerName,\
                              UA_NODEID_NUMERIC(0,UA_NS0ID_BASEDATAVARIABLETYPE),\
                              attr,NULL,NULL);
 
}


int main(void)
{
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    addVariable(server);

    UA_StatusCode retval = UA_Server_run(server, &running);

    UA_Server_delete(server);
    //return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
    return (int)retval;
}
