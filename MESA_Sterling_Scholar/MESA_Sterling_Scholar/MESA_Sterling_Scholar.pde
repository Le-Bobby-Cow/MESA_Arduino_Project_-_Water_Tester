import processing.serial.*;

Serial myPort;  // Create object from Serial class

PImage openingScreen, homeIcon, settingsIcon, logIcon, notiIcon, wallpaper, accountIcon, questionIcon;
boolean open = true;
boolean question = false;
//float turbSkuff;
Button[] icons = new Button[9];
int savedTime;
int delayLength = 1000;
int delayLengthGraph = 1000;
boolean tab1, tab2, tab3, tab4 = false;
String input = ",,,,";      // Data received from the serial port
String[] splitInputs = {"", "", "", "", ""};
int arrLengths = 150;
float pHVal, ECVal, TempVal, TurbVal;
float[] pHVals = new float[arrLengths];
float[] ECVals = new float[arrLengths];
float[] TempVals = new float[arrLengths];
float[] TurbVals = new float[arrLengths];
int passedTime;
float maxpH, maxEC, maxTemp, maxTurb;



void setup() 
{
  try {
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
  } catch (Exception e) {
    stop();
  }
  savedTime = millis();
  frameRate(90000000);
  size(1180, 730);
  openingScreen = loadImage("1024px-Pokémon_Water_Type_Icon.svg.png");
  homeIcon = loadImage("IMG_1613.PNG");
  settingsIcon = loadImage("IMG_16131.PNG");
  logIcon = loadImage("IMG_16132.PNG");
  notiIcon = loadImage("IMG_16133.PNG");
  accountIcon = loadImage("IMG_16134.PNG");
  questionIcon = loadImage("IMG_16135.PNG");
  wallpaper = loadImage("blue-long-exposure-photo-of-body-of-water-lake-lake-image.jpeg");
  icons[0] = new Button(width/5, 665, homeIcon) ;
  icons[1] = new Button(width*2/5, 665, logIcon  ) ;
  icons[2] = new Button(width*3/5, 665, notiIcon) ;
  icons[3] = new Button(width*4/5, 665, settingsIcon) ;
  icons[4] = new Button(90, 158, accountIcon) ;
  icons[5] = new Button(30, 260, questionIcon) ;
  icons[6] = new Button(405, 260, questionIcon) ;
  icons[7] = new Button(30, 510, questionIcon) ;
  icons[8] = new Button(405, 510, questionIcon) ;
}

void draw()
{
  passedTime = millis() - delayLength;

  // Draw all data
  if (open==true) {
    frameRate(60);
    openScreen();
  } else {
    statScreen();
    bottomTab();

    if (tab1==true) {
      statScreen();
      bottomTab();
    }
    if (tab2==true) {
      logScreen();
      bottomTab();
    }
    if (tab3==true) {
      notiScreen();
      bottomTab();
    }
    if (tab4==true) {
      settingsScreen();
      bottomTab();
    }
  }
  if (icons[5].hov) {
    infopH();
  }
  if (icons[6].hov) {
    infoEC();
  }
  if (icons[7].hov) {
    infoTemp();
  }
  if (icons[8].hov) {
    infoTurb();
  }
}
void mousePressed() {
  if (icons[0].hov) {
    tab1 = true;
    tab2 = false;
    tab3 = false;
    tab4 = false;
  }
  if (icons[1].hov) {
    tab1 = false;
    tab2 = true;
    tab3 = false;
    tab4 = false;
  }
  if (icons[2].hov) {
    tab1 = false;
    tab2 = false;
    tab3 = true;
    tab4 = false;
  }
  if (icons[3].hov) {
    tab1 = false;
    tab2 = false;
    tab3 = false;
    tab4 = true;
  }
}
void drawGraphs() {

  // Draw all line graphs
  stroke(0);
  strokeWeight(2);
  fill(255);
  rect(50, 50, 300, 200);
  rect(50, 300, 300, 200);
  rect(425, 50, 300, 200);
  rect(425, 300, 300, 200);
  stroke(255, 0, 0);
  strokeWeight(2); 

  for (int i = 0; i < pHVals.length - 1; i++) {
    line(50 + i * 2, 50 + ((200 / maxpH) * (maxpH - pHVals[i])), 50 + (1 + i) * 2, 50 + ((200 / maxpH) * (maxpH - pHVals[i + 1])));
  }
  for (int i = 0; i < ECVals.length - 1; i++) {
    line(425 + i * 2, 50 + ((200 / maxEC) * (maxEC - ECVals[i])), 425 + (1 + i) * 2, 50 + ((200 / maxEC) * (maxEC - ECVals[i + 1])));
  }
  for (int i = 0; i < TempVals.length - 1; i++) {
    line(50 + i * 2, 300 + ((200 / maxTemp) * (maxTemp - TempVals[i])), 50 + (1 + i) * 2, 300 + ((200 / maxTemp) * (maxTemp - TempVals[i + 1])));
  }
  for (int i = 0; i < TurbVals.length - 1; i++) {
    line(425 + i * 2, 300 + ((200 / maxTurb) * (maxTurb - TurbVals[i])), 425 + (1 + i) * 2, 300 + ((200 / maxTurb) * (maxTurb - TurbVals[i + 1])));
  }

  // Draw rating graphs

  fill(0);
  stroke(255);
  textSize(20);
  textAlign(LEFT, BOTTOM);
  text("pH:" + nfs((pHVal), 1, 2), 50, 275);
  text("EC:" + nfs(ECVal, 1, 2), 425, 275);
  text("Temperature:" + nfs(TempVal, 1, 2), 50, 525);
  text("Turbidity:" + nfs(TurbVal, 0, 4), 425, 525);
  fill(255, 0, 0);
  stroke(0);
  rect(770, 50, 50, 500);
  fill(#FFA500);
  rect(770, 175, 50, 250);
  fill(#FFFF00);
  rect(770, 225, 50, 150);
  fill(0, 255, 0);
  rect(770, 250, 50, 100);
  fill(255);

  fill(255, 0, 0);
  stroke(0);
  rect(870, 50, 50, 500);
  fill(#FFA500);
  rect(870, 250, 50, 250);
  fill(#FFFF00);
  rect(870, 400, 50, 150);
  fill(0, 255, 0);
  rect(870, 500, 50, 50);

  fill(255, 0, 0);
  stroke(0);
  rect(970, 50, 50, 250);
  fill(255, 255, 0);
  rect(970, 300, 50, 100);
  fill(0, 255, 0);
  rect(970, 400, 50, 50);
  fill(0, 255, 255);
  rect(970, 450, 50, 50);
  fill(0, 0, 255);
  rect(970, 500, 50, 50);

  fill(255);
  rect(1070, 50, 50, 500);
  fill(255, 0, 0);
  stroke(0);
  rect(1070, 50, 50, 100);
  fill(#FFA500);
  rect(1070, 150, 50, 100);
  fill(#FFFF00);
  rect(1070, 250, 50, 100);
  fill(189, 255, 0);
  rect(1070, 350, 50, 100);
  fill(0, 255, 0);
  rect(1070, 450, 50, 100);


  fill(0);
  stroke(255);
  strokeWeight(8); 
  textSize(12);
  textAlign(CENTER, BOTTOM);
  text("pH", 795, 45);
  text("EC", 895, 45);
  text("Temp", 995, 45);
  text("Turb", 1095, 45);
  textAlign(LEFT, BOTTOM);
  fill(255, 255, 255, 150);
  strokeWeight(2);
  stroke(50);
  rect(824, 534 +7 - (500 * (pHVal / 14)), 35, 18 );
  rect(924, 534+7 - constrain((500 * (ECVal / 2000)), 0, 500), 43, 18 );
  rect(1024, 534+7 - (500 * (TempVal / 105)), 39, 18 );
  rect(1124, TurbVal-8, 36, 17 );
  stroke(255);
  strokeWeight(8); 
  fill(0);

  text(nf(pHVal, 1, 2), 828, 550 +7 - (500 * (pHVal / 14)));
  line(775, 550 - (500 * (pHVal / 14)), 815, 550 - (500 * (pHVal / 14)));
  text(nf(ECVal, 1, 2), 925, 550+7 - constrain((500 * (ECVal / 2000)), 0, 500) );  
  line(875, 550 - constrain((500 * (ECVal / 2000)), 0, 500), 915, 550 - constrain((500 * (ECVal / 2000)), 0, 500));
  text(nf(TempVal, 1, 2), 1027, 550+7 - (500 * (TempVal / 105)));  
  line(975, 550 - (500 * (TempVal / 105)), 1015, 550 - (500 * (TempVal / 105)));
  stroke(100);
  delayLength = 150;

  text(nf(TurbVal, 1, 2), 1128, TurbVal+7);  

  line(1075, TurbVal, 1115, TurbVal);
  textAlign(CENTER, BOTTOM);
}


void manageValues() {
  // Manage the input string
  if ((frameCount%4)==0) {
    pHVal = float(splitInputs[1]);
    ECVal = float(splitInputs[2]);
    TempVal = float(splitInputs[3]);
    TurbVal = float(splitInputs[4]);

    //Determine Max Values
    if (pHVal > maxpH) {
      maxpH = 5 * ceil(pHVal / 5);
    }
    if (ECVal > maxEC) {
      maxEC = 100 * ceil(ECVal / 100);
    }
    if (TempVal > maxTemp) {
      maxTemp = 10 * ceil(TempVal / 10);
    }
    if (TurbVal > maxTurb) {
      maxTurb = 100 * ceil(TurbVal / 100);
    }

    //Limit the readings values
    constrain(pHVal, 0, maxpH);
    constrain(ECVal, 0, maxEC);
    constrain(TempVal, 0, maxTemp);
    constrain(TurbVal, 0, maxTurb);

    //Shift data array
    for (int i = pHVals.length - 1; i > 0; i--) {
      pHVals[i] = pHVals[i - 1];
      ECVals[i] = ECVals[i - 1];
      TempVals[i] = TempVals[i - 1];
      TurbVals[i] = TurbVals[i - 1];
    }
    pHVals[0] = pHVal;
    ECVals[0] = ECVal;
    TempVals[0] = TempVal;
    TurbVals[0] = TurbVal;

    //Check for new high reading
    for (int i = 0; i < pHVals.length; i++) {
      float maxpHTemp = maxpH;
      float maxECTemp = maxEC;
      float maxTempTemp = maxTemp;
      float maxTurbTemp = maxTurb;

      if (pHVals[i] > maxpHTemp) {
        maxpHTemp = pHVals[i];
      }
      if (ECVals[i] > maxECTemp) {
        
        maxECTemp = ECVals[i];
      }
      if (TempVals[i] > maxTempTemp) {
        maxTempTemp = TempVals[i];
      }
      if (TurbVals[i] > maxTurbTemp) {
        maxTurbTemp = TurbVals[i];
      }

      maxpH = constrain(5 * ceil(maxpHTemp / 5), 0, 15);
      maxEC = 100 * ceil(maxECTemp / 100);
      maxTemp = 10 * ceil(maxTempTemp / 10);
      maxTurb = 1.3 * ceil(maxTurbTemp / 100);
    }
  }
}

void serialEvent(Serial myPort) { 
  input = myPort.readString();         // read it and store it in val
  input = trim(input);
  println(input);
  String[] prevVals = splitInputs;
  splitInputs = split(input, ',');
  if (splitInputs.length < 5) {
    splitInputs = prevVals;
  }
  manageValues();
} 

void openScreen() {
  imageMode(CENTER);
  background(54, 146, 220);
  textSize(82);
  fill(255);
  textAlign(CENTER);
  text("Water Purity Tester", 600, 270);
  textSize(20);
  text("Designed By: Vivek Anandh, Adrian Sucahyo, Ruiyu Zhang, Nick Zhao", 600, 530);
  image(openingScreen, 600, 400);
  if (passedTime > delayLength) {
    open=false;
    savedTime = millis();
  }
}
void statScreen() {
  background(200);
  imageMode(CORNER);
  image(wallpaper, 0, 0);
  manageValues();
  drawGraphs();
  imageMode(CENTER);
  icons[5].display();
  icons[5].hover();
  icons[6].display();
  icons[6].hover();
  icons[7].display();
  icons[7].hover();
  icons[8].display();
  icons[8].hover();
}
void bottomTab() {
  fill(20, 40, 60, 100);
  stroke(0);
  strokeWeight(3);
  rect(-10, 600, 1210, 150);
  for (int i=0; i<4; i++) {
    icons[i].display();
    icons[i].hover();
  }
}
void logScreen() {
  imageMode(CORNER);
  image(wallpaper, 0, 0);
  imageMode(CENTER);
  fill(20, 40, 60, 150);
  rect(50, 50, 1080, 500);
  fill(20, 40, 60);
  rect(50, 50, 1080, 70);
  textAlign(LEFT);
  fill(255);
  textSize(50);
  text("Water Quality Log", 65, 100);
  fill(255, 240);
  rect(50, 120, 1080, 75);

  fill(0);
  textSize(30);
  text("10:03 AM on June 21, 2021:", 65, 168);
  textSize(33);
  fill(255, 100, 0);
  text("Fair", 480, 170);

  fill(255, 240);
  rect(50, 195, 1080, 75);
  fill(0);
  textSize(30);
  text("09:57 AM on June 21, 2021:", 65, 243);
  textSize(33);
  fill(0, 150, 0);
  text("Excellent", 480, 245);

  fill(0, 150, 255);
  rect(980, 215, 135, 35);
  fill(0);
  textSize(15);
  text("View Exact Values", 983, 237);

  fill(255, 240);
  rect(50, 270, 1080, 75);
  fill(0);
  textSize(30);
  text("09:28 AM on June 21, 2021:", 65, 318);
  textSize(33);
  fill(255, 0, 0);
  text("Poor", 480, 320);
  fill(0);
  textSize(15);

  fill(0, 150, 255);
  rect(980, 290, 135, 35);
  fill(0);
  textSize(15);
  text("View Exact Values", 983, 312);

  fill(255, 240);
  rect(50, 345, 1080, 75);
  fill(0);
  textSize(30);
  text("09:58 PM on June 20, 2021:", 65, 393);
  textSize(33);
  fill(100, 200, 0);
  text("Good", 480, 395);
  fill(0);

  fill(0, 150, 255);
  rect(980, 365, 135, 35);
  fill(0);
  textSize(15);
  text("View Exact Values", 983, 387);

  fill(255, 240);
  rect(50, 420, 1080, 75);
  fill(0);
  textSize(30);
  text("04:03 PM on June 20, 2021:", 65, 470);
  textSize(33);
  fill(0, 150, 0);
  text("Excellent", 480, 473);
  fill(0);
  textSize(25);

  fill(0, 150, 255);
  rect(980, 440, 135, 35);
  fill(0);
  textSize(15);
  text("View Exact Values", 983, 462);

  fill(0, 150, 255);
  rect(980, 140, 135, 35);
  fill(0);
  textSize(15);
  text("View Exact Values", 983, 162);

  fill(0, 255, 0, 200);
  rect(50, 495, 1080, 55);
  fill(0);
  text("+ ", 535, 528);
  text("New Entry", 560, 530);
}
void notiScreen() {
  imageMode(CORNER);
  image(wallpaper, 0, 0);
  imageMode(CENTER);
  fill(20, 40, 60, 150);
  rect(50, 50, 1080, 500);
  fill(20, 40, 60);
  rect(50, 50, 1080, 70);
  textAlign(LEFT);
  fill(255);
  textSize(50);
  text("Notifications", 65, 100);
  fill(255, 240);
  rect(50, 120, 1080, 70);

  fill(255, 0, 0);
  textSize(40);
  text("Alert:", 65, 170);
  textSize(25);
  fill(0);
  text("EC, pH, and Turbidity values have changed significantly (1 min ago)", 175, 168);
  fill(0, 150, 255);
  rect(1025, 140, 80, 35);
  fill(0);
  textSize(15);
  text("Check Log", 1028, 162);

  fill(255, 240);
  rect(50, 190, 1080, 70);
  fill(255, 0, 0);
  textSize(40);
  text("Alert:", 65, 235);
  textSize(25);
  fill(0);
  text("EC and Turbidity values have changed significantly (17 min ago)", 175, 233);
  fill(0, 150, 255);
  rect(1025, 205, 80, 35);
  fill(0);
  textSize(15);
  text("Check Log", 1028, 227);

  fill(255, 0, 0, 200);
  rect(530, 515, 150, 25);
  fill(0);
  text("Clear Notifications", 540, 533);
}
void settingsScreen() {
  imageMode(CORNER);
  image(wallpaper, 0, 0);
  imageMode(CENTER);
  fill(20, 40, 60, 150);
  rect(50, 50, 1080, 500);
  fill(20, 40, 60);
  rect(50, 50, 1080, 70);
  textAlign(LEFT);
  fill(255);
  textSize(50);
  text("Settings", 65, 100);
  fill(255, 240);
  rect(50, 120, 1080, 75);

  fill(0);
  textSize(30);
  text("Skyline High School MESA Team", 125, 170);
  icons[4].display();
  icons[4].hover();
  fill(255, 240);
  rect(50, 195, 1080, 75);
  fill(0);
  textSize(30);
  text("Log Interval:", 65, 243);
  textSize(25);
  text("24 Hours", 245, 243);
  fill(0);
  textSize(15);

  fill(255, 240);
  rect(50, 270, 1080, 75);
  fill(0);
  textSize(30);
  text("Bluetooth:", 65, 318);
  textSize(25);
  fill(0, 255, 0);
  text("Connected", 220, 318);
  fill(0);
  textSize(15);

  fill(255, 240);
  rect(50, 345, 1080, 75);
  fill(0);
  textSize(30);
  text("Notification Settings", 65, 393);

  fill(255, 240);
  rect(50, 420, 1080, 75);
  fill(0);
  textSize(30);
  text("Tutorial", 65, 468);
  fill(0);
  textSize(25);

  fill(255, 0, 0, 200);
  rect(50, 495, 1080, 55);
  fill(0);
  text("Log Out", 560, 528);
}

void infopH() {
  fill(255);
  rect(50, 290, 395, 84);
  fill(0);
  textSize(17);
  textAlign(LEFT);
  text("The pH scale is used to specify the acidity or ", 55, 310);
  text("basicity of an aqueous solution. Drinking water ", 55, 330);
  text("should be 6.5 to 8.5 on the scale according to", 55, 350);
  text("the EPA.", 55, 370);
  textAlign(CENTER);
}
void infoEC() {
  fill(255);
  rect(425, 290, 393, 70);
  fill(0);
  textSize(17);
  textAlign(LEFT);
  text("EC is a measure of the solution's ability to ", 430, 310);
  text("conduct electricity. Drinking water should not ", 430, 330);
  text("exceed 400 μS/cm according to the WHO.", 430, 350);
  textAlign(CENTER);
}
void infoTemp() {
  fill(255);
  rect(50, 530, 393, 65);
  fill(0);
  textSize(17);
  textAlign(LEFT);
  text("Temperature is a measure of average kinetic", 55, 550);
  text("energy of atoms and molecules in a system. ", 55, 570);
  text("Drinking water should not exceed 160°F.", 55, 590);
  textAlign(CENTER);
}
void infoTurb() {
  fill(255);
  rect(425, 530, 375, 65);
  fill(0);
  textSize(17);
  textAlign(LEFT);
  text("Turbidity is the cloudiness of a fluid caused ", 430, 550);
  text("by particles. Drinking water should be below", 430, 570);
  text("1 NTU and never exceed 5 NTU.", 430, 590);
  textAlign(CENTER);
}
