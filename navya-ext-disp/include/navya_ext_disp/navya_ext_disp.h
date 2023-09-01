#ifndef NAVYA_EXT_DISP_H
#define NAVYA_EXT_DISP_H

#include <QWidget>
#include <QLabel>
#include <QScreen>
#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <autodrive_msgs/ModeCmd.h>

namespace Ui {
class ExtDisp;
}

class ExtDisp : public QWidget
{
  Q_OBJECT

public:
  explicit ExtDisp(QWidget *parent = nullptr);
  ~ExtDisp();
  void cb_mode_cmd(const autodrive_msgs::ModeCmd::ConstPtr& msg); // Don't forget to add callback

public slots:
  void spinOnce();

private:
  Ui::ExtDisp *ui;

  QTimer *ros_timer;

  QPixmap ManualDriving, AutonomousDriving;

  ros::NodeHandlePtr nh_;
  ros::Subscriber mode_cmd_sub_;
  // ros::Publisher  monitor_rpt_pub_;
};

#endif // NAVYA_EXT_DISP_H
