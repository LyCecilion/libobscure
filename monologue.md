# 文字转语音台词

世界上使用最广泛的某现代商业操作系统的部分程序仍然在使用错误代码来表示错误，而 Linux 却仍然使用清晰易懂的错误提示。为什么不扩大 Linux 的市场呢？

于是我修复了 Linux 报错提示看得懂的 Bug，这样 Linux 用户也能体验到错误代码了。

于是我发明了：

---

Library obscure 将常见的错误文本替换为某现代商业操作系统风格的统一提示。项目目前覆盖了 p error, string error, string error r, g a i string error，GNU 的 error 和 error at line 错误接口。

在有 gcc 环境下的 Linux 中，git clone 该 Repo 后编译，编译的产物位于 build 文件夹下的 library obscure dot so，可以通过 file 确认动态库类型。

Library obscure 的使用很简单，将该 so 文件加载到 L D preload 中即可。

你可以对一次命令注入，这不会修改当前 Shell 的后续命令，例如。

这里的错误代码来源于零叉八零零七零零零零按位或 error number，还原了 Windows 侧错误代码的风格。这里 UP 主使用了 slash bin slash ls 和 slash bin slash cat 以指定具体的 binary，是因为 UP 主设置了 ls 和 cat 的 alias 到 eza 和 bat，后者具有自己的错误处理逻辑。一般你无须添加 slash bin 前缀。

当然，你也可以直接将 Library obscure 注入到 Shell 中。

Python 中的错误字符串也会被替换。

对于网络解析的错误，例如 DNS 解析失败，走的是 g a i string error。Library obscure 故意忽略 e code，恒定返回 Windows Socket 的 W S A E connect refused。

当前版本的 library obscure 的目标平台是 g lib c Linux，不能确保 musl、BSD、macOS 上正常运行，也不能确保静态链接程序正常运行。Library obscure 不注入 set uid 和 set cap 程序。Library obscure 实现了 string error r 的 GNU 变体，不确保和 POSIX 等其他 ABI 的兼容性。至于 library obscure 的原理，可以参阅 GitHub 上的项目 README。

该项目使用 MIT License 开源。

---

还有，感谢以上两位主要开发者，绝大部分的贡献都是他们做的。

视频制作不易，恳请大家点赞关注，或者给项目一个 Star，让更多人吃上错误代码。
