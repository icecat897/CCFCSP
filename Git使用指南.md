# Git & GitHub 入门指南（个人备忘版）

> 写给刚开始用 Git 的自己。环境：Windows + Git Bash，远程仓库托管在 GitHub。
> 仓库示例：`https://github.com/icecat897/CCFCSP.git`

---

## 目录

1. [先建立一个心智模型](#1-先建立一个心智模型)
2. [第一次使用前的配置](#2-第一次使用前的配置只做一次)
3. [⭐ 最常用：日常「更新」三步曲](#3--最常用日常更新三步曲)
4. [常用命令速查表](#4-常用命令速查表)
5. [场景一：把一个本地项目首次传到 GitHub](#5-场景一把一个本地项目首次传到-github)
6. [场景二：换电脑 / 重新下载这个项目](#6-场景二换电脑--重新下载这个项目)
7. [查看状态、历史与改动](#7-查看状态历史与改动)
8. [.gitignore：让某些文件不被管理](#8-gitignore让某些文件不被管理)
9. [后悔药：撤销各种操作](#9-后悔药撤销各种操作)
10. [分支（简单了解即可）](#10-分支简单了解即可)
11. [⚠️ 中国大陆访问 GitHub 的网络问题](#11-️-中国大陆访问-github-的网络问题重点)
12. [常见报错对照表](#12-常见报错对照表)

---

## 1. 先建立一个心智模型

Git 里你的文件在 **4 个地方**之间流动，理解了这张图，命令就好记了：

```
  工作区              暂存区             本地仓库            远程仓库(GitHub)
(你正在编辑的文件)   (准备提交的快照)    (.git 里的历史)     (云端的备份/分享)
      │   git add        │   git commit       │     git push        │
      │ ───────────────► │ ─────────────────► │ ──────────────────► │
      │                  │                    │                     │
      │ ◄──────────────────────────────────────────── git pull ────┤
      │                          (从云端拉取别处的更新到本地)         │
```

- **工作区**：你电脑上正在改的文件。
- **暂存区（staging）**：用 `git add` 把「这次想提交的改动」挑出来放进来。
- **本地仓库**：用 `git commit` 把暂存区的内容存成一个「版本（commit）」，带一条说明。
- **远程仓库**：用 `git push` 把本地的版本同步到 GitHub；用 `git pull` 把 GitHub 上的更新拿回本地。

---

## 2. 第一次使用前的配置（只做一次）

告诉 Git 你是谁（会记录在每条提交里）：

```bash
git config --global user.name "你的名字"
git config --global user.email "你的邮箱"
```

查看当前配置：

```bash
git config --global --list
```

> `--global` 表示对这台电脑上所有仓库生效。去掉它就只对当前仓库生效。

---

## 3. ⭐ 最常用：日常「更新」三步曲

> 这是你 99% 时间在用的流程。每次改完代码想同步到 GitHub，就走这三步。

```bash
# 第 0 步（建议）：先看看改了哪些文件，做到心里有数
git status

# 第 1 步：把改动加入暂存区
git add .                 # 加入「所有」改动（最常用）
# 或者只加某个文件：
git add 40次/40_3/3.cpp

# 第 2 步：提交成一个版本，-m 后面写清楚这次改了什么
git commit -m "优化第40次第3题，修复样例3 的 WA"

# 第 3 步：推送到 GitHub
git push
```

**记忆口诀：`status` 看 → `add` 选 → `commit` 存 → `push` 传。**

> 第一次推送某个分支要写全 `git push -u origin main`（`-u` 建立关联）。之后只敲 `git push` 就行——我们已经帮你设置过了。

---

## 4. 常用命令速查表

| 命令 | 作用 |
|------|------|
| `git status` | 查看当前有哪些改动 / 处于什么状态（**最常用，多敲**） |
| `git add .` | 把所有改动加入暂存区 |
| `git add <文件>` | 只把某个文件加入暂存区 |
| `git commit -m "说明"` | 把暂存区内容提交为一个版本 |
| `git push` | 把本地提交推送到 GitHub |
| `git pull` | 把 GitHub 上的更新拉到本地 |
| `git log --oneline` | 查看提交历史（一行一条） |
| `git diff` | 查看「工作区」相对上次还没 add 的改动 |
| `git diff --cached` | 查看「暂存区」里已 add、还没 commit 的改动 |
| `git clone <网址>` | 把一个远程仓库完整下载到本地 |
| `git remote -v` | 查看当前仓库关联的远程地址 |

---

## 5. 场景一：把一个本地项目首次传到 GitHub

> 这就是我们刚才对 `CCFCSP` 文件夹做的全过程，记录下来方便你下次对新项目操作。

```bash
# 1) 进入项目文件夹，初始化为 git 仓库（main 为默认分支名）
cd 你的项目文件夹
git init -b main

# 2) （可选但推荐）创建 .gitignore，写明不想上传的文件，比如：
#    *.exe
#    output/

# 3) 把所有文件加入暂存并提交第一个版本
git add .
git commit -m "first commit: 初始化项目"

# 4) 去 https://github.com/new 网页上建一个【空】仓库
#    ⚠️ 不要勾选 Add README / .gitignore / license，否则会和本地冲突

# 5) 关联远程仓库地址（换成你自己的）
git remote add origin https://github.com/icecat897/你的仓库名.git

# 6) 推送
git push -u origin main
```

---

## 6. 场景二：换电脑 / 重新下载这个项目

在新电脑上，把 GitHub 仓库整个拉下来：

```bash
git clone https://github.com/icecat897/CCFCSP.git
cd CCFCSP
```

之后如果你在 GitHub 网页上、或另一台电脑上改过东西，要先把更新拿回来再继续：

```bash
git pull        # 拉取远程的最新内容
```

> 好习惯：**每次开始工作前先 `git pull`，结束工作后 `git push`**，避免多设备之间冲突。

---

## 7. 查看状态、历史与改动

```bash
git status                 # 现在有什么没提交的改动？
git log --oneline -10      # 最近 10 条提交
git log --oneline --graph  # 带分支图的历史
git diff                   # 我改了什么（还没 add 的部分）
git diff --cached          # 我 add 了什么（还没 commit 的部分）
git show 6b3bf82           # 查看某一条提交的具体改动（换成真实的 commit id）
```

---

## 8. `.gitignore`：让某些文件不被管理

在仓库根目录建一个名为 `.gitignore` 的文本文件，里面每行写一个「不想上传」的规则。例如本仓库用的：

```gitignore
# 编译产物
*.exe
*.o
output/

# 编辑器/系统文件
.vscode/
.DS_Store
Thumbs.db
```

- `*.exe` 忽略所有 .exe 文件；`output/` 忽略所有叫 output 的文件夹。
- ⚠️ `.gitignore` 只对**还没被 git 跟踪过**的文件有效。如果某文件之前已经被提交过，要先 `git rm --cached <文件>` 让 git 不再跟踪它。

---

## 9. 后悔药：撤销各种操作

> 按「改动走到哪一步」对号入座。带 ⚠️ 的会丢失改动，操作前想清楚。

```bash
# 撤销工作区某文件的修改（还没 add）—— ⚠️ 改动会丢失，恢复成上次提交的样子
git restore 文件名

# 把已经 add 的文件【移出】暂存区（改动还在，只是不提交了）
git restore --staged 文件名

# 改最后一条提交的说明文字（还没 push 时最安全）
git commit --amend -m "新的提交说明"

# 撤销最近一次提交，但保留改动在工作区（commit 没了，文件改动还在）
git reset --soft HEAD~1

# ⚠️ 彻底丢弃最近一次提交及其改动（慎用！）
git reset --hard HEAD~1
```

> 原则：**已经 `push` 到 GitHub 的提交，尽量不要用 `reset --hard` 去改写历史**，尤其是多人/多设备协作时。想撤销已推送的改动，更安全的是 `git revert <commit>`（它会新建一条"反向提交"）。

---

## 10. 分支（简单了解即可）

分支让你在不影响主线 `main` 的情况下做实验。个人备赛场景基本用不到，但了解一下：

```bash
git branch                 # 查看所有分支
git switch -c feature-x    # 新建并切换到分支 feature-x
git switch main            # 切回 main
git merge feature-x        # 把 feature-x 的改动合并进当前分支
```

---

## 11. ⚠️ 中国大陆访问 GitHub 的网络问题（重点）

你大概率会反复遇到这类报错（我们这次就遇到了）：

```
curl 55 Send failure: Connection was reset
fatal: the remote end hung up unexpectedly
```

**这不是你命令写错了，是连接 GitHub 时被网络掐断了。** 按从简单到彻底的顺序尝试：

**① 直接重试**
连接重置往往是间断性的，多 `git push` 几次就成功了（我们这次就是重试后成功的）。

**② 加两个抗不稳定的设置（已对本仓库设置过，可改成全局）**

```bash
git config --global http.postBuffer 524288000   # 提高传输缓冲到 500MB
git config --global http.version HTTP/1.1        # 用更稳的 HTTP/1.1
```

**③ 挂代理（最彻底，推荐）**
如果你有科学上网工具（如 Clash，本地端口通常是 `7890`），让 git 走代理：

```bash
# 设置代理（端口换成你自己工具的端口）
git config --global http.proxy http://127.0.0.1:7890
git config --global https.proxy http://127.0.0.1:7890

# 不需要时取消代理
git config --global --unset http.proxy
git config --global --unset https.proxy
```

**④ 改用 SSH 协议**
有时候 SSH 比 HTTPS 稳定。需要先生成密钥并把公钥贴到 GitHub，然后把远程地址换成 SSH 形式：

```bash
git remote set-url origin git@github.com:icecat897/CCFCSP.git
```
（SSH 配置稍麻烦，搜索"GitHub SSH key 配置"按步骤做一次即可。）

---

## 12. 常见报错对照表

| 报错关键字 | 含义 | 解决 |
|-----------|------|------|
| `Connection was reset` / `curl 55/56` / `remote end hung up` | 网络被掐断 | 见第 11 节：重试 / 加设置 / 挂代理 |
| `Authentication failed` / `403` | 身份验证失败 | HTTPS 不能用密码，需用浏览器授权或 Personal Access Token |
| `Repository not found` | 仓库地址错或没建/没权限 | 检查 `git remote -v` 的网址；确认 GitHub 上仓库已创建 |
| `Updates were rejected ... fetch first` | 远程有你本地没有的提交 | 先 `git pull`（或 `git pull --rebase`）再 `git push` |
| `fatal: not a git repository` | 当前文件夹不是 git 仓库 | `cd` 到正确目录，或先 `git init` |
| `nothing to commit, working tree clean` | 没有任何改动 | 正常提示，说明没东西要提交 |

---

🎯 记住最核心的一句话：**改完东西，就 `git add .` → `git commit -m "说明"` → `git push`。** 其余都是查得到的细节。
