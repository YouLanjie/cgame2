# cgame2

## 简介

- 这是一个c语言实战程序，一个小游戏——五子棋
- 开发平台:
  - [x] Ubuntu Linux
  - [ ] Debian Linux
  - [ ] Deepin Linux
- 支持两种语言： 汉语、英语

## 使用

- 通过源代码
  - 必要的软件:***gcc***
    - 如果没有，Debian Linux or Ubuntu Linux使用以下命令安装gcc

      ``` sh
      sudo apt install gcc
      ```

  - 下载源代码到本地
    - 使用git克隆此仓库到本地：

      ``` sh
      git clone https://github.com/youlanjie/cgame2.git
      ```

    - 或者从[这里](https://github.com/YouLanjie/cgame2/archive/refs/heads/main.zip)下载压缩包并解压
  - 编译
    - 使用make编译，文件会生成在bin目录下：

      ``` sh
      make
      ```

    - 或者 **进入cgame2/src/** 目录，使用gcc编译所有c文件：

      ``` sh
      gcc *.c */*.c -o main
      ```

    - 安装程序：

      ```sh
      make && make install
      ```


- 编译好的文件(bin/main)可以直接执行，程序做过兼容性的加强

- 其实在仓库的母文件夹下的bin目录就存放着已经编译好了的ELF文件，只要你的CPU架构是x86\_64的，就可以直接执行
