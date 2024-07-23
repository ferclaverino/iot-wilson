# iot-caudalimeter

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
  ssh-keygen -t ed25519 -C "fernando.claverino@gmail.com"
  cat .ssh/id_ed25519.pub
  ```

  and add it to github

- Clone repo

  ```
  git clone git@github.com:ferclaverino/iot-caudalimeter.git
  ```

### Setup for 1st time

- Start containers

  ```
  cd iot-caudalimeter/raspberrypi
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
  - Get datasoure id and replace `$data-source-id` with new one`services/grafana/setup/dashboard.json`
  - Import `services/grafana/setup/dashboard.json`

- Create flow on node red
  - Import `services/nodered/setup/flows.json`
  - Deploy

## Install on Arduino

### Upload arduino with mock sketch

```
cd iot-caudalimeter/arduino/mock-serial-json
arduino-cli compile --fqbn arduino:avr:uno
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno
```

### Debug serial monitor

```
arduino-cli monitor -p /dev/ttyACM0
```

## During development

### Mount remote pi folder

#### Setup for 1st time

```
sudo apt install sshfs
mkdir ~/pi3/
```

#### Mount

```
sshfs -o default_permissions pi@pi3.local:/home/pi ~/pi3/
```

#### Unmount

```
fusermount3 -u ~/pi3/
```
