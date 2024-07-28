# iot-wilson

## Install on Arduino

You can install and use one of the following three sketches:

- Mock test bench
  - Function: Publishes random metrics every 5 seconds.
  - Use Case: Ideal for testing integration with Node-RED and Grafana.
- Manual test bench:
  - Function: Allows you to control the water level in a tank using buttons.
  - Use Case: Useful for ensuring a consistent flow of 3 liters of water.
    You can measure the number of pulses from the flow meter and the time required for proper calibration.
- AUtomatic test bench:
  - Function: Measures water level in the tank using an ultrasonic sensor, maintaining an approximate volume between 1 and 4 liters.
  - Use Case: Suitable for running long-term tests to ensure stability and accuracy of measurements over extended periods.

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
