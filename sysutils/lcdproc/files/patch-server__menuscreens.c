--- server/menuscreens.c.orig	2017-06-18 20:40:11.000000000 +0000
+++ server/menuscreens.c	2023-07-10 08:16:23.704416000 +0000
@@ -492,7 +492,7 @@
 
 	debug(RPT_DEBUG, "%s()", __FUNCTION__);
 
-	main_menu = menu_create("mainmenu", NULL, "LCDproc Menu", NULL);
+	main_menu = menu_create("mainmenu", NULL, "DynFi Menu", NULL);
 	if (main_menu == NULL) {
 		report(RPT_ERR, "%s: Cannot create main menu", __FUNCTION__);
 		return;
