#include "../include/widget.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   Widget window;
   srand(time(0));
   window.resize(1000, 900);
   window.show();
   return app.exec();
}