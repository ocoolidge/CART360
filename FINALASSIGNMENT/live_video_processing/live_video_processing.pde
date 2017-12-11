import gab.opencv.*;
import processing.video.*;
import java.awt.*;
import processing.serial.*;

Serial myPort;

Capture video;
OpenCV opencvFrontFace;

static int BLACK_STRAIGHT_ON = 5;
static int BLACK_DIAGONAL_ON = 6;
static int RED_1_ON = 7;
static int RED_2_ON = 8;
static int RED_3_ON = 9;

static int BLACK_STRAIGHT_OFF = 0;
static int BLACK_DIAGONAL_OFF = 1;
static int RED_1_OFF = 2;
static int RED_2_OFF = 3;
static int RED_3_OFF = 4;



void setup() {
  size(640, 480);
  
  String[] cameras = Capture.list();
  String portName = Serial.list()[3];
  
  myPort = new Serial(this, portName, 9600);
  
  video = new Capture(this, 640/2, 480/2, 15);
  
  //video = new Capture(this, cameras[0]);
  
  //getCameraList();
  
  opencvFrontFace = new OpenCV(this, 640/2, 480/2);
 
  opencvFrontFace.loadCascade(OpenCV.CASCADE_FRONTALFACE); 
 
  video.start();
  
  printArray(Serial.list());
}

void draw() {
  scale(2);
  opencvFrontFace.loadImage(video);
  
  image(video, 0, 0 );

  noFill();
  strokeWeight(2);
  
  Rectangle[] frontFaces = opencvFrontFace.detect();
 
  stroke(0, 255, 0);
  
  for (int i = 0; i < frontFaces.length; i++) {
    //println(" " + frontFaces[i].x + ", " + frontFaces[i].y);
    rect(frontFaces[i].x, frontFaces[i].y, frontFaces[i].width, frontFaces[i].height);
  }
  if(frontFaces.length <= 0){
    myPort.write(RED_1_OFF);
    myPort.write(RED_2_OFF);
    myPort.write(RED_3_OFF);
    println("RED_1: OFF  RED_2: OFF  RED_3: OFF  ");
  }
  if(frontFaces.length >= 2){
    myPort.write(RED_1_ON);
    myPort.write(RED_2_OFF);
    myPort.write(RED_3_OFF);
    println("RED_1: ON  RED_2: OFF  RED_3: OFF  ");
  }else if(frontFaces.length >= 2){
    myPort.write(RED_1_ON);
    myPort.write(RED_2_ON);
    myPort.write(RED_3_OFF);
    println("RED_1: ON  RED_2: ON  RED_3: OFF  ");
  }else if(frontFaces.length >= 1){
    myPort.write(RED_1_ON);
    myPort.write(RED_2_ON);
    myPort.write(RED_3_ON);
    println("RED_1: ON  RED_2: ON  RED_3: ON  ");
  }
  
  //println(frontFaces.length);
}

void captureEvent(Capture c) {
  c.read();
}

void getCameraList(){
  String[] cameras = Capture.list();
 
  if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  }else {
    println("Available cameras:");
    for (int i = 0; i < cameras.length; i++) {
      println(i + cameras[i]);
    }
  }
}