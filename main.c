#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <curses.h>
#include <string.h>
#include <gtk/gtk.h>
struct update_data_struct{
	GtkLabel *label1;
	long int *num;
};
void *backendFunction(void * arg){
	long int * _num	=	(long int *)arg;
	long int i 		= 	0;
	while(1){
		*_num	=	i++;
		usleep(1000);
	}
}
gboolean update_data(gpointer user_data){	
	char out[20];
	
	struct update_data_struct* data = (struct update_data_struct*)user_data; 
	
	long int sec = *data->num/1000,ms = *data->num%1000;
	
	sprintf(out, "Time: %2ld sec %3ld ms",sec,ms);

	gtk_label_set_text(data->label1,out);
}
static void activate (GtkApplication *app, gpointer user_data){
	GtkWidget *window;
	GtkWidget *label_box;
	GtkWidget *label1;
	
	long int *num	= (long int*)user_data;
	
	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
	
	label_box 	= gtk_box_new (FALSE,0);
	gtk_container_add (GTK_CONTAINER (window), label_box);
	
	label1	=	gtk_label_new (NULL);
	
	gtk_container_add  (GTK_CONTAINER(label_box), label1);
    
	struct update_data_struct* data = (struct update_data_struct*)malloc(sizeof(struct update_data_struct));
    
    data->label1 = GTK_LABEL(label1);
      
    data->num = num;
       
    g_timeout_add(200, (GSourceFunc) update_data, (gpointer) data);
    
	gtk_widget_show_all (window);
}
int main(int    argc, char **argv){
	long int num = 0;
	
	pthread_t pth;
	
	pthread_create(&pth, NULL, backendFunction, &num);
	
	GtkApplication *app;
	
	int status;
	
	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	
	g_signal_connect (app, "activate", G_CALLBACK (activate), &num);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}


