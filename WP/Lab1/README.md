Laboratory Work №1
==================

The purpose of this laboratory work was for us to get acquainted with Windows API, message handling, parent and child windows creating. 

I've used limits of maximization and minimzation, because the elements in the window are responsive to size modification of the parent window. It was done using 'WM_GETMINMAXINFO' and 'WM_SIZE' messages.


#### Features
*  When clicking on "Update" button it:
*  changes color of the background (randomly);
*  changes font of customized input box and of button itself;
*  updates the buffer for text output (WM_PAINT) and lead to its output;
*  changes the color of customized text output (randomly).
*  If the button exit is clicked, the program will destroy window and will exit;
*  The text from customized input box will appear in the window after update button is pressed.
*  If clicked, close button will display a message box with notification and then will assign a random 
size for main window.
*  If clicked the X (exit) from top bar, a message box will be thrown.
*  The size of the window is limited to a rectangle that is proportional with the display screen, done
with WM_GETMINMAXINFO. 
