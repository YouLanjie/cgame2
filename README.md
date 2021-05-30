# cgame2

### 简介
- 这是一个c语言实战程序。
- 一个小游戏
- 内容是五子棋
- 开发平台:Debian Linux

### 使用
- 通过源代码
	- 必要的软件:`gcc`

	- 下载源代码到本地
		- 使用git克隆此仓库到本地：
		```
		git clone https://github.com/youlanjie/cgame2.git
		```
		- 或者从[这里](https://github.com/YouLanjie/cgame2/archive/refs/heads/main.zip)下载压缩包并解压
		- 再或者直接复制源代码，如果这样注意一定要复制hedfile里的文件

	- 编译
		- 使用dpkg安装：

		进入cgame2/文件夹，执行

		`./build.sh`

		没有报错则执行

		`./update.sh`

		- 或者进入cgame2/src/目录，使用gcc编译main.c文件：

		```gcc main.c -o file```或者```gcc -o file main.c```

