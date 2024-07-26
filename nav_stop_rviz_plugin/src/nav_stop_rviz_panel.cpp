#include <nav_stop_rviz_plugin/nav_stop_rviz_panel.hpp>

namespace nav_stop_rviz_plugin
{
NavStopRvizPanel::NavStopRvizPanel(QWidget* parent) :
        rviz::Panel(parent)
{
  Q_EMIT enable(true);

  setObjectName("Nav Stop Panel");
  setName(objectName());

  QVBoxLayout* layout = new QVBoxLayout();
  setLayout(layout);

  estop_label_ = new QLabel("E-Stop Status: Not Triggered");
  estop_label_->setAlignment(Qt::AlignCenter);
  estop_label_->setStyleSheet("QLabel { color : green; }");
  estop_button_ = new QPushButton("Trigger E-Stop");
  cancel_button_ = new QPushButton("Cancel Nav Goal");
  cancel_label_ = new QLabel("");
  cancel_label_->setAlignment(Qt::AlignCenter);
  cancel_label_->setStyleSheet("QLabel { color : red; }");

  layout->addWidget(new QLabel("E-Stop Toggle:"));
  layout->addWidget(estop_label_);
  layout->addWidget(estop_button_);
  layout->addStretch();
  layout->addWidget(new QLabel("Navigation Cancel:"));
  layout->addWidget(cancel_label_);
  layout->addWidget(cancel_button_);
  layout->addStretch();

  connect(estop_button_, &QPushButton::released, this, [=]
    {
      QtConcurrent::run(this, &NavStopRvizPanel::publishEStop);
    }
  );
  connect(cancel_button_, &QPushButton::released, this, [=]
    {
      QtConcurrent::run(this, &NavStopRvizPanel::sendGoalCancel);
    }
  );

  estop_pub_ = nh_.advertise<std_msgs::Bool>("/e_stop", 1);
  cancel_pub_ = nh_.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 1);
  stopTriggered_ = false;
}

NavStopRvizPanel::~NavStopRvizPanel()
{
}

void NavStopRvizPanel::publishEStop()
{
  std_msgs::Bool msg;
  if (!stopTriggered_) {
    msg.data = true;
    estop_pub_.publish(msg);
    stopTriggered_ = true;
    estop_label_->setText("E-Stop Status: Triggered");
    estop_label_->setStyleSheet("QLabel { color : red; }");
    estop_button_->setText("Disable E-Stop");
  } else {
    msg.data = false;
    estop_pub_.publish(msg);
    stopTriggered_ = false;
    estop_label_->setText("E-Stop Status: Not Triggered");
    estop_label_->setStyleSheet("QLabel { color : green; }");
    estop_button_->setText("Trigger E-Stop");
  }
}

void NavStopRvizPanel::sendGoalCancel()
{
  actionlib_msgs::GoalID cancel_msg;
  cancel_pub_.publish(cancel_msg);
  cancel_label_->setText("Cancel Sent.");
  QtConcurrent::run(this, &NavStopRvizPanel::delayDisappear);
}

void NavStopRvizPanel::delayDisappear()
{
  ros::Duration(5).sleep();
  cancel_label_->setText("");
}

void NavStopRvizPanel::load(const rviz::Config& config)
{
  rviz::Panel::load(config);
}

void NavStopRvizPanel::save(rviz::Config config) const
                 {
  rviz::Panel::save(config);
}

}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(nav_stop_rviz_plugin::NavStopRvizPanel, rviz::Panel)
