float barX = 400.0f;
float barY = 950.0f;
float barVX = 5.0f;
float barWidth = 200.0f;
float barHeight = 30.0f;

//void moveBar(){
//  if ( keyPressed ) {
//    if ( keyCode == RIGHT ) {
//      barX = barX + barVX;
//    } else if ( keyCode == LEFT ) {
//      barX = barX - barVX;
//    }
//  }
//}

void moveBar(){
  if ( angle > 150 ) {
    barX = barX + barVX;
  } else if ( angle < 120 ) {
    barX = barX - barVX;
  }
}

void drawBar(){
  rect(barX, barY, barWidth, barHeight);
}
