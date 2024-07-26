#ifndef NAV_STOP_RVIZ_PLUGIN_MY_RVIZ_PANEL_HPP
#define NAV_STOP_RVIZ_PLUGIN_MY_RVIZ_PANEL_HPP

#include <QFuture>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QtConcurrent/QtConcurrentRun>
#include <QVBoxLayout>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <actionlib_msgs/GoalID.h>
#include <rviz/panel.h>

namespace nav_stop_rviz_plugin
{

class NavStopRvizPanel : public rviz::Panel
{
Q_OBJECT

public:
  NavStopRvizPanel(QWidget* parent = 0);
  virtual ~NavStopRvizPanel();

Q_SIGNALS:
  void enable(const bool);

protected Q_SLOTS:
  virtual void load(const rviz::Config &config);
  virtual void save(rviz::Config config) const;

private:
  virtual void publishEStop();
  virtual void sendGoalCancel();
  void delayDisappear();

  bool stopTriggered_;

  QPushButton* estop_button_;
  QPushButton* cancel_button_;
  QLabel* estop_label_;
  QLabel* cancel_label_;

  ros::NodeHandle nh_;
  ros::Publisher estop_pub_;
  ros::Publisher cancel_pub_;
};

}

#endif
