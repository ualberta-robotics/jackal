[![Institut Maupertuis logo](http://www.institutmaupertuis.fr/media/gabarit/logo.png)](http://www.institutmaupertuis.fr)

This demonstrates a simple RViz plugin which calls a service:
- An information or error message is displayed depending on the service response
- The service is called in a separate thread in the Qt GUI

# Running
```bash
roslaunch simple_rviz_plugin rviz.launch
```

# Screenshots
![Panel](panel.png)

![Service success](service_success.png)

![Service error](service_error.png)
