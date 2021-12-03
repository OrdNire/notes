**初始化仓库**

1、git init

**连接仓库**

2、git remote add origin “ssh”

**获取当前最新版本**

3、git pull

**创建并转到新的分支**

4、git checkout -b dev origin/dev 

**获取当前分支及所有分支**

5、git branch

**转到某分支（如果此分支不存在则为新建分支）**

6、git checkout feature   **/**   git checkout -b feature

**进行自己的活动**

7、touch shuaige.txt（创建了一个txt文件）

进入之后按“i”，进入输入模式，输入完成后输入“：”和“wq”

形式为："：wq"并按回车

**查看（有需要）**

8、vi shuaige.txt

同上，输入："：wq"并按回车

**将文件加入到缓冲区**

9、git add .（“add”和”.“中间有空格）

10、git commit -m"完成shuaige.txt 罗舒能 2020-3-29 16：28"

**查看自己的文件**

11、cat shuaige.txt

**返回dev分支**

12、git checkout dev

**在上传之前先获取当前最新版本**

13、git pull

**feature与dev分支合并**

14、git merge feature --no-ff

**上传**

15、git push origin dev

***如果有冲突，提示中会给出，看不懂上网查***

vi shuaige.txt

进行修改

**删除分支**

git branch -d 分支名

**获取自己的日志**

git reflog    **/**     git log（进入之后按q退出）

**返回上一次commit操作**

git reset

**删除指定文件/文件夹**

当我们需要删除暂存区或分支上的文件，但是本地' 需要，这个文件，只是‘不希望加入版本控制'，可以使用

git rm -r *--cached .*

当我们需要删除暂存区或分支上的文件，同时工作区‘不需要 '这个文件，可以使用'git rm'

git rm file

**git ignore操作(important)**

 *通过git ls-files查看当前版本管理文件* （git status也可）

1) 创建自己的    .gitignore   文件

touch .gitignore

2)  编辑自己的   .gitignore  文件

vim .gitignore     **/**     在文件夹中直接以文本方式打开并编辑

3）注意

以”#”号开头表示注释；
以斜杠“/”开头表示目录；
以星号“*”通配多个字符；
以问号“?”通配单个字符；
以方括号“[]”包含单个字符的匹配列表；
以叹号“!”表示不忽略(跟踪)匹配到的文件或目录； 

 此外，git 对于 .ignore 配置文件是按行从上到下进行规则匹配的，意味着如果前面的规则匹配的范围更大，则后面的规则将不会生效； 

 file/
说明：忽略目录file下的全部内容；不管是根目录下的/file/目录，还是某个子目录/child/file/目录，都会被忽略； 

 /file/
说明：忽略根目录下的/file/目录的全部内容； 

 /*
!.gitignore
说明：忽略所有文件，但不忽略.gitignore文件；

4）.gitignore规则不生效

.gitignore只能忽略那些原来没有被track的文件，如果某些文件已经被纳入了版本管理中，则修改.gitignore是无效的。

解决方法就是先把本地缓存删除（改变成未track状态），然后再提交:

git rm -r *--cached .*

git add .

git commit -m 'update .gitignore'

https://jingyan.baidu.com/article/1974b289e8f00cb4b0f77435.html

 https://blog.csdn.net/o07sai/article/details/81043474 (可供参考，但有些说法与我注意中说的有冲突，以自己实际为准，之后弄明白了我再对其进行优化)

**git status用法**

https://blog.csdn.net/qq_34234087/article/details/97696060

主要可以用它来进行查看自己的仓库的信息和改动，并给出之后步骤提示

