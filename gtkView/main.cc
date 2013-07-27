#include <gtk/gtk.h>
#include <webkit/webkit.h>
#define URI_PATH1 "http://10.1.58.230:/demos/SimplePlayer.html"
int main(int argc, char* argv[])
{
    // Initialize GTK+
    gtk_init(&argc, &argv);

    // Create an 800x600  window that will contain the browser instance

    GtkWidget *window      = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window),GTK_WIN_POS_CENTER_ALWAYS);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);


    GtkWidget *vbox = gtk_vbox_new(FALSE,0);
    gtk_container_set_border_width(GTK_CONTAINER(vbox),10);
    gtk_container_add(GTK_CONTAINER(window),vbox);

    GtkWidget *box_view = gtk_vbox_new(TRUE,0);
    GtkWidget *hbox = gtk_hbox_new(FALSE,0);
    //创建提示关闭按钮
    GtkWidget *button1 = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(button1)," 关闭视频 ");
    g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(destroyWindowCb),NULL);
    GtkWidget *label1 = gtk_label_new(NULL);
    //字体为蓝色20号
    gtk_label_set_markup(GTK_LABEL(label1),"<span foreground = 'blue' font_desc = '20'>关闭视频</span>");
    //排列
    gtk_box_pack_start(GTK_BOX(vbox),box_view, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
    //hbox排列
    gtk_box_pack_start(GTK_BOX(hbox),button1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox),label1, FALSE, FALSE, 5);


    // Create a scrollable area, and put the browser instance into it
    GtkWidget *scrolledWindow = gtk_scrolled_window_new(NULL, NULL);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow),
    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolledWindow),GTK_SHADOW_IN);
    gtk_box_pack_start(GTK_BOX(box_view),scrolledWindow,TRUE,TRUE,0);
    // Create a browser instance
    WebKitWebView *webview = WEBKIT_WEB_VIEW(webkit_web_view_new());

    gtk_container_add(GTK_CONTAINER(scrolledWindow), GTK_WIDGET(webview));

    // Set up callbacks so that if either the main window or the browser instance is
    // closed, the program will exit
    g_signal_connect(window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
    g_signal_connect(webview, "close-web-view", G_CALLBACK(closewebviewCb), window);

    // Load a web page into the browser instance
    webkit_web_view_load_uri(webview,URI_PATH1);

    WebKitWebSettings *settings1 = webkit_web_settings_new ();
    g_object_set (G_OBJECT(settings1), "enable-plugins",TRUE, NULL);
    webkit_web_view_set_settings (WEBKIT_WEB_VIEW(webview), settings1);
    g_object_unref (settings1);

    //Default value:TURE
    WebKitWebSettings *settings2 = webkit_web_settings_new ();
    g_object_set (G_OBJECT(settings2), "enable-scripts", TRUE, NULL);
    webkit_web_view_set_settings (WEBKIT_WEB_VIEW(webview), settings2);
    g_object_unref (settings2);

    gtk_widget_grab_focus(GTK_WIDGET(webview));

    // Make sure the main window and all its contents are visible
    gtk_widget_show_all(window);

    // Run the main GTK+ event loop
    gtk_main();

    return 0;
}
