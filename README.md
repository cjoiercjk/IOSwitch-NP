# IOSwitch-NP

An NPC++ implementation of IOSwitch, including request parsing, block address mapping, request handoff, ACK/NAK processing, and switch configuration tools.

## Directory Structure

- `defaultGroup/`: Switch data plane source code.
- `build/`: Microcode build scripts and configuration.
- `control/`: Table configuration, configuration validation, and runtime control programs.
- `config/example.json`: Example configuration.

## Build

Run the following commands on an NP system with the Xuanwu platform and SDK installed:

```bash
cd /root/XuanwuPlatform/apps
git clone https://github.com/cjoiercjk/IOSwitch-NP.git IOSwitch
cd IOSwitch
cp ../l3fwd_demo/build/license.dat build/license.dat
bash build/build.sh
cmake -S control -B control/build
cmake --build control/build -j4
```

## Configure and Run

Edit `config/example.json`: `routes` defines IP addresses, MAC addresses, output ports, and queues; `flows` defines client and access-controller IP addresses, QPs, initial PSNs, and epochs; `blocks` maps address buckets to owner IP addresses.

```bash
./control/build/ioswitch_check_config config/example.json
./control/build/ioswitch_on_board --load config/example.json
```

The program loads the switch microcode and installs table entries. Enter `R` to view counters or `Q` to exit.
