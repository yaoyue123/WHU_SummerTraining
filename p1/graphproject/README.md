# Project 2: 打败蒜头魔王 拯救网安大陆

## 介绍
92世纪初年，蔬菜横行霸道，尤其以蒜头君为首的大蒜最为猖獗，他有时候回家、有时候迷失于迷宫需要逃跑、有时候梦到自己当了王子、有时候改行当了蒜术士、有时候还会去爬楼梯，积怨极深，但网安大陆人民一直没有找到机会反击。直到有一天，蒜头君将网安人民喜爱的花椰妹（你们就是喜爱她。）掳走，网安人民终于忍无可忍，决定群起而攻之，进军计蒜城堡。

可是尴尬的来了，网安人民虽然知道计蒜城堡的位置，也拥有一份最新地图，但是路径错综复杂，网安人民只有有限的粮草，无法支持他们探索所有的路线。于是，网安人民需要你们的帮助，写出一个最短路径蒜法的代码库，来帮助蒜出通向计蒜城堡的最短路径，以最少的损耗来迎接最后的决战。

噩耗连连，网安作战中心的电脑由于过于老旧，无法带动一个 GUI 桌面环境，于是要求你们能够以最短的时间写出一份可以直接在命令行里运行的工具，及时进军计蒜城堡。拜托了！！！

在帮助网安作战中心之前，我需要帮助大家来学习如何写出这样一份工具，碰巧也直接当作你们这周的作业。

Command Line Interface (CLI)，中文翻译是命令行交互接口。这是一个在前端和后端都非常有用的工具，可以使用命令行对某些系统功能或工具进行调用。我们在这次作业里面将会带（假的，其实大部分是让大家自己研究）大家实现一个简单的 CLI。

---
![apt-cli-example](./img/apt-cli.png)
<center>我们用到的apt-get也是一个常用CLI</center>

---
我们本次作业的目的是用 C语言 完成一个包含图分析与蒜法的代码库，包括图元素的基础分析（顶点与边基础统计、图度量、边度量等）、最短路径蒜法等功能。再将此代码库制作成一个 CLI 工具，可以直接在 Linux 的 Terminal 里面运行。

本次作业将仍以 Debug 时的双人组配对编程的形式完成（如果上次三人组的继续保持三人组，请大家不要换座位不要换座位不要换座位）。本次作业将会占学期总评的5%，分数是小事，更重要的是战胜蒜头君的荣耀。

## 背景与目的
想要通过本次作业让大家对 Linux 的命令行的认识更进一步，并且就此机会将图相关搜索蒜法做好封装，以在之后的作业（战）中使用。

更重要的是，帮助推翻蒜头的黑暗统治。

## 具体要求
- C 语言实现，只允许调用 ```stdlib.h```, ```stdio.h```，```string.h```和```assert.h```（**0.5%**）
  - 其余函数如有需要，请自行实现，不做限制
  - 可使用网上的资源，但请在文件注释中注明来源


- 编辑 ```stats.h``` 和 ```stats.c``` 文件，完成如下函数（**1%**）：
  - ```int numberOfEdges(char name[])``` 接受测试图的文件名的 ```char``` 数组，返回图中边的数量
  - ```int numberOfVertices(char name[])``` 接受测试图的文件名的 ```char``` 数组，返回图中顶点的数量
  - ```double freemanNetworkCentrality(char name[])``` 接受测试图的文件名的 ```char``` 数组，返回图中 Freeman's Network Centrality 值 所提供数据为有向图，但是在蒜这个值的时候可以当成双向连通
  - ```double betweennessCentrality(char name[], char node[])``` 接受测试图的文件名的 ```char``` 数组，返回图中 **node** 的 Betweenness Centrality 值
  - ```double closenessCentrality(char name[], char node[])``` 接受测试图的文件名的 ```char``` 数组，返回图中 **node** 的 Closeness Centrality 值
  - ```double eigenvectorCentrality(char name[], char node[])``` 接受测试图的文件名的 ```char``` 数组，返回图中 **node** 的 Eigenvector Centrality 值
  - 参考 https://www.cl.cam.ac.uk/teaching/1213/L109/stna-lecture3.pdf
  - 评分标准为
    - 前**两个**函数 + 后面四个函数中选**两个**
    - **4/4 = 100% * 1% = 1%，6/4 = 125% * 1% = 1.25%**
    - ```betweenness, closeness, engenvector``` 接受 ```"max"``` 作为 ```char node[]``` 的参数，返回图中相应的 Centrality 的最大值。每个正确输出都作为 ```0.1%``` 学期总评的 Bonus。

- 将 ```DFS、BFS、Dijkstra、SPFA、A*``` 五个蒜法封装在 ```search.h``` 和 ```search.c``` 文件中（**2%，各0.4%**）
  - 每个函数封装结构没有要求，输入输出也没有要求
  - 测试会有有权图和无权图，BFS 不在有权图的考察范围内，大家可以不用实现
  - 需要额外加入一个函数 ```int* shortestPath(int u, int v, char algorithm[], char name[])```用来评分
    - 输入两个 ```int``` 值，```u``` 和 ```v```，分别为起点与终点的顶点编号
    - 输入一个 ```char``` 数组，装有所选算法的名字（分别为：```{DFS, BFS, Dijkstra, SPFA, Astar}```， 请严格遵守）
    - 输入一个 ```char``` 数组，装有测试图的文件名
    - 输出一个 ```int``` 数组指针，装有从 ```u``` 到 ```v``` 的最短路径
  - 我们将对这五个算法进行检查评分，并提供简单的数据及其 autograder 让你们本地自检


- 编辑 ```main.c``` 文件，实现以下功能(**0.5%**)：
  - 输出二进制文件名为 ```search-cli```
  - 利用 main 函数中的 argv 和 argc 参数接受命令行中的参数，完成以下命令行功能：
    - ```./search-cli -h/--help```(-h或--help，以下同) 显示帮助菜单，格式没有要求，不作为评分要求，只求自己能够看懂
    - ```./search-cli -g/--graph FILE_PATH -s/--stats STATS_PARAMS``` 显示以 ```FILE_PATH``` 为输入文件的图的统计信息，输出没有格式要求，具体支持的```STATS_PARAMS```参数如下：
      - ```edges``` 返回图中边的个数
      - ```vertices``` 返回图中顶点个数
      - ```freeman``` 返回图的 Freeman Centrality
      - ```betweenness -u NODE_NAME``` 返回 ```NODE_NAME``` 的 Betweenness Centrality
      - ```closeness -u NODE_NAME``` 返回 ```NODE_NAME``` 的 Closeness Centrality
      - ```eigenvector -u NODE_NAME``` 返回 ```NODE_NAME``` 的 Eigenvector Centrality
    - ```./search-cli -g/--graph FILE_PATH -sp/--shortestpath SEARCH_PARAMS -u STARTING_POINT -v TARGET_POINT``` 显示以 ```FILE_PATH``` 为输入文件的图中 从开始点 u 到 终点 v 的用 ```SEARCH_PARAMS```蒜出来的最短路径
      - 样例输入： ```./search-cli -g ./sx-stackoverflow.txt -sp Dijkstra -u 1 -v 5```
      - 样例输出： ```1 -> 2 -> 3 -> 4 -> 5```


- 自测文件为 ```test.txt```，检测所写算法能否在小的数据集上运行正确，具体文件格式如下：
  - 这个图的来源是一张地图，默认为无向图
  - 每一行格式： ```u v w``` 代表从```u```到```v```的权重为```w```的边
  - 正确答案保存在```test_key.txt``` 注：只有唯一最优解
  - 4%的分数只需要在这个数据集上通过即可


- ```Makefile```
  - 目标二进制文件为： ```search-cli```
  - 不规定具体编译路径
  - 样例```Makefile```只是一个骨架，不能直接运行不能直接运行不能直接运行！！！


- 真正的测试集来源于斯坦福开放的图数据集(**1%**)（https://snap.stanford.edu/data/amazon0601.txt.gz）
  - 同样的格式 ```u v w```，有向图
  - 具体信息参见 https://snap.stanford.edu/data/amazon0601.html
  - 将会提供修改版数据集，测试也将在修改版上进行


- 加分项
  - **0.1%** ```./search-cli -j``` 可以在 Terminal 中画出一副你想象中蒜头君的图（如图所示）
  ![boxed](./img/box_ascii_draw.png)
  - **1%** 更大的数据集，来自于 https://snap.stanford.edu/data/sx-stackoverflow.html
    - ~260万个顶点 ~6400万条边
    - 需要更好的优化（内存，时间复杂度）
  - **0.1%** ```Makefile``` 中加入 ```make clean```
  - 待更新


- 目录结构 - 可增加新文件，此目录下所有文件是批改所需，请不要改动文件名
  ```
    GraphProject/main.c
                 search.c
                 search.h
                 stats.c
                 stats.h
                 test.txt
                 test_key.txt
                 Makefile
                 submission.url
  ```


- 交作业方式
  - 与 Debug 作业相同
  - 原则上不更换小组
  - 每小组开一个新的 ```repo```，名字叫做 ```GraphProject```
  - 开新的```branch```，修改本目录下的 ```submission.url```


## 最后希望大家成功把蒜头大魔王干掉，为网安大陆带来一阵安宁！！！！！
