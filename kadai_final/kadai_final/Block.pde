//MAX_BLOCKS
final int MAX_BLOCKS = 8;

float[] blockX = new float[MAX_BLOCKS];
float[] blockY = new float[MAX_BLOCKS];

float[] blockWidth = new float[MAX_BLOCKS];
float[] blockHeight = new float[MAX_BLOCKS];
boolean[] blockHitFlag = new boolean[MAX_BLOCKS];

final int BLOCK_ROWS  =  4;  // ブロックの横一列の個数
final int BLOCK_GAP  =  4;    // ブロックとブロックの間隔

void moveBlocks() {
  // Blockは動かない
}

/* Blockの描画処理 */
void drawBlocks() {
  for (int i = 0; i < MAX_BLOCKS; i++ ) {
    if ( blockHitFlag[i]  ==  false ) {
      fill(139, 69, 19);
      rect(blockX[i], blockY[i], blockWidth[i], blockHeight[i]);
    }
  }
}

/* Blockの配置処理 */
void arrangeBlocks() {
  
  int i = 0;
  while ( i < MAX_BLOCKS ) {
    blockWidth[i] = 316.0f;
    blockHeight[i] = 45.0f;
    blockHitFlag[i] = false;
    blockX[i] = BLOCK_GAP + i % BLOCK_ROWS * (blockWidth[i] + BLOCK_GAP);
    blockY[i] =  i / BLOCK_ROWS * (blockHeight[i] + BLOCK_GAP);
    i++;
  }
}
