import gab.opencv.*;
import processing.video.*;
import java.awt.Rectangle;
import processing.serial.*;
import ddf.minim.*;

Capture cam;
OpenCV opencv;
Serial myPort;
Minim minim;
AudioPlayer player;

void setup() {
  size(640, 480);

  // 初始化摄像头
  String[] cameras = Capture.list();
  if (cameras.length == 0) {
    println("没有检测到摄像头。");
    exit();
  } else {
    cam = new Capture(this, cameras[1]);
    cam.start();
  }

  // 初始化 OpenCV 和人脸检测
  opencv = new OpenCV(this, 640, 480);
  opencv.loadCascade(OpenCV.CASCADE_FRONTALFACE);  

  // 设置串口
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);

  // 初始化音频播放
  minim = new Minim(this);
  player = minim.loadFile("Tingsha.mp3");  // 替换为您的音频文件名
  player.loop();
}

void draw() {
  if (cam.available() == true) {
    cam.read();
  }
  opencv.loadImage(cam);

  // 检测人脸
  Rectangle[] faces = opencv.detect();
  image(cam, 0, 0);

  if (faces.length > 0) {
    // 检测到人脸
    myPort.write('W'); // 发送信号点亮白色 LED
    player.setGain(0); // 设置正常音量
    if (!player.isPlaying()) {
      player.rewind();
      player.play();
    }
  } else {
    // 未检测到人脸
    myPort.write('O'); // 发送信号点亮橙色 LED
    player.setGain(-10); // 设置较低的音量
  }
}

void stop() {
  player.close();
  minim.stop();
  super.stop();
}
