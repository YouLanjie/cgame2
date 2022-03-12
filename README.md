# cgame2

## 简介

- 这是一个c语言实战程序，一个小游戏——五子棋
- 开发平台:
  - [x] Ubuntu Linux
  - [ ] Debian Linux
  - [ ] Deepin Linux

- 支持的系统
  - [x] Linux
  - [x] Windows (使用gcc在VScode中运行)

## 使用

- 通过源代码
  - 建议安装的软件: ***make、git***
  - 需要的软件: ***gcc***
    - 如果没有，Debian Linux or Ubuntu Linux可以使用以下命令安装gcc

      ``` sh
      sudo apt install gcc
      ```

  - 下载源代码到本地
    - 使用git克隆此仓库到本地：

      ``` sh
      git clone https://github.com/youlanjie/cgame2.git
      ```

    - 或者从[这里下载压缩包](https://github.com/YouLanjie/cgame2/archive/refs/heads/main.zip)并解压
  - 编译
    - 使用make编译，文件会生成在bin目录下：

      ``` sh
      make
      ```

    - 或者在 *cgame2* 文件夹下直接使用gcc编译所有c文件：

      ``` sh
      gcc include/tools.c *.c -o main
      ```

    - 安装软件到 */usr/local/cgame2* 下：

      ```sh
      make && make install
      ```


- 手动编译好的文件(**bin/main**)可以直接执行，程序做过兼容性的加强

