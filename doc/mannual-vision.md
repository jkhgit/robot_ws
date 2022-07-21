# vision

- camera: usb camera

- Usage

requirements
```
$ cd robot_ws
$ git checkout vision
$ python3 -m pip install -r src/stream/requirements.txt
```

terminal 1
```
$ ros2 run stream image_publisher
```

terminal 2
```
$ ros2 run stream image_subscriber
```
