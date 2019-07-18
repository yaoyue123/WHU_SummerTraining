# 作业规范


本次作业要求大家 3 - 5 人组队(吃豆人的队伍），作业要求大家的代码风格规范，另外不希望有人划水，所以如果有人贡献率低于 10% 会有所扣分。

本次作业共占 25% 的分数。


# 下面的操作，一个小组只需要一个人操作就可以了！！！！


---

1. 请每个小组新建一个 repo
2. 本周所有练习的代码，全部放在这个里面
3. 修改 README.md，每一行填入你们的 姓名-学号-邮箱 （例如 xiaohei-201813244t1-suantoujun@jisuanke.com） `git config user.email` 查看邮箱
4. 把 @xiaohei 拉入你们的 group 里，并设置我 owner。

---


1. 请每个组派一个人在 https://gitlab.inspurcloud.cn/WuHanU/snake 目录中 pull 一下，下面会看到 `submission.url`
2. 开一个新 branch 名字,为你们的小组名（例如 `git branch test-group`）  
3. 修改 submission.url 文件，将 submission.url 的第一行更为为小组 repo 的 url。（例如 https://gitlab.inspurcloud.cn.test-group/Debug）
4. git add, commit, push (`千万不要提交到 master 上!!!`)


---

# 作业的提交（协同分工提交，最后是会查贡献率的）


第一,二 天作业的提交：在 repo 中新建文件 `1` ，然后把当天的项目放入(所有代码文件和 Makefile)。

第一天评分细节：测试 5 个 test 函数，进行测试。

- create game from file      1分
- snake move                 1分
- board update(next frame)   1分
- invaid memory              1分
- memory free                1分

第二天评分细节：在 20 * 40 的图上测试 bfs 代码。 

在指定图上搜索最短路。 5 组（每组一分，使用哪个 bfs 代码自己决定）， 直接调用 get_action() 函数测试。

第三天作业的提交：在 repo 中新建文件 `学号`(自己的学号，例如新建文件 20181234213, 把 ai.c 放进目录(可以增加其他相关文件)

在指定图上进行搜索 （2 组生长速度是 5，3 组生长速度是 1，同样也是直接调用 get_action()） （7 * 7 的空图），每组一分。


