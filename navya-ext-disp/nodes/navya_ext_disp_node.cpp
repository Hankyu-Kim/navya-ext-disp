#include <QApplication>
#include "navya_ext_disp.h"


int main(int argc, char *argv[])
{

  ros::init(argc, argv, "navya_ext_disp_node",ros::init_options::AnonymousName);
  QApplication a(argc, argv);

  ExtDisp w;
  w.setWindowTitle(QString::fromStdString(
                       ros::this_node::getName()));

  w.show();
  return a.exec();
}
