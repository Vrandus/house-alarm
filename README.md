# house-alarm
Basic IoT house alarm for raspberry pi in C


## Wiring

**double check IR sensor inputs and outputs before connecting +5**

![image](https://puu.sh/C8kb6/4d7de21abb.jpg)

## Install
In terminal

```bash
git clone https://github.com/Vrandus/house-alarm.git
```

## Usage

Runs housealarm until indefinitely(until killed `^C`)

```bash
./houseAlarm
```

## setting up ifttt emails

in `HouseAlarm.c`

```C
/* replace with your own webhook key
can be found at: https://ifttt.com/services/maker_webhooks/settings
*/

ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/<YOUR KEY>", <VAL1>, <VAL2>, <VAL3>);
```

afterwards, execute `Makefile`

```bash
make all
```
