# cgame2

## 简介

- 这是一个c语言实战程序，一个小游戏——五子棋

- 支持的系统
  - [x] Linux
  - [ ] ~~Windows (使用gcc编译)~~

> 我于2022-08的更新中暂时抛弃了对windows的兼容。  
与windows兼容的版本在`windows`分支中

## 使用

- 通过源代码
  - 建议安装的软件: ***make、git***
  - 需要的软件: ***gcc***

  - 下载源代码到本地
    - 使用git克隆此仓库到本地：

      ``` sh
      git clone https://github.com/youlanjie/cgame2.git --recurse-submodules
      ```
	- 倘若没有获取到子模块，请在仓库主目录内使用以下命令：
	
	  ```sh
	  git submodule init
	  git submodule update
	  ```
	
  - 编译
    - 使用make编译，文件会生成在bin目录下：

      ``` sh
      make
      ```

    - Arch用户可以使用[PKGBUILD文件](https://github.com/YouLanjie/cgame2/blob/arch-package/PKGBUILD)运行`makepkg`构建软件包再运行Pacman进行安装，也可以从[AUR](https://aur.archlinux.org/packages/cgame2)上安装

- 手动编译好的文件(**bin/main**)应可以直接执行，~~程序做过兼容性的加强~~
