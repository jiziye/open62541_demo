#include <stdio.h>
//#include <open62541.h>
#include"open62541.h"

int main(void)
{
    // UA_Client  *client = UA_Client_new(UA_ClientConfig_setDefault);
    UA_Client  *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if(retval != UA_STATUSCODE_GOOD)
    {
        UA_Client_delete(client);
        return (int)retval;
    }

    UA_Variant value;
    UA_Variant_init(&value);
 
    UA_NodeId testvar = UA_NODEID_STRING(1,"the.answer");
    retval = UA_Client_readValueAttribute(client, testvar, &value);
 
    if(retval == UA_STATUSCODE_GOOD) {
        UA_Int32 *p = (UA_Int32 *)value.data;
        printf("Var = %d \n",*p);
    }

    UA_Client_write
    UA_Variant_deleteMembers(&value);
    UA_Client_delete(client);
    return UA_STATUSCODE_GOOD;
}