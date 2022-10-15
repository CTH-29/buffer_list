# buffer list

## 简述

线程安全（理论上，还没测试）的单向链表创建的队列缓冲空间

## TODO

buffer空间使用了malloc和memncpy来申请空间和复制数据，在数据量大的使用，可能不是一个很好的选择

## 使用

push 存入队列末尾的buffer
pop 取出并删除队列开头的buffer
peek 取出队列开头的buffer

xxx_at 表示指定位置

具体函数使用详见main.c

## 测试

```bash
mkdir build
cd build
cmake ..
make
run ../test
```

## license

MIT
