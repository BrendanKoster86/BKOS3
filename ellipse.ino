/*
 * Code gekopieerd van TFT_eSPI om deze toe te kunnen passen voor het kleine scherm
 */

#if scherm_ili == 9488
  void drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
    tft.drawEllipse(x0, y0, rx, ry, color);
  }
  void fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
    tft.fillEllipse(x0, y0, rx, ry, color);
  }
#elif scherm_ili == 9341
  void drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color)
  {
    if (rx<2) return;
    if (ry<2) return;
    int32_t x, y;
    int32_t rx2 = rx * rx;
    int32_t ry2 = ry * ry;
    int32_t fx2 = 4 * rx2;
    int32_t fy2 = 4 * ry2;
    int32_t s;
  
    //begin_tft_write();          // Sprite class can use this function, avoiding begin_tft_write()
//    tft.inTransaction = true;
  
    for (x = 0, y = ry, s = 2*ry2+rx2*(1-2*ry); ry2*x <= rx2*y; x++) {
      // These are ordered to minimise coordinate changes in x or y
      // drawPixel can then send fewer bounding box commands
      tft.drawPixel(x0 + x, y0 + y, color);
      tft.drawPixel(x0 - x, y0 + y, color);
      tft.drawPixel(x0 - x, y0 - y, color);
      tft.drawPixel(x0 + x, y0 - y, color);
      if (s >= 0) {
        s += fx2 * (1 - y);
        y--;
      }
      s += ry2 * ((4 * x) + 6);
    }
  
    for (x = rx, y = 0, s = 2*rx2+ry2*(1-2*rx); rx2*y <= ry2*x; y++) {
      // These are ordered to minimise coordinate changes in x or y
      // drawPixel can then send fewer bounding box commands
      tft.drawPixel(x0 + x, y0 + y, color);
      tft.drawPixel(x0 - x, y0 + y, color);
      tft.drawPixel(x0 - x, y0 - y, color);
      tft.drawPixel(x0 + x, y0 - y, color);
      if (s >= 0)
      {
        s += fy2 * (1 - x);
        x--;
      }
      s += rx2 * ((4 * y) + 6);
    }
  
//    tft.inTransaction = lockTransaction;
//    tft.end_tft_write();              // Does nothing if Sprite class uses this function
  }
  
  
  /***************************************************************************************
  ** Function name:           fillEllipse
  ** Description:             draw a filled ellipse
  ***************************************************************************************/
  void fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color)
  {
    if (rx<2) return;
    if (ry<2) return;
    int32_t x, y;
    int32_t rx2 = rx * rx;
    int32_t ry2 = ry * ry;
    int32_t fx2 = 4 * rx2;
    int32_t fy2 = 4 * ry2;
    int32_t s;
  
    //begin_tft_write();          // Sprite class can use this function, avoiding begin_tft_write()
//    tft.inTransaction = true;
  
    for (x = 0, y = ry, s = 2*ry2+rx2*(1-2*ry); ry2*x <= rx2*y; x++) {
      tft.drawFastHLine(x0 - x, y0 - y, x + x + 1, color);
      tft.drawFastHLine(x0 - x, y0 + y, x + x + 1, color);
  
      if (s >= 0) {
        s += fx2 * (1 - y);
        y--;
      }
      s += ry2 * ((4 * x) + 6);
    }
  
    for (x = rx, y = 0, s = 2*rx2+ry2*(1-2*rx); rx2*y <= ry2*x; y++) {
      tft.drawFastHLine(x0 - x, y0 - y, x + x + 1, color);
      tft.drawFastHLine(x0 - x, y0 + y, x + x + 1, color);
  
      if (s >= 0) {
        s += fy2 * (1 - x);
        x--;
      }
      s += rx2 * ((4 * y) + 6);
    }
  
//    tft.inTransaction = lockTransaction;
//    tft.end_tft_write();              // Does nothing if Sprite class uses this function
  }
#endif
