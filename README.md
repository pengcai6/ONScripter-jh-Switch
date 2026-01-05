# **ONScripter-jh for Nintendo Switch**

[![Version](https://img.shields.io/badge/version-2.1.0-blue.svg)](https://github.com/wetor/ONScripter-jh-Switch/releases)
[![License](https://img.shields.io/badge/license-GPL--2.0-green.svg)](COPYING)
[![Platform](https://img.shields.io/badge/platform-Nintendo%20Switch-red.svg)]()

## **简介 / Introduction**

ONScripter-jh for Nintendo Switch 是一个用于在 Nintendo Switch 上运行 NScripter 脚本游戏的开源模拟器。

- **ONScripter**（Open Source NScripter）是一个用来解析 NScripter 脚本的第三方开源 Galgame 游戏引擎
- **ONScripter-jh** 是 jh10001 在原有 ONS 基础上进行修改的版本，提供更好的性能和中文支持
- **ONScripter-jh for Switch** 是 wetor 移植的 SDL2 分支，用于在 Nintendo Switch 平台运行 ONS 游戏

---

## **版本信息 / Version Info**

| 组件           | 版本     |
| -------------- | -------- |
| ONS NX Version | 2.1.0    |
| ONS JH Version | 0.7.6    |
| ONS Version    | 20250115 |
| NSC Version    | 2.96     |
| C++ Standard   | C++17    |

---

## **更新日志 / Update Logs**

### 2025.1.15 - Version 2.1.0

- 🔧 升级到 C++17 标准
- 🔧 更新编译器优化选项（支持 ARMv8-A CRC + Crypto）
- 🔧 改进日志系统，支持多级别日志输出
- 🔧 更新系统配置以支持更新的 Switch 固件
- 🔧 代码现代化和清理
- 🐛 修复多处潜在的内存问题
- 📝 更新文档

### 2021.7.5

- Support English games
  Install && Switch language:
  1. Put the "onsemu" in the "SDFile" folder into the root directory of the sd card
  2. Install "ONSBrowser-install-05293394190000.nsp"
  3. Put the ONS games folder in "onsemu"
  4. Run "ONScripter", and press joycon "Plus +" button, the first setting is language switching
  5. Enjoy!

### 2021.7.3 GUI ver.2.0

- **修复 12.0 以上系统无法打开的问题**
- 修复退出游戏无法返回 GUI 并且报错的问题

### 2019.10.3 GUI ver.1.1

- 修复游戏数量小于 5 个时打开启动器错误的问题
- 修复部分游戏存档错误问题

---

## **功能特性 / Features**

- ✅ 支持大多数 ONScripter/NScripter 游戏
- ✅ 中文/日文/英文游戏支持
- ✅ 视频播放支持（通过 SDL_kitchensink/FFmpeg）
- ✅ 高性能 SIMD (ARM NEON) 优化
- ✅ Lua 脚本支持
- ✅ 全屏/窗口模式切换
- ✅ 字体描边渲染
- ✅ 存档功能

---

## **系统要求 / Requirements**

- Nintendo Switch（已破解，支持自制软件）
- Atmosphere 或其他自制固件
- 支持的固件版本：9.0.0+（推荐使用最新版本）

---

## **下载地址 / Download**

**请先查看安装说明**

- **GitHub Releases**: https://github.com/wetor/ONScripter-jh-Switch/releases/latest
- **百度网盘**: https://pan.baidu.com/s/1lFaTjYLOPluEe8YFBPmW4w 提取码: e8q7

---

## **安装说明 / Installation**

### **安装模拟器**

1. 将 SDFile 文件夹中的 `onsemu` 放入内存卡根目录（和 switch 文件夹同级）
2. 安装 `ONSBrowser-install-0529293394190000.nsp`
3. 桌面即可出现快捷方式

### **安装游戏**

1. 从网上下载 ONS 游戏包（不区分平台，只要是 ONScripter 模拟器能运行的游戏资源就可以）

2. 检查游戏资源是否完整：
   - 必须存在以下文件之一：`0.txt`、`00.txt`、`nscript.dat`
   - 可能存在：`*.nsa`、`*.sar` 文件
   - 大部分存在：`icon0.png`

3. 将游戏资源文件夹用**英文字符**重命名，放至 SD 卡的 `onsemu` 文件夹中
   - 例如：`SDCard:/onsemu/Rewrite/00.txt`

⚠️ **注意事项**：

- 游戏文件夹名称**不能使用中文字符**，否则将无法正常识别
- 如果仍然出错，可以使用其他平台的 ONS 模拟器测试同一资源包

---

## **使用说明 / Usage**

### **控制方式**

| 按键   | 功能         |
| ------ | ------------ |
| A      | 确认/前进    |
| B      | 取消/返回    |
| +      | 打开设置菜单 |
| L      | 查看帮助     |
| 左摇杆 | 移动光标     |
| 触摸屏 | 触摸操作     |

### **快速启动**

如需制作游戏的单独前端，可使用 Releases 中附带的工具：

- 工具来源：https://gitlab.com/martinpham/NSP-Forwarder

或者修改模拟器源代码，将游戏资源打包进 romfs。

---

## **编译说明 / Building**

### **环境要求**

- devkitPro（包含 devkitA64）
- libnx 4.0.0 或更高版本
- switch-portlibs（SDL2、FFmpeg 等）

### **编译步骤**

```bash
# 设置 devkitPro 环境变量
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM
export DEVKITPPC=$DEVKITPRO/devkitPPC

# 克隆项目
git clone https://github.com/wetor/ONScripter-jh-Switch.git
cd ONScripter-jh-Switch

# 初始化子模块
git submodule update --init --recursive

# 编译
make -j$(nproc)
```

编译完成后会生成 `ONScripter.nro` 文件。

---

## **截图 / Screenshots**

<img src="./screenshot/2.jpg" width="45%" /> <img src="./screenshot/3.jpg" width="45%" />
<img src="./screenshot/4.jpg" width="45%" /> <img src="./screenshot/5.jpg" width="45%" />
<img src="./screenshot/1.jpg" width="45%" />

---

## **相关链接 / Related Links**

| 项目                    | 链接                                           |
| ----------------------- | ---------------------------------------------- |
| 原版 ONScripter 官网    | https://onscripter.osdn.jp/onscripter.html     |
| ONScripter-jh 项目      | https://bitbucket.org/jh10001/onscripter-jh    |
| ONS for PSVita          | https://github.com/wetor/ONScripter-jh-PSVita  |
| ONS for Switch 演示视频 | https://www.bilibili.com/video/av68622183/     |
| ONS Switch GUI          | https://github.com/wetor/ONS-Switch-GUI        |
| 博客链接                | https://blog.wetorx.cn/post/onscripter-ns.html |

---

## **许可证 / License**

本项目基于 GNU General Public License v2.0 许可证发布。详见 [COPYING](COPYING) 文件。

---

## **贡献者 / Contributors**

- **Ogapee** - 原版 ONScripter 作者
- **jh10001** - ONScripter-jh 维护者
- **wetor** - Nintendo Switch 移植

---

## **问题反馈 / Issues**

如有问题，请在 [GitHub Issues](https://github.com/wetor/ONScripter-jh-Switch/issues) 提交反馈。

提交问题时请提供：

1. Switch 固件版本
2. 使用的游戏名称
3. 错误信息或截图
4. 复现步骤
