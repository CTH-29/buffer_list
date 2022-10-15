# buffer list

## 简述

线程安全（理论上，还没测试）的单向链表创建的buffer缓冲空间

## TODO

buffer空间使用了malloc和memncpy来申请空间和复制数据，在数据量大的使用，可能不是一个很好的选择

## 使用

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
