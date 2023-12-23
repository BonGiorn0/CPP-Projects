//
// "$Id$"
//
//    Simple example of using Fl_Table - Greg Ercolano 11/29/2010
//
//    Demonstrates the simplest use of Fl_Table possible.
//    Display a 10x10 array of integers with row/col headers.
//    No interaction; simple display of data only.
//    See other examples for more complex interactions with the table.
//
// Copyright 2010 Greg Ercolano.
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
// 

#include "MyTable.hpp"

#define MAX_ROWS 201
#define MAX_COLS 201		// A-Z

// Derive a class from Fl_Table
// Draw the row/col headings
//    Make this a dark thin upbox with the text inside.
//
void MyTable::DrawHeader(const char *s, int X, int Y, int W, int H) {
  fl_push_clip(X,Y,W,H);
    fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, row_header_color());
    fl_color(FL_BLACK);
    fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
  fl_pop_clip();
} 
// Draw the cell data
//    Dark gray text on white background with subtle border
//
void MyTable::DrawData(int n, int X, int Y, int W, int H) {
  fl_push_clip(X,Y,W,H);
    // Draw cell bg
    if (n > 0){
      fl_color(FL_WHITE);
    }else{
      fl_color(FL_BLACK);
    }
    fl_rectf(X,Y,W,H);
    // Draw cell data
    //fl_color(FL_BLACK); fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
    // Draw box border
    fl_color(color()); fl_rect(X,Y,W,H);
  fl_pop_clip();
} 
// Handle drawing table's cells
//     Fl_Table calls this function to draw each visible cell in the table.
//     It's up to us to use FLTK's drawing functions to draw the cells the way we want.
//
void MyTable::draw_cell(TableContext context, int ROW=0, int COL=0, int X=0, int Y=0, int W=0, int H=0) {
  static char s[40];
  switch ( context ) {
    case CONTEXT_STARTPAGE:                   // before page is drawn..
      fl_font(FL_HELVETICA, 16);              // set the font for our drawing operations
      return; 
    case CONTEXT_COL_HEADER:                  // Draw column headers
      sprintf(s,"%c",'A'+COL);                // "A", "B", "C", etc.
      DrawHeader(s,X,Y,W,H);
      return; 
    case CONTEXT_ROW_HEADER:                  // Draw row headers
      sprintf(s,"%03d:",ROW);                 // "001:", "002:", etc
      DrawHeader(s,X,Y,W,H);
      return; 
    case CONTEXT_CELL:                        // Draw data in cells
      //sprintf(s,"%d",data[ROW][COL]);
      DrawData(data[ROW][COL],X,Y,W,H);
      return;
    default:
      return;
  }
}
// Constructor
//     Make our data array, and initialize the table options.
//
MyTable::MyTable(int X, int Y, int W, int H, const char *L=0) : Fl_Table(X,Y,W,H,L) {

  Clear();
  // Rows
  rows(rowCount);
  row_header(0);              // enable row headers (along left)
  row_height_all(60);         // default height of rows
  row_resize(0);              // disable row resizing
  // Cols
  cols(colCount);
  col_header(0);              // enable column headers (along top)
  col_width_all(60);          // default width of columns
  col_resize(0);              // enable column resizing
  end();			// end the Fl_Table group
}

void MyTable::setValue(int row, int col, int val){
  data[row][col] = val;
}
size_t MyTable::getValue(int row, int col) const{
  return data[row][col];
}

void MyTable::setRowCount(size_t val){

  rowCount = val;
}

void MyTable::setColCount(size_t val){
  colCount = val;
}

size_t MyTable::getRowCount() const{
  return rowCount;
}

size_t MyTable::getColCount() const{
  return colCount;
}

void MyTable::Fill(){
  if(rowCount != colCount)
    return;
  Clear();
  for(size_t i = 0, j = colCount, k = 0; i < j; i++, j--)
    for(size_t k = i; k < j; k++)
      data[i][k] = 0;
  redraw();
}

void MyTable::Resize(){
  rows(rowCount);
  cols(colCount);
}

void MyTable::Clear(){
  for ( int r=0; r<MAX_ROWS; r++ )
    for ( int c=0; c<MAX_COLS; c++ )
        data[r][c] = 1;
}
MyTable::~MyTable(){}
