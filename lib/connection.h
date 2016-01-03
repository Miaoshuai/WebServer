/*======================================================
    > File Name: connection.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月21日 星期一 17时06分48秒
 =======================================================*/
#ifndef CONNECTION_H_
#define CONNECTION_H_
#include "buffer.h"

namespace netlib
{
    class Connection
    {
        public:
            int fd_;    //标示此连接的描述符
            Buffer inputBuffer_;    //输入buffer
            Buffer outputBuffer_;   //输出buffer
        public:
            Connection(int fd):fd_(fd)
            {
        
            }
            ~Connection()
            {
            
            }

    };
}
#endif
