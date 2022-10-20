# buffer list

## 简述

线程安全的单向链表创建的队列缓冲空间  
通过复制或者指针的方式来保存数据

## TODO

线程安全的测试
## 使用

push 存入队列末尾的buffer  
pop 取出队列开头的buffer，删除  
peek 取出队列开头的buffer，不删除  

at 表示指定位置  
后缀 2 表示通过指针的方式存储，不进行内存复制

具体函数使用详见main.c

## 测试

```bash
./build.sh
```

## license

MIT
