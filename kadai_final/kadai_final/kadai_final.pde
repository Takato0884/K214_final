//student-number:2110136
//name:Takato Hayashi



import processing.serial.*;
Serial serial;
import ddf.minim.*;
Minim minim;
int angle;

void setup() {
  size(1280, 1024);
  arrangeBlocks();
  setup_ball();
  minim = new Minim(this);
  correctSE = minim.loadSample("./data/bgm/correct.mp3");
  incorrectSE = minim.loadSample("./data/bgm/incorrect.mp3");
  completeSE = minim.loadSample("./data/bgm/complete.mp3");
  serial = new Serial(this, "COM4", 9600);
}

void serialEvent(Serial port) {  
  if ( port.available() >= 3 ) {  // ヘッダ + 上位バイト + 下位バイト で合計３バイト
    if ( port.read() == 'H' ) {  // ヘッダ文字を見つけたところから読み取る
      int high = port.read();   // 上位バイト読み込み
      int low = port.read();    // 下位バイト読み込み
      int recv_data = high*256 + low;  // 上位・下位を合体させる
      angle = recv_data;
      println(recv_data);  // 結果の表示
    }
  }
}

void draw() {  
  background(54, 216, 55,1.5);
  
  //終了判定および表示項目
  if(blockHitFlag[0]==true && blockHitFlag[1]==true && blockHitFlag[2]==true && blockHitFlag[3]==true
      && blockHitFlag[4]==true && blockHitFlag[5]==true && blockHitFlag[6]==true && blockHitFlag[7]==true){
  //if(ans_blockHitFlag[0]==false){ //テスト用
      noLoop();
      completeSE.trigger();
      fill(255,0,204);
      textSize(300);
      text("CLEAR",width/2-450,height/2);  
      fill(255);
      textSize(50);
      int time = millis() - base_time;
      text("your time", 700, 600);
      fill(255);
      text(time/1000.0, 1000, 600);
    } else {
          fill(255);
          textSize(50);
          int time = millis() - base_time;
          text(time/1000.0, 1000, 600);
    }

  for (int i = 0; i < MAX_BALLS; i++ ) {
      /* BallとBarの衝突判定 */
      if (ballY[i] > barY && ballY[i] < barY + barHeight) {
        if (ballX[i] > barX && ballX[i] < barX + barWidth/2) {
          ballVY[i] = -ballVY[i];
          if (ballVX[i]>0){
            ballVX[i] = -ballVX[i];
          }else{
            ballVX[i] = ballVX[i];
          }          
        }else if(ballX[i] > barX + barWidth/2 && ballX[i] < barX + barWidth){
          ballVY[i] = -ballVY[i];
          if (ballVX[i]<0){
            ballVX[i] = -ballVX[i];
          }else{
            ballVX[i] = ballVX[i];
          }
        }
      }
  }

  /* Ballと複数Blockの衝突判定 */
  for ( int i = 0; i < MAX_BLOCKS; i++ ) {
    for ( int j = 0; j < MAX_BALLS; j++ ) {
      if  ( blockHitFlag[i] == false ) {
        if ( ballX[j] > blockX[i] && ballX[j] < blockX[i] + blockWidth[i] ) {
          if ( ballY[j] > blockY[i] && ballY[j] < blockY[i] + blockHeight[i] ) {
            ballVY[j] = -ballVY[j];     
            blockHitFlag[i] = true;
            correctSE.trigger();
          }
        }
    }
    }
  }
  
 //if (serial.available() > 0){
 //   char angle = serial.readChar();
 //   print((angle));
 // }
  

  /* Ball */
  moveBall();
  drawBall();

  /* Bar */
  moveBar();
  drawBar();

  /* Block */
  moveBlocks();
  drawBlocks();
}
