#include <gtk/gtk.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <string.h>
#include "../image_processing/display.h"
#include "../image_processing/pixel_operations.h"

#include "../image_processing/SDL_rotozoom.h"
#include "../image_processing/binarize.h"
#include "../image_processing/filters.h"
#include "../image_processing/rotate.h"

#include "../sudoku-solver-c/txt_file_2_grid.c"
#include "../sudoku-solver-c/solver.c"
#include "../sudoku-solver-c/display.c"

#include "../test_NN/softmax.h"
#include "../training_NN/relu.h"

#include "../Detection/rlsa.h"
#include "../Detection/cut.h"
#include "../Detection/matrix.h"


typedef struct UserInterface
{
    GtkWindow* window;              // Main window
    GtkButton* start_button;        // Start button
    GtkFileChooserButton* file;     //file chooser button
    GtkGrid* grid ;                 //gtk grid
    int *init_grid;                 //pointer to initial grid
    int *res_grid;                  //pointer to result grid 
    guint event; 
    GtkEventBox* event_box;
    //ROW 0
    GtkWidget *label_0_0;
    GtkWidget *label_1_0;
    GtkWidget *label_2_0;
    GtkWidget *label_3_0;
    GtkWidget *label_4_0;
    GtkWidget *label_5_0;
    GtkWidget *label_6_0;
    GtkWidget *label_7_0;
    GtkWidget *label_8_0;
    //ROW 1
    GtkWidget *label_0_1;
    GtkWidget *label_1_1;
    GtkWidget *label_2_1;
    GtkWidget *label_3_1;
    GtkWidget *label_4_1;
    GtkWidget *label_5_1;
    GtkWidget *label_6_1;
    GtkWidget *label_7_1;
    GtkWidget *label_8_1;
    //ROW 2
    GtkWidget *label_0_2;
    GtkWidget *label_1_2;
    GtkWidget *label_2_2;
    GtkWidget *label_3_2;
    GtkWidget *label_4_2;
    GtkWidget *label_5_2;
    GtkWidget *label_6_2;
    GtkWidget *label_7_2;
    GtkWidget *label_8_2;
    //ROW 3
    GtkWidget *label_0_3;
    GtkWidget *label_1_3;
    GtkWidget *label_2_3;
    GtkWidget *label_3_3;
    GtkWidget *label_4_3;
    GtkWidget *label_5_3;
    GtkWidget *label_6_3;
    GtkWidget *label_7_3;
    GtkWidget *label_8_3;
    //ROW 4
    GtkWidget *label_0_4;
    GtkWidget *label_1_4;
    GtkWidget *label_2_4;
    GtkWidget *label_3_4;
    GtkWidget *label_4_4;
    GtkWidget *label_5_4;
    GtkWidget *label_6_4;
    GtkWidget *label_7_4;
    GtkWidget *label_8_4;
    //ROW 5
    GtkWidget *label_0_5;
    GtkWidget *label_1_5;
    GtkWidget *label_2_5;
    GtkWidget *label_3_5;
    GtkWidget *label_4_5;
    GtkWidget *label_5_5;
    GtkWidget *label_6_5;
    GtkWidget *label_7_5;
    GtkWidget *label_8_5;
    //ROW 6
    GtkWidget *label_0_6;
    GtkWidget *label_1_6;
    GtkWidget *label_2_6;
    GtkWidget *label_3_6;
    GtkWidget *label_4_6;
    GtkWidget *label_5_6;
    GtkWidget *label_6_6;
    GtkWidget *label_7_6;
    GtkWidget *label_8_6;
    //Row 7
    GtkWidget *label_0_7;
    GtkWidget *label_1_7;
    GtkWidget *label_2_7;
    GtkWidget *label_3_7;
    GtkWidget *label_4_7;
    GtkWidget *label_5_7;
    GtkWidget *label_6_7;
    GtkWidget *label_7_7;
    GtkWidget *label_8_7;
    //ROW 8
    GtkWidget *label_0_8;
    GtkWidget *label_1_8;
    GtkWidget *label_2_8;
    GtkWidget *label_3_8;
    GtkWidget *label_4_8;
    GtkWidget *label_5_8;
    GtkWidget *label_6_8;
    GtkWidget *label_7_8;
    GtkWidget *label_8_8;

} UserInterface;

//labels_c_l
GtkWidget* returnwidget(gpointer user_data , int i)
{
    UserInterface* ui = user_data;
    if(i==0)
        return (ui -> label_0_0);
    if(i==1)
        return (ui -> label_1_0);
    if(i==2)
        return (ui -> label_2_0);
    if(i==3)
        return (ui -> label_3_0);
    if(i==4)
        return (ui -> label_4_0);
    if(i==5)
        return (ui -> label_5_0);
    if(i==6)
        return (ui -> label_6_0);
    if(i==7)
        return (ui -> label_7_0);
    if(i==8)
        return (ui -> label_8_0);
    if(i==9)
        return (ui -> label_0_1);
    if(i==10)
        return (ui -> label_1_1);
    if(i==11)
        return (ui -> label_2_1);
    if(i==12)
        return (ui -> label_3_1);
    if(i==13)
        return (ui -> label_4_1);
    if(i==14)
        return (ui -> label_5_1);
    if(i==15)
        return (ui -> label_6_1);
    if(i==16)
        return (ui -> label_7_1);
    if(i==17)
        return (ui -> label_8_1);
    if(i==18)
        return (ui -> label_0_2);
    if(i==19)
        return (ui -> label_1_2);
    if(i==20)
        return (ui -> label_2_2);
    if(i==21)
        return (ui -> label_3_2);
    if(i==22)
        return (ui -> label_4_2);
    if(i==23)
        return (ui -> label_5_2);
    if(i==24)
        return (ui -> label_6_2);
    if(i==25)
        return (ui -> label_7_2);
    if(i==26)
        return (ui -> label_8_2);
    if(i==27)
        return (ui -> label_0_3);
    if(i==28)
        return (ui -> label_1_3);
    if(i==29)
        return (ui -> label_2_3);
    if(i==30)
        return (ui -> label_3_3);
    if(i==31)
        return (ui -> label_4_3);
    if(i==32)
        return (ui -> label_5_3);
    if(i==33)
        return (ui -> label_6_3);
    if(i==34)
        return (ui -> label_7_3);
    if(i==35)
        return (ui -> label_8_3);
    if(i==36)
        return (ui -> label_0_4);
    if(i==37)
        return (ui -> label_1_4);
    if(i==38)
        return (ui -> label_2_4);
    if(i==39)
        return (ui -> label_3_4);
    if(i==40)
        return (ui -> label_4_4);
    if(i==41)
        return (ui -> label_5_4);
    if(i==42)
        return (ui -> label_6_4);
    if(i==43)
        return (ui -> label_7_4);
    if(i==44)
        return (ui -> label_8_4);
    if(i==45)
        return (ui -> label_0_5);
    if(i==46)
        return (ui -> label_1_5);
    if(i==47)
        return (ui -> label_2_5);
    if(i==48)
        return (ui -> label_3_5);
    if(i==49)
        return (ui -> label_4_5);
    if(i==50)
        return (ui -> label_5_5);
    if(i==51)
        return (ui -> label_6_5);
    if(i==52)
        return (ui -> label_7_5);
    if(i==53)
        return (ui -> label_8_5);
    if(i==54)
        return (ui -> label_0_6);
    if(i==55)
        return (ui -> label_1_6);
    if(i==56)
        return (ui -> label_2_6);
    if(i==57)
        return (ui -> label_3_6);
    if(i==58)
        return (ui -> label_4_6);
    if(i==59)
        return (ui -> label_5_6);
    if(i==60)
        return (ui -> label_6_6);
    if(i==61)
        return (ui -> label_7_6);
    if(i==62)
        return (ui -> label_8_6);
    if(i==63)
        return (ui -> label_0_7);
    if(i==64)
        return (ui -> label_1_7);
    if(i==65)
        return (ui -> label_2_7);
    if(i==66)
        return (ui -> label_3_7);
    if(i==67)
        return (ui -> label_4_7);    
    if(i==68)
        return (ui -> label_5_7);
    if(i==69)
        return (ui -> label_6_7);
    if(i==70)
        return (ui -> label_7_7);
    if(i==71)
        return (ui -> label_8_7);
    if(i==72)
        return (ui -> label_0_8);
    if(i==73)
        return (ui -> label_1_8);
    if(i==74)
        return (ui -> label_2_8);
    if(i==75)
        return (ui -> label_3_8);
    if(i==76)
        return (ui -> label_4_8);
    if(i==77)
        return (ui -> label_5_8);
    if(i==78)
        return (ui -> label_6_8);
    if(i==79)
        return (ui -> label_7_8);
    if(i==80)
        return (ui -> label_8_8);
    return 0;
    
}

/////////////////////////////////////////////////////////////////////////////
//transitions functions 

//todo , add blur coeff
SDL_Surface *image_treatment(char *path ){
    SDL_Surface *image = IMG_Load(path);
    binarize(image);
    return image;
}

//FELIX PART 


void sudoku_detection(SDL_Surface * img, SDL_Surface * array[81]){
  //find the sudoku
  /*
  SDL_Surface * imgrlsa = copy_image(img);
  rlsa(rlsaimg);
  matrix* mtx = cutGraph(rlsaimg, img);
  */

  matrix * mtx = SDLtoMatrix(img);

  //find sudoku blocks
  cutMatrix(mtx, array);
  for(int i = 0; i < 81; i++){
      array[i] = rotozoomSurface(array[i], 0.0, 28.0/(double)array[i]->w, 1.0);
      }
  deleteMatrix(mtx);
}

//PARAMETER:
//surfaces: all the cut squares of the sudoku
void digit_recognition(SDL_Surface* surfaces[81] , UserInterface* ui){
    int numHidden = 100;
    int numOutputs = 10;
    //CREATES THE ARRAYS WE NEED
    int labels[81];
    double hidden1[numHidden];
    double hidden2[numHidden];
    double outputs[numOutputs];
    double hiddenWeights1[numHidden][784];
    double hiddenBiases1[numHidden];
    double hiddenWeights2[numHidden][numHidden];
    double hiddenBiases2[numHidden];
    double outputWeights[numOutputs][numHidden];
    double outputBiases[numOutputs];

    //INITIALISES WEIGHTS AND BIASES FROM A FILE
    FILE* file = NULL;
    file = fopen("../param_NN.txt", "r");
    if(file == NULL){
        printf("Error: cannot open file \"param_NN.txt\"\n");
    }
    else{
        for (int i = 0; i < numHidden; ++i) {
            fscanf(file, "%lf\n", &hiddenBiases1[i]);
            for (int j = 0; j < 784; ++j) {
                fscanf(file, "%lf\n", &hiddenWeights1[i][j]);
            }
        }
        for (int i = 0; i < numHidden; ++i) {
            fscanf(file, "%lf\n", &hiddenBiases2[i]);
            for (int j = 0; j < numHidden; ++j) {
                fscanf(file, "%lf\n", &hiddenWeights2[i][j]);
            }
        }
        for (int i = 0; i < numOutputs; ++i) {
            fscanf(file, "%lf\n", &outputBiases[i]);
            for (int j = 0; j < numHidden; ++j) {
                fscanf(file, "%lf\n", &outputWeights[i][j]);
            }
        }
        fclose(file);
        printf("Weights and biases have been loaded succesfully from \"param_NN.txt\"\n");
    }

    //CYCLES THROUGH EACH SURFACE OF THE SUDOKU
    for (int i = 0; i < 81; ++i) {
        //RESIZES SURFACE TO 28x28 PIXELS
        SDL_Surface* input = rotozoomSurface(surfaces[i],0.0, 1/surfaces[i]->w*28,1.0);

        //INITIALISES THE INPUTS ARRAY
        int inputs[784];
        for (int j = 0; j < 28; ++j) {
            for (int k = 0; k < 28; ++k) {
                int pixel = getpixel(input, i, j);
                inputs[j*28+k] = (pixel) ? 0 : 1;
            }
        }

        //----------FORWARD PROPAGATION----------

        //HIDDEN LAYER 1
        for (int j=0; j<numHidden; j++) {
            double activation = hiddenBiases1[j];
            for (int k=0; k<784; k++) {
                activation += inputs[j]*hiddenWeights1[j][k];
            }
            hidden1[j] = relu(activation);
        }

        //HIDDEN LAYER 2
        for (int j=0; j<numHidden; j++) {
            double activation = hiddenBiases2[j];
            for (int k=0; k<numHidden; k++) {
                activation+=hidden1[k] * hiddenWeights2[j][k];
            }
            hidden2[j] = relu(activation);
        }

        //OUTPUT LAYER
        for (int j=0; j<numOutputs; j++) {
            double activation = outputBiases[j];
            for (int k=0; k<numHidden; k++) {
                activation+=hidden2[k] * outputWeights[j][k];
            }
            outputs[j] = activation;
        }
        softmax(outputs, numOutputs);

        //DEFINES THE FINAL HYPOTHESIS
        double higherProbability = 0.0;
        int hypothesis;
        for (int j = 0; j < numOutputs; ++j) {
            if(outputs[j] > higherProbability){
                higherProbability = outputs[j];
                hypothesis = j;
            }
        }
        //INITIALISES THE CORRESPONDING LABEL
        labels[i] = hypothesis;
    }
    int *label_pointer = &labels[0];

    
    /*
    for(int i=0 ; i <81 ; ++i)
        *(ui -> init_grid +i) =*(label_pointer + i);
    */
}

//////////////////////////////////////////////////////////////////////////////
//signal handlers

// Signal handler for the "clicked" signal of the start button.//convert button 
void on_start(GtkButton *button, gpointer user_data)
{
    UserInterface* ui = user_data;
    //label_cols_row
    //80=total cells of the 2d array 
    for (int i=0; i <=80 ; i++)
    {
        gchar *my_string = g_strdup_printf("%i",*(ui -> init_grid + i));
        //printf("*(ui -> init_grid + i)")
        //g_print(my_string);
        //g_print("\n");
        gtk_label_set_text (GTK_LABEL(returnwidget(user_data , i)),(const gchar*)my_string);
    
    }
    
}

// Signal handler for the "clicked" signal of the execute button.
void on_execute(GtkButton *button, gpointer user_data)
{
    UserInterface* ui = user_data;
    //label_cols_row
    //80=total cells of the 2d array 
    //add solver with pointers 
    solve_pointers(ui -> init_grid, 9 , ui -> res_grid );

    for (int i=0; i <=80 ; i++)
    {
        gchar *my_string = g_strdup_printf("%i",*(ui -> res_grid + i));
        gtk_label_set_text (GTK_LABEL(returnwidget(user_data , i)),(const gchar*)my_string);
    
    }
    
}
void on_save(GtkButton *button, gpointer user_data)
{
    UserInterface* ui = user_data;
    char result[]= {'r','e','s','u','l','t',(ui -> event ) + '0','\0'};
    int *result2=ui->res_grid;
    FILE *fp1= fopen(result,"w");
    for(size_t i=0;i<9;i++){
        for(size_t j=0;j<9;j++){
            if(j==2 || j==5 || j ==8){  
                fprintf(fp1,"%d ",result2[i*9 +j]); 
            }
            else{
                fprintf(fp1,"%d",result2[i*9 +j]); 
            }    
        }
        if(i==2 || i==5){
            fprintf(fp1,"\n");
        }
        fprintf(fp1,"\n");
    }
    fclose(fp1);  
}



// Signal handler for the "clicked" signal of the clear button.
void on_clear(GtkButton *button, gpointer user_data)
{
    for (int i=0; i <=80 ; i++)
        gtk_label_set_text (GTK_LABEL(returnwidget(user_data , i)),(const gchar*)"0");   
}

// Signal handler for the "file-set" signal of the filechooser button.
void on_filechooser_file_set(GtkFileChooserButton *f,gpointer user_data)
    {
        UserInterface* ui = user_data;
        (ui -> event)+=1;
        printf("filename = %s\n" , gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f)));
        SDL_Surface *image =image_treatment(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f)));
        //display1(image);
        SDL_Surface * array4[81];
        sudoku_detection(image,array4);
        digit_recognition(array4,ui);
        //gtk_container_add (GTK_CONTAINER (ui ->event_box), gtk_image_new_from_file ("gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f))"));

    }

//////////////////////////////////////////////////////////////////////////////
// Main function.
int main (int argc, char *argv[])
{
     
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Loads the UI description and builds the UI.
    // (Exits if an error occurs.)
    GtkBuilder* builder = gtk_builder_new();
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "gui.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Gets the widgets from glade

    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.duel"));
    gtk_window_set_resizable (window, FALSE);
    GtkButton* start_button = GTK_BUTTON(gtk_builder_get_object(builder, "start_button"));
    GtkButton* save_button = GTK_BUTTON(gtk_builder_get_object(builder, "save_button"));
    GtkFileChooserButton* file = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "filechooser"));
    //GtkWidget* main_box  = GTK_WIDGET(gtk_builder_get_object(builder, "main_box"));
    GtkGrid* grid =GTK_GRID(gtk_builder_get_object(builder, "gridbox5"));
    GtkButton* execute = GTK_BUTTON(gtk_builder_get_object(builder, "execute"));
    GtkButton* clear = GTK_BUTTON(gtk_builder_get_object(builder, "Clear"));
    GtkEventBox* event_box = GTK_EVENT_BOX(gtk_builder_get_object(builder, "event_box"));

    //get alll labels from the grid 
    //[ROW][COL]
    //ROW 0
    GtkWidget *label_0_0=GTK_WIDGET(gtk_builder_get_object(builder, "label[0][0]"));
    GtkWidget *label_1_0=GTK_WIDGET(gtk_builder_get_object(builder, "label[1][0]"));
    GtkWidget *label_2_0=GTK_WIDGET(gtk_builder_get_object(builder, "label[2][0]"));
    GtkWidget *label_3_0=GTK_WIDGET(gtk_builder_get_object(builder, "label[3][0]"));
    GtkWidget *label_4_0=GTK_WIDGET(gtk_builder_get_object(builder, "label[4][0]"));
    GtkWidget *label_5_0=GTK_WIDGET(gtk_builder_get_object(builder, "label[5][0]"));
    GtkWidget *label_6_0=GTK_WIDGET(gtk_builder_get_object(builder, "label[6][0]"));
    GtkWidget *label_7_0=GTK_WIDGET(gtk_builder_get_object(builder, "label[7][0]"));
    GtkWidget *label_8_0=GTK_WIDGET(gtk_builder_get_object(builder, "label[8][0]"));
    //ROW 1
    GtkWidget *label_0_1=GTK_WIDGET(gtk_builder_get_object(builder, "label[0][1]"));
    GtkWidget *label_1_1=GTK_WIDGET(gtk_builder_get_object(builder, "label[1][1]"));
    GtkWidget *label_2_1=GTK_WIDGET(gtk_builder_get_object(builder, "label[2][1]"));
    GtkWidget *label_3_1=GTK_WIDGET(gtk_builder_get_object(builder, "label[3][1]"));
    GtkWidget *label_4_1=GTK_WIDGET(gtk_builder_get_object(builder, "label[4][1]"));
    GtkWidget *label_5_1=GTK_WIDGET(gtk_builder_get_object(builder, "label[5][1]"));
    GtkWidget *label_6_1=GTK_WIDGET(gtk_builder_get_object(builder, "label[6][1]"));
    GtkWidget *label_7_1=GTK_WIDGET(gtk_builder_get_object(builder, "label[7][1]"));
    GtkWidget *label_8_1=GTK_WIDGET(gtk_builder_get_object(builder, "label[8][1]"));
    //ROW 2
    GtkWidget *label_0_2=GTK_WIDGET(gtk_builder_get_object(builder, "label[0][2]"));
    GtkWidget *label_1_2=GTK_WIDGET(gtk_builder_get_object(builder, "label[1][2]"));
    GtkWidget *label_2_2=GTK_WIDGET(gtk_builder_get_object(builder, "label[2][2]"));
    GtkWidget *label_3_2=GTK_WIDGET(gtk_builder_get_object(builder, "label[3][2]"));
    GtkWidget *label_4_2=GTK_WIDGET(gtk_builder_get_object(builder, "label[4][2]"));
    GtkWidget *label_5_2=GTK_WIDGET(gtk_builder_get_object(builder, "label[5][2]"));
    GtkWidget *label_6_2=GTK_WIDGET(gtk_builder_get_object(builder, "label[6][2]"));
    GtkWidget *label_7_2=GTK_WIDGET(gtk_builder_get_object(builder, "label[7][2]"));
    GtkWidget *label_8_2=GTK_WIDGET(gtk_builder_get_object(builder, "label[8][2]"));
    //ROW 3
    GtkWidget *label_0_3=GTK_WIDGET(gtk_builder_get_object(builder, "label[0][3]"));
    GtkWidget *label_1_3=GTK_WIDGET(gtk_builder_get_object(builder, "label[1][3]"));
    GtkWidget *label_2_3=GTK_WIDGET(gtk_builder_get_object(builder, "label[2][3]"));
    GtkWidget *label_3_3=GTK_WIDGET(gtk_builder_get_object(builder, "label[3][3]"));
    GtkWidget *label_4_3=GTK_WIDGET(gtk_builder_get_object(builder, "label[4][3]"));
    GtkWidget *label_5_3=GTK_WIDGET(gtk_builder_get_object(builder, "label[5][3]"));
    GtkWidget *label_6_3=GTK_WIDGET(gtk_builder_get_object(builder, "label[6][3]"));
    GtkWidget *label_7_3=GTK_WIDGET(gtk_builder_get_object(builder, "label[7][3]"));
    GtkWidget *label_8_3=GTK_WIDGET(gtk_builder_get_object(builder, "label[8][3]"));
    //ROW 4
    GtkWidget *label_0_4=GTK_WIDGET(gtk_builder_get_object(builder, "label[0][4]"));
    GtkWidget *label_1_4=GTK_WIDGET(gtk_builder_get_object(builder, "label[1][4]"));
    GtkWidget *label_2_4=GTK_WIDGET(gtk_builder_get_object(builder, "label[2][4]"));
    GtkWidget *label_3_4=GTK_WIDGET(gtk_builder_get_object(builder, "label[3][4]"));
    GtkWidget *label_4_4=GTK_WIDGET(gtk_builder_get_object(builder, "label[4][4]"));
    GtkWidget *label_5_4=GTK_WIDGET(gtk_builder_get_object(builder, "label[5][4]"));
    GtkWidget *label_6_4=GTK_WIDGET(gtk_builder_get_object(builder, "label[6][4]"));
    GtkWidget *label_7_4=GTK_WIDGET(gtk_builder_get_object(builder, "label[7][4]"));
    GtkWidget *label_8_4=GTK_WIDGET(gtk_builder_get_object(builder, "label[8][4]"));
    //ROW 5
    GtkWidget *label_0_5=GTK_WIDGET(gtk_builder_get_object(builder, "label[0][5]"));
    GtkWidget *label_1_5=GTK_WIDGET(gtk_builder_get_object(builder, "label[1][5]"));
    GtkWidget *label_2_5=GTK_WIDGET(gtk_builder_get_object(builder, "label[2][5]"));
    GtkWidget *label_3_5=GTK_WIDGET(gtk_builder_get_object(builder, "label[3][5]"));
    GtkWidget *label_4_5=GTK_WIDGET(gtk_builder_get_object(builder, "label[4][5]"));
    GtkWidget *label_5_5=GTK_WIDGET(gtk_builder_get_object(builder, "label[5][5]"));
    GtkWidget *label_6_5=GTK_WIDGET(gtk_builder_get_object(builder, "label[6][5]"));
    GtkWidget *label_7_5=GTK_WIDGET(gtk_builder_get_object(builder, "label[7][5]"));
    GtkWidget *label_8_5=GTK_WIDGET(gtk_builder_get_object(builder, "label[8][5]"));
    //ROW 6
    GtkWidget *label_0_6=GTK_WIDGET(gtk_builder_get_object(builder, "label[0][6]"));
    GtkWidget *label_1_6=GTK_WIDGET(gtk_builder_get_object(builder, "label[1][6]"));
    GtkWidget *label_2_6=GTK_WIDGET(gtk_builder_get_object(builder, "label[2][6]"));
    GtkWidget *label_3_6=GTK_WIDGET(gtk_builder_get_object(builder, "label[3][6]"));
    GtkWidget *label_4_6=GTK_WIDGET(gtk_builder_get_object(builder, "label[4][6]"));
    GtkWidget *label_5_6=GTK_WIDGET(gtk_builder_get_object(builder, "label[5][6]"));
    GtkWidget *label_6_6=GTK_WIDGET(gtk_builder_get_object(builder, "label[6][6]"));
    GtkWidget *label_7_6=GTK_WIDGET(gtk_builder_get_object(builder, "label[7][6]"));
    GtkWidget *label_8_6=GTK_WIDGET(gtk_builder_get_object(builder, "label[8][6]"));
    //Row 7
    GtkWidget *label_0_7=GTK_WIDGET(gtk_builder_get_object(builder, "label[0][7]"));
    GtkWidget *label_1_7=GTK_WIDGET(gtk_builder_get_object(builder, "label[1][7]"));
    GtkWidget *label_2_7=GTK_WIDGET(gtk_builder_get_object(builder, "label[2][7]"));
    GtkWidget *label_3_7=GTK_WIDGET(gtk_builder_get_object(builder, "label[3][7]"));
    GtkWidget *label_4_7=GTK_WIDGET(gtk_builder_get_object(builder, "label[4][7]"));
    GtkWidget *label_5_7=GTK_WIDGET(gtk_builder_get_object(builder, "label[5][7]"));
    GtkWidget *label_6_7=GTK_WIDGET(gtk_builder_get_object(builder, "label[6][7]"));
    GtkWidget *label_7_7=GTK_WIDGET(gtk_builder_get_object(builder, "label[7][7]"));
    GtkWidget *label_8_7=GTK_WIDGET(gtk_builder_get_object(builder, "label[8][7]"));
    //ROW 8
    GtkWidget *label_0_8=GTK_WIDGET(gtk_builder_get_object(builder, "label[0][8]"));
    GtkWidget *label_1_8=GTK_WIDGET(gtk_builder_get_object(builder, "label[1][8]"));
    GtkWidget *label_2_8=GTK_WIDGET(gtk_builder_get_object(builder, "label[2][8]"));
    GtkWidget *label_3_8=GTK_WIDGET(gtk_builder_get_object(builder, "label[3][8]"));
    GtkWidget *label_4_8=GTK_WIDGET(gtk_builder_get_object(builder, "label[4][8]"));
    GtkWidget *label_5_8=GTK_WIDGET(gtk_builder_get_object(builder, "label[5][8]"));
    GtkWidget *label_6_8=GTK_WIDGET(gtk_builder_get_object(builder, "label[6][8]"));
    GtkWidget *label_7_8=GTK_WIDGET(gtk_builder_get_object(builder, "label[7][8]"));
    GtkWidget *label_8_8=GTK_WIDGET(gtk_builder_get_object(builder, "label[8][8]"));




//testing 
///////////////////////////////////////////////////////////////////////////////

// to remove 
    int soduko_grid[9][9]=
                       {{ 5, 3, 0 , 0, 7, 0, 0, 0, 0 },
                       { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
                       { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
                       { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
                       { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
                       { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
                       { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
                       { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
                       { 0, 0, 0, 0 , 8, 0, 0, 7, 9 } };

///////////////////////////////////////////////////////////////////////////////

    int res[9][9];
    //init the ui structure to be used in signal heandlers     
    UserInterface ui =
    {
        .window = window,
        .start_button = start_button,
        .file = file,
        .grid = grid,
        .init_grid=&soduko_grid[0][0],
        .res_grid=&res[0][0],
        .event=0,
        .event_box = event_box,
        .label_0_0=label_0_0,
        .label_1_0=label_1_0,
        .label_2_0=label_2_0,
        .label_3_0=label_3_0,
        .label_4_0=label_4_0,
        .label_5_0=label_5_0,
        .label_6_0=label_6_0,
        .label_7_0=label_7_0,
        .label_8_0=label_8_0,
        //ROW 1
        .label_0_1=label_0_1,
        .label_1_1=label_1_1,
        .label_2_1=label_2_1,
        .label_3_1=label_3_1,
        .label_4_1=label_4_1,
        .label_5_1=label_5_1,
        .label_6_1=label_6_1,
        .label_7_1=label_7_1,
        .label_8_1=label_8_1,
        //ROW 2
        .label_0_2=label_0_2,
        .label_1_2=label_1_2,
        .label_2_2=label_2_2,
        .label_3_2=label_3_2,
        .label_4_2=label_4_2,
        .label_5_2=label_5_2,
        .label_6_2=label_6_2,
        .label_7_2=label_7_2,
        .label_8_2=label_8_2,
        //ROW 3
        .label_0_3=label_0_3,
        .label_1_3=label_1_3,
        .label_2_3=label_2_3,
        .label_3_3=label_3_3,
        .label_4_3=label_4_3,
        .label_5_3=label_5_3,
        .label_6_3=label_6_3,
        .label_7_3=label_7_3,
        .label_8_3=label_8_3,
        //ROW 4
        .label_0_4=label_0_4,
        .label_1_4=label_1_4,
        .label_2_4=label_2_4,
        .label_3_4=label_3_4,
        .label_4_4=label_4_4,
        .label_5_4=label_5_4,
        .label_6_4=label_6_4,
        .label_7_4=label_7_4,
        .label_8_4=label_8_4,
        //ROW 5
        .label_0_5=label_0_5,
        .label_1_5=label_1_5,
        .label_2_5=label_2_5,
        .label_3_5=label_3_5,
        .label_4_5=label_4_5,
        .label_5_5=label_5_5,
        .label_6_5=label_6_5,
        .label_7_5=label_7_5,
        .label_8_5=label_8_5,
        //ROW 6
        .label_0_6=label_0_6,
        .label_1_6=label_1_6,
        .label_2_6=label_2_6,
        .label_3_6=label_3_6,
        .label_4_6=label_4_6,
        .label_5_6=label_5_6,
        .label_6_6=label_6_6,
        .label_7_6=label_7_6,
        .label_8_6=label_8_6,
        //Row 7
        .label_0_7=label_0_7,
        .label_1_7=label_1_7,
        .label_2_7=label_2_7,
        .label_3_7=label_3_7,
        .label_4_7=label_4_7,
        .label_5_7=label_5_7,
        .label_6_7=label_6_7,
        .label_7_7=label_7_7,
        .label_8_7=label_8_7,
        //ROW 8
        .label_0_8=label_0_8,
        .label_1_8=label_1_8,
        .label_2_8=label_2_8,
        .label_3_8=label_3_8,
        .label_4_8=label_4_8,
        .label_5_8=label_5_8,
        .label_6_8=label_6_8,
        .label_7_8=label_7_8,
        .label_8_8=label_8_8,
      };
    // Connects signal handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start), &ui);
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save), &ui);
    g_signal_connect(execute, "clicked", G_CALLBACK(on_execute), &ui);
    g_signal_connect(clear, "clicked", G_CALLBACK(on_clear), &ui);
    g_signal_connect(file, "file-set", G_CALLBACK(on_filechooser_file_set), &ui);

    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}
