
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <stdlib.h>
#include <stdio.h>

#include "MyTable.hpp"

enum{
    SPACING = 20,
    TOP_BAR_HEIGHT = 30,
    BUTTON_WIDTH = 80,
    BUTTON_HEIGHT = 30,
    INPUT_WIDTH = 80,
    INPUT_HEIGHT = 30,
    SMALL_INPUT_WIDTH = 40,
    SMALL_INPUT_HEIGHT = 30,
    TABLE_WIDTH = 600,
    TABLE_HEIGHT = 600,
    WINDOW_WIDTH = 
        4 * SPACING + TABLE_WIDTH + 2 * BUTTON_WIDTH,
    WINDOW_HEIGHT = 
        4 * SPACING + TABLE_HEIGHT + 2 * BUTTON_HEIGHT,
};

struct resizeArg{
    MyTable *t;
    Fl_Int_Input *in;
};

struct fillArg{
    MyTable *t;
    Fl_Int_Input *in_row;
    Fl_Int_Input *in_col;
};

struct valueArg{
    MyTable *t;
    Fl_Int_Input *i;
    Fl_Int_Input *j;
    Fl_Int_Input *val;
};

void ResizeColumnNumber(Fl_Widget *w, void *user){
    resizeArg *tmp = (resizeArg *)user; 
    tmp->t->Clear();
    tmp->t->setColCount(atoi(tmp->in->value()));
    tmp->t->Resize(TABLE_WIDTH, TABLE_HEIGHT);

}
void ResizeRowsNumber(Fl_Widget *w, void *user){
    resizeArg *tmp = (resizeArg *)user; 
    tmp->t->Clear();
    tmp->t->setRowCount(atoi(tmp->in->value()));
    tmp->t->Resize(TABLE_WIDTH, TABLE_HEIGHT);

}

void FillTable(Fl_Widget *w, void *user){
    fillArg *tmp = (fillArg *)user;
    tmp->t->Fill();
}

void SaveFile(Fl_Widget* widget, void* user) {
    Fl_File_Chooser *chooser = new Fl_File_Chooser(".", "*.{txt}", Fl_File_Chooser::CREATE, "aahw");
    chooser->show();
    while (chooser->shown())
       Fl::wait();
    if (chooser->value() != nullptr) {
        printf("Selected file: %s\n", chooser->value());
    }

    FILE *f = fopen(chooser->value(), "w");

    MyTable *table = (MyTable *)user;
    fprintf(f, "%ld %ld\n", table->getRowCount(), table->getColCount());
    for(size_t i = 0; i < table->getRowCount(); i++){
        for(size_t j = 0; j < table->getColCount(); j++)
            fprintf(f, "%ld ", table->getValue(i, j));
        fprintf(f, "\n");
    }

    fclose(f);
}

void OpenFile(Fl_Widget* widget, void* user) {
    Fl_File_Chooser *chooser = new Fl_File_Chooser(".", "*.{txt}", FL_SINGLE, "whaa");
    chooser->show();
    while (chooser->shown())
       Fl::wait();
    if (chooser->value() != nullptr) {
        printf("Selected file: %s\n", chooser->value());
    }

    FILE *f = fopen(chooser->value(), "r");

    int row = 0, col = 0, tmp = 0;
    fscanf(f, "%d %d", &row, &col);
    MyTable *table = (MyTable *)user;
    table->setRowCount(row);
    table->setColCount(col);
    table->Resize(TABLE_WIDTH, TABLE_HEIGHT);
    for(size_t i = 0; i < row; i++){
        for(size_t j = 0; j < row; j++){
            fscanf(f, "%d \n", &tmp);
            table->setValue(i, j, tmp);
        }
    }

    fclose(f);
}

void GetValue(Fl_Widget *, void *user){
    valueArg *tmp = (valueArg *)user;
    int res = tmp->t->getValue(
        atoi(tmp->i->value()),
        atoi(tmp->j->value())
    );
    char str[4];
    sprintf(str, "%d",res);
    tmp->val->value(str);
}

void SetValue(Fl_Widget *, void *user){
    valueArg *tmp = (valueArg *)user;
    tmp->t->setValue(
        atoi(tmp->i->value()),
        atoi(tmp->j->value()),
        atoi(tmp->val->value())
    );
    tmp->t->redraw();
}

void ClearTable(Fl_Widget *, void *user){
    ((MyTable *)user)->Clear();
    ((MyTable *)user)->redraw();
}

int main(){
    Fl_Window *win = new Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Simple Table");
        MyTable *table = new MyTable(SPACING, SPACING + TOP_BAR_HEIGHT, TABLE_WIDTH + 2, TABLE_HEIGHT + 2);

        Fl_Box *rowLabel = new Fl_Box(
            WINDOW_WIDTH - 2*BUTTON_WIDTH - 2*SPACING, 
            1*SPACING + 0*BUTTON_HEIGHT + TOP_BAR_HEIGHT,
            INPUT_WIDTH, INPUT_HEIGHT, "Rows");

        Fl_Box *colLabel = new Fl_Box(
            WINDOW_WIDTH - BUTTON_WIDTH - SPACING, 
            1*SPACING + 0*BUTTON_HEIGHT + TOP_BAR_HEIGHT,
            INPUT_WIDTH, INPUT_HEIGHT, "Columns");

        Fl_Int_Input *colField = new Fl_Int_Input(
            WINDOW_WIDTH - BUTTON_WIDTH - SPACING, 
            1*SPACING + 1*BUTTON_HEIGHT + TOP_BAR_HEIGHT,
            INPUT_WIDTH, INPUT_HEIGHT);

        Fl_Int_Input *rowField = new Fl_Int_Input(
            WINDOW_WIDTH - 2*BUTTON_WIDTH - 2*SPACING, 
            1*SPACING + 1*BUTTON_HEIGHT + TOP_BAR_HEIGHT,
            INPUT_WIDTH, INPUT_HEIGHT);

        Fl_Button *fillBtn = new Fl_Button(
            WINDOW_WIDTH - 2*BUTTON_WIDTH - 2*SPACING, 
            2*SPACING + 2*BUTTON_HEIGHT + TOP_BAR_HEIGHT,
            BUTTON_WIDTH, BUTTON_HEIGHT, "Fill");

        Fl_Button *clearBtn = new Fl_Button(
            WINDOW_WIDTH - BUTTON_WIDTH - SPACING, 
            2*SPACING + 2*BUTTON_HEIGHT + TOP_BAR_HEIGHT,
            BUTTON_WIDTH, BUTTON_HEIGHT, "Clear");

        Fl_Int_Input *iField = new Fl_Int_Input(
            TABLE_WIDTH + 1*SMALL_INPUT_WIDTH + 2*SPACING, 
            3*SPACING + 3*BUTTON_HEIGHT + TOP_BAR_HEIGHT,
            SMALL_INPUT_WIDTH, SMALL_INPUT_HEIGHT, "i = ");

        Fl_Int_Input *jField = new Fl_Int_Input(
            TABLE_WIDTH + 2*SMALL_INPUT_WIDTH + 5*SPACING, 
            3*SPACING + 3*BUTTON_HEIGHT + TOP_BAR_HEIGHT,
            SMALL_INPUT_WIDTH, SMALL_INPUT_HEIGHT, "j = ");

        Fl_Int_Input *valueField = new Fl_Int_Input(
            TABLE_WIDTH + 2*SMALL_INPUT_WIDTH + 3*SPACING, 
            4*SPACING + 3*BUTTON_HEIGHT + SMALL_INPUT_HEIGHT +TOP_BAR_HEIGHT,
            INPUT_WIDTH, SMALL_INPUT_HEIGHT, "New value ");

        Fl_Button *setValueBtn = new Fl_Button(
            WINDOW_WIDTH - 2*BUTTON_WIDTH - 2*SPACING, 
            5*SPACING + 5*BUTTON_HEIGHT + TOP_BAR_HEIGHT,
            BUTTON_WIDTH, BUTTON_HEIGHT, "Set Value");

        Fl_Button *getValueBtn = new Fl_Button(
            WINDOW_WIDTH - BUTTON_WIDTH - SPACING, 
            5*SPACING + 5*BUTTON_HEIGHT + TOP_BAR_HEIGHT,
            BUTTON_WIDTH, BUTTON_HEIGHT, "Get Value");

        resizeArg *col = new resizeArg{table, colField};
        resizeArg *row = new resizeArg{table, rowField};
        fillArg *fill = new fillArg{table, rowField, colField};
        valueArg *val = new valueArg{table, iField, jField, valueField};

        Fl_Menu_Bar *topBar = new Fl_Menu_Bar(0, 0, WINDOW_WIDTH, TOP_BAR_HEIGHT, "smth");
            topBar->add("File/Open", FL_CTRL + 'o', OpenFile, (void *)table);
            topBar->add("File/Save", FL_CTRL + 's', SaveFile, (void *)table);
            topBar->add("Table/Fill", FL_CTRL + 'f', FillTable, (void *)fill); 
            topBar->add("Table/Get Value", FL_CTRL + 'g', GetValue, (void *)val);
            topBar->add("Table/Set Value", FL_CTRL + 'v', SetValue, (void *)val);
            topBar->add("Table/Clear", FL_CTRL + 'r', ClearTable, (void *)table);

        colField->callback(ResizeColumnNumber, (void *)col);
        rowField->callback(ResizeRowsNumber, (void *)row);
        fillBtn->callback(FillTable, (void *)fill);
        clearBtn->callback(ClearTable, (void *)table);
        getValueBtn->callback(GetValue, (void *)val);
        setValueBtn->callback(SetValue, (void *)val);

        colField->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
        rowField->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
        
    win->end();
    win->show();
    return(Fl::run());
}

//
// End of "$Id$".
//

