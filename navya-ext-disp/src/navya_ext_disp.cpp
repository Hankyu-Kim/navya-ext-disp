#include "navya_ext_disp.h"
#include "ui_navya_ext_disp.h"

ExtDisp::ExtDisp(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ExtDisp)
{
  ui->setupUi(this);

  nh_.reset(new ros::NodeHandle("~"));

  setWindowFlags(Qt::FramelessWindowHint);

  QList<QScreen*> screens = QGuiApplication::screens();
  if (screens.size() > 1) {
    ROS_INFO("Second monitor setted, You may need to mirror 2nd and 3rd monitor on settings for WSCE Navya");
    QScreen* secondScreen = screens.at(1);
    QRect screenGeometry = secondScreen->geometry();

    setGeometry(screenGeometry);
  }
  showFullScreen();

  ros_timer = new QTimer(this);
  connect(ros_timer, SIGNAL(timeout()), this, SLOT(spinOnce()));
  ros_timer->start(100);

  mode_cmd_sub_ = nh_->subscribe<autodrive_msgs::ModeCmd>("/autodrive/mode_cmd", 1, &ExtDisp::cb_mode_cmd, this);

  // monitor_rpt_pub_ = nh_->advertise<std_msgs::Float64>("monitor_rpt_topic" ,1);

  ManualDriving.load(":/images/ManualDriving.png");
  AutonomousDriving.load(":/images/AutonomousDriving.png");
}

ExtDisp::~ExtDisp() 
{
  delete ui;
}

void ExtDisp::spinOnce(){
  if(ros::ok()){
    ros::spinOnce();
  }
  else
      QApplication::quit();
}

void ExtDisp::cb_mode_cmd(const autodrive_msgs::ModeCmd::ConstPtr &msg){
  if ((int)(msg->mode_cmd) == 0){
    ui->lblCurrentMode->resize(1920, 1080);
    ui->lblCurrentMode->setPixmap(ManualDriving);
    ui->lblCurrentMode->setScaledContents(true);
    ui->lblCurrentMode->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    ui->lblCurrentMode->setVisible(true);
  }

  else if ((int)(msg->mode_cmd) == 3){
    ui->lblCurrentMode->resize(1920, 1080);
    ui->lblCurrentMode->setPixmap(AutonomousDriving);
    ui->lblCurrentMode->setScaledContents(true);
    ui->lblCurrentMode->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    ui->lblCurrentMode->setVisible(true);
  }

  else{
    ROS_ERROR("MODE ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  }
}
