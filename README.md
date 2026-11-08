# IOSwitch-NP

使用 NPC++ 实现的 IOSwitch 交换机程序，包含请求解析、块地址映射、请求交接、ACK/NAK 处理及交换机配表工具。

## 目录

- `defaultGroup/`：交换机数据面源码。
- `build/`：微码编译脚本与配置。
- `control/`：配表、配置检查和运行控制程序。
- `config/example.json`：配置示例。

## 编译

在已安装玄武平台和 SDK 的 NP 环境中执行：

```bash
cd /root/XuanwuPlatform/apps
git clone https://github.com/cjoiercjk/IOSwitch-NP.git IOSwitch
cd IOSwitch
cp ../l3fwd_demo/build/license.dat build/license.dat
bash build/build.sh
cmake -S control -B control/build
cmake --build control/build -j4
```

## 配置与运行

编辑 `config/example.json`：`routes` 设置 IP、MAC、出端口和队列；`flows` 设置客户端和接入控制器的 IP、QP、初始 PSN 和 epoch；`blocks` 设置地址桶对应的拥有者 IP。

```bash
./control/build/ioswitch_check_config config/example.json
./control/build/ioswitch_on_board --load config/example.json
```

程序加载交换机微码并下发表项。运行后输入 `R` 查看计数器，输入 `Q` 退出。
