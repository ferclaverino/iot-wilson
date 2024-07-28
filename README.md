# iot-wilson

## Install on Arduino

You can instal on arduino 3 possible sketches:

- Tesch bench mock:
  It publishes random metrics every 5 seconds.
  This is usefull test integration with nodered and granafa.
- Tesch bench manual:
  You control water level on tank using buttons.
  This is usefull for making sure you are always passing 3L of water.
  So you can measure counter of pulses published on caudalitemer and time to do proper calibration.
- tesch bench manual:
  Water level on tank is controlled by mesuring distance using ultrasonic sensor.
  It will be between 4L and 1L aprox and provifing and aproximate volume of 3L.
  This i usefull to run test bench for hours and make sure measures are stable
  and everything works well against long periods of time.

### Upload mock test bench

```
arduino-cli compile --fqbn arduino:avr:uno test-bench-caudalimeter-mock && arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno test-bench-caudalimeter-mock
```

### Upload manual test bench

```
arduino-cli compile --fqbn arduino:avr:uno test-bench-caudalimeter-manual && arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno test-bench-caudalimeter-manual
```

### Upload automatic test bench

```
arduino-cli compile --fqbn arduino:avr:uno test-bench-caudalimeter-auto && arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno test-bench-caudalimeter-auto && arduino-cli monitor -p /dev/ttyACM0
```

## Install on Raspberry

### Install Raspberry Pi OS lite

Follow https://raspberrytips.com/install-raspberry-pi-imager-ubuntu/.
I recommend the manual installation to get latest version.

### Install arduino-cli on raspberry pi

- https://arduino.github.io/arduino-cli/1.0/installation/
- https://arduino.github.io/arduino-cli/1.0/getting-started/

### Install iot stack on raspberry pi

- Connect

  ```
  ssh pi3.local
  ```

- Update apt

  ```
  sudo apt update
  sudo apt upgrade
  ```

- Install docker

  ```
  curl -fsSL https://get.docker.com | sh
  sudo usermod -aG docker $USER
  exit
  ```

- Generate ssh

  ```
  ssh-keygen -t ed25519 -C "${your email}"
  cat .ssh/id_ed25519.pub
  ```

  and add it to your github account

- Clone repo

  ```
  git clone git@github.com:ferclaverino/iot-wilson.git
  ```

### Setup for 1st time

- Start containers

  ```
  cd iot-wilson/raspberrypi
  docker compose up
  ```

- Create database on influxdb

  ```
  docker compose exec -it influxdb influx
  create database wilson
  exit
  ```

- Create dashboard on grafana

  - Create datasource
    - url: http://influxdb:8086
    - database: wilson
  - Get datasoure id and replace `${data-source-id}` with new one`services/grafana/setup/dashboard.json`
  - Import `services/grafana/setup/dashboard.json`

- Create flow on node red
  - Import `services/nodered/setup/flows.json`
  - Deploy

## During development

### Upload any arduino sketch

```
cd iot-wilson/arduino/
arduino-cli compile --fqbn arduino:avr:uno ${arduino-sketch}
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno ${arduino-sketch}
```

### Debug serial monitor

```
arduino-cli monitor -p /dev/ttyACM0
```
