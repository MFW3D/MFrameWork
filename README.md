﻿![image](https://github.com/captainl1993/MFrameWork/blob/master/logo.png)

作者联系方式：
	Email：captainl1993@126.com 
	QQ：1452882479
	官方网站：http://mfw3d.com http://mfw3d.cn 

Author contact information:
	Email：captainl1993@126.com
	QQ：1452882479
	official website：http://mfw3d.com http://mfw3d.cn 

# MFrameWork
MFrameWork:
1、集成高效的数据存储和访问
2、网络机制
3、分布式服务器框架
4、三维引擎框架
5、以及客户端对接框架等
6、自动化代码生成方案，数据增删改查操作无需写代码，数据协议文件自
动生成

# MFrameWork
MFrameWork:
1、Integrated, efficient data storage and access
2、Network mechanism
3、Distributed server framework
4、3D engine framework
5、client framework, etc.
6、Automatic code generation scheme, data additions and deletions, 
search operations without writing code, data protocol files from
Dynamic generation.

实现目的:
1、实现方便快捷的转变为游戏服务器，数据服务器，以及三维应用客户端
2、逻辑框架实现麻将逻辑，以棋牌服务器为例进行开发

purpose:
1、Easy to implement changes to game servers, data servers, 
and 3D application clients
2、Logic framework to achieve mahjong logic, chess server as
 an example for development


项目配置：
1、安装vs2015编译器，项目代码支持linux编译
2、下载预编译好的项目依赖，下载地址：
百度云盘链接：http://pan.baidu.com/s/1qYI6HwK 密码：ra9s
3、下载后将压缩包内容解压到MFW项目根目录，也就是bin，lib，include
目录与解决方案文件同目录
4、使用debug x64 进行编译，这样配置好依赖的路径


configuration：
1、To run this project ,install vs2015.you can also use linux Compile this project.
2、Download pre compiled project dependencies and download addresses：
Baidu cloud link：http://pan.baidu.com/s/1qYI6HwK  passwd：ra9s
3、After downloading, extract the contents of the compressed package into the root of
 the MFW project, that is, the contents of the packet "bin，lib，include",The directory 
 and the solution file are in the same directory
4、Compile using debug x64, so that you configure the path of dependency.

MFW3D Engine 架构
![image](https://github.com/captainl1993/MFrameWork/blob/master/Doc/Imgs/MFW3DEngine.png)

框架结构介绍：
=============================================================
 MFW框架
=============================================================
-------------------------------------------------------------
1 MFW
-------------------------------------------------------------
1.1 介绍
1.1.1 框架中使用的基础库和方法
1.1.2 数据库和网络通讯的基类
-------------------------------------------------------------
2 MFW_Common
-------------------------------------------------------------
2.1 介绍
2.1.1 服务器客户端可以使用的公共方法和基类
2.1.2 提供网络处理，数据消息传递的父类
-------------------------------------------------------------
3 MFW_Produce
-------------------------------------------------------------
3.1 介绍
3.1.1 数据生成产物集合
3.1.2 提供数据库的读写和公共的生成物
-------------------------------------------------------------
4 MFW_Proto
-------------------------------------------------------------
4.1 介绍
4.1.1 服务器和客户端使用的所有协议
-------------------------------------------------------------
5 MFW_DB
-------------------------------------------------------------
5.1 介绍
5.1.1 数据库服务器，提供数据的读写服务
5.1.2 为登录服务器和游戏服务器提供数据支持
-------------------------------------------------------------
6 MFW_Login
-------------------------------------------------------------
6.1 介绍
6.1.1 提供玩家登录验证，和注册
-------------------------------------------------------------
7 MFW_Logic
-------------------------------------------------------------
7.1 介绍
7.1.1 逻辑服务器，实现基本的逻辑业务
-------------------------------------------------------------
8 MFW_Manager
-------------------------------------------------------------
8.1 介绍
8.1.1 分配玩家到相应的服务器
8.1.2 管理玩家游戏状态
-------------------------------------------------------------
9 MFW_Engine3D
-------------------------------------------------------------
9.1 介绍
9.1.1 三维引擎基础库封装
9.1.2 提供和高效的三维渲染
-------------------------------------------------------------
10 MFW_Engine
-------------------------------------------------------------
10.1 介绍
10.1.1 独立3维客户端
-------------------------------------------------------------
11 MFW_EngineMFC
-------------------------------------------------------------
11.1 介绍
11.1.1 MFC嵌入3维客户端
-------------------------------------------------------------
12 MFW_Engine3DNet
-------------------------------------------------------------
12.1 介绍
12.1.1 clr封装的三维客户端库，提供Donet框架使用
-------------------------------------------------------------
13 MFW_Tools
-------------------------------------------------------------
13.1 介绍
13.1.1 提供生成器，生成数据库操作代码和对应的协议
13.1.2 提供DoNet访问tcp客户端封装
13.1.3 提供Unity3D使用的客户端TCP封装
-------------------------------------------------------------
14 MFW_Web
-------------------------------------------------------------
14.1 介绍
14.1.1 http服务器封装用例
