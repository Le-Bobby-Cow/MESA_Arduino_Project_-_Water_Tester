class Button {
   // Member Variables
   int x, y;
   PImage stillImg;
   boolean hov;
   // Multiple constructers for numbers and other buttons
   Button(int x, int y, PImage stillImg) {
      this.x = x;
      this.y = y;
      hov = false;
      this.stillImg = stillImg;
   }
   
   //Display Method
   void display() {
      image(stillImg, x, y);
   }
   
   void hover() {
      hov = mouseX > x+13-200/2 && mouseX < x+13+200/2 && mouseY > y+17-200/2 && mouseY < y+17+200/2;
   }
}
