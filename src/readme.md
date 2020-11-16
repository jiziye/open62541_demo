# OPC UA
OPC UA为可以在协议消息中编码的值定义类型系统。

OPC UA中，使用面向对象的方式定义业务模型。
面向对象中通过类(包括类成员变量，类成员函数，类实例)，以及类之间的继承关系实现对业务的建模，
而OPC UA的通过节点，以及节点之间的引用关系实现对业务的建模。
定义节点自身的属性，节点之间的引用。

## Node节点
节点是OPC UA数据交互的基本单元，客户端和服务器之间的交互通信，都是基于节点进行的。节点可以根据不同的用途归属于不同的节点类别（NodeClass).
OPC UA中预定义了8种节点：

    ObjectNode
    ObjectTypeNode
    VariableNode
    VariableTypeNode
    MethodNode
    ReferenceTypeNode
    DataTypeNode
    ViewNode

    节点的属性(attritube)用来描述节点，一个节点的属性取决于NodeClass,不过，每个节点也有一些通用属性，如下：
    NodeID
    NodeClass
    BrowseName
    DisplayName
    Description
    writemask
    userwritemask

    OPC UA中，最重要的节点类别（nodeclass) 是对象object ，变量variable，方法method。
    对象object可以拥有变量variable和方法method，而且可以触发事件。
    1.节点类别为变量variable的节点 代表一个值，客户端可以对这个值进行读取，写入，订阅其变化。
    2.节点类别为方法method的节点 代表服务器中一个由客户端调用并返回结果的方法。 每个方法指定客户端应使用的输入参数和客户端的结果。
    3.节点类别为对象object的节点 用于地址空间结构，对象使用变量对外提供值，但没有value属性。对象可以用于分组管理变量，方法或其他对象。对象也可以是一个事件通知器，客户端可以订阅事件通知其来接收事件。
  
 - 除了些通用属性，对象唯一的附加属性是用来识别对象是否可以作为事件通知器，即客户端是否可以订阅对象来接受事件，或者读取、更新事件的历史。 
- 变量的附加属性比较多。值得注意的一点是，变量的数据类型(DataType)这个附加属性。变量的数据类型表示为地址空间的节点，因此这个附加属性是NodeId类型的。 
- 方法的附加属性有Executable和UseExecutable，这两个是关于执行方面的。除了附加属性，方法还拥有特性(Property)，说白了就是属于方法的输入输出变量。方法的输入输出参数不是通过属性描述的，而是通过变量。


## Reference 引用：
引用描述了两个节点之间的关系，用来把多个节点关联起来，OPC UA预定义了多种引用。
hasTypeDefinition
hasTypeDefinition用来描述面向对象中类、类实例之间的关系。
ObjectNode的hasTypeDefinition引用，指向了一个ObjectTypeNode，表示该ObjectNode的类型;
    VariableNode的hasTypeDefinition引用，指向一个VariableTypeNode，表示该 VariableNode的类型。

hasSubType
hasSubType用来描述面向对象中的继承关系。当子类从父类继承后，子类拥有一个hasSubType引用指向父类。
hasComponents

hasComponents类似设计模式中的组合模式。
    ObjectNode一般都由多个VariableNode组成，ObjectNode包含某个VariableNode时，ObjectNode拥有一个hasComponents引用，指向该VariableNode；
    VariableNode也可以包含子VariableNode，此时也用hasComponents描述它们的关系。

Organizes
Organizes用来指明两个节点的层次结构，可以类比为文件夹和文件的关系，通过Organizes，可以把多个文件(节点)组织到同一个文件夹(父节点)下面。

## service 服务
服务可以看做是OPC UA Server提供的API集合，也可以看做是RPC(Remote Procedure Call)接口集合，服务以方法的方式提供出来，服务使用了类似Web的请求-应答机制，当客户端调用一个服务时，客户端发送一个请求给服务器，服务器处理完成请求后，返回响应消息给客户端。
客户端访问服务器提供的所有功能，都是通过调用服务完成。


## usage
源码编译：
gcc -std = c99 open62541.c myServer.c -o myServer


客户端：
下载安装ua expert

连接服务器：
点击+，add server
点击advanced：输入自定义configuration name: test_online
endpoint url: opc.tcp://opcua.rocks:4840/
session name :  test_online_session
点击ok.

project出servers出现test_online，右键选择connect.
稍等一会，在address space处会显示服务器的节点。
opc.tcp://opcua.rocks:4840/提供了一个Hello World的方法，可通过右键菜单调用该方法

myServer1.c的头文件添加错误：
// #include <open62541/plugin/log_stdout.h>
// #include <open62541/server.h>
// #include <open62541/server_config_default.h>
注释后，改用#include "open62541.h"

ua expert可在地址空间看到the answer.
