URDF Parser for Zephyr RTOS
===========

This is a small URDF (Universal Robot Descriptor File) Parser library. It is intended to be
used to load the most important information needed to display a robot. It was created to
serve as a simple static library to be used in rbdl-toolkit and the rbdl library. One of the main desing goals was to keep it simple and provide a consistent error handling that may be
used to find errors in the URDF files that are loaded.

Insipiration was drawn from the urdfdom library and just as urdfdom it uses tinyxml as
the xml implementation.

Feel free to use it in your own projects.<br>

## Build with your application

```shell
west build -b <board> -s <source> -- -DZEPHYR_EXTRA_MODULES=<path/of/urdfparser>
```

## Example application source code
```cpp
#include <kernel.h>
#include <urdf/model.h>

const char* urdf_str =
    "<?xml version=\"1.0\">\n"
    "<robot name=\"test\">\n"
    "  <material name=\"Grey\">\n"
    "    <color rgba=\"0.2 0.2 0.2 1.0\"/>"
    "  </material>"
    "  <link name=\"link_0\">\n"
    "    <inertial>\n"
    "      <origin rpy=\"0 0 0\" xyz=\"-0.1 0 0.07\"/>\n"
    "      <mass value=\"5.0\"/>\n"
    "      <inertia ixx=\"0.05\" ixy=\"0\" ixz=\"0\" iyy=\"0.06\" iyz=\"0\" izz=\"0.03\"/>\n"
    "    </inertial>\n"
    "    <visual>\n"
    "      <origin rpy=\"0 0 0\" xyz=\"0 0 0\"/>\n"
    "      <geometry>\n"
    "        <mesh filename=\"meshes/link_0.obj\"/>\n"
    "      </geometry>\n"
    "      <material name=\"Grey\"/>\n"
    "    </visual>\n"
    "  </link>\n"
    "<!-- joint between link_0 and link_1 -->\n"
    "  <joint name=\"joint_1\" type=\"revolute\">\n"
    "    <parent link=\"link_0\"/>\n"
    "    <child link=\"link_1\"/>\n"
    "    <origin rpy=\"0 0 0\" xyz=\"0 0 0.1575\"/>\n"
    "    <axis xyz=\"0 0 1\"/>\n"
    "    <limit effort=\"300\" lower=\"-2.96705972839\" upper=\"2.96705972839\" velocity=\"10\"/>\n"
    "    <dynamics damping=\"0.5\"/>\n"
    "  </joint>\n"
    "  <link name=\"link_1\">\n"
    "    <inertial>\n"
    "      <origin rpy=\"0 0 0\" xyz=\"0 -0.03 0.12\"/>\n"
    "      <mass value=\"4\"/>\n"
    "      <inertia ixx=\"0.1\" ixy=\"0\" ixz=\"0\" iyy=\"0.09\" iyz=\"0\" izz=\"0.02\"/>\n"
    "    </inertial>\n"
    "    <visual>\n"
    "      <origin rpy=\"0 0 0\" xyz=\"0 0 0\"/>\n"
    "      <geometry>\n"
    "        <mesh filename=\"meshes/link_1.obj\"/>\n"
    "      </geometry>\n"
    "      <material name=\"Blue\"/>\n"
    "    </visual>\n"
    "  </link>\n"
    "</robot>";

void main()
{
    try
    {
        printk("start example\r\n");

        auto robot = urdf::UrdfModel::fromUrdfStr(urdf_str);
        if (robot == nullptr)
        {
            printk("urdf parsing failed");
            return;
        }
      
        printk("robot : %s\r\n", robot->name.c_str());

        for (auto& link : robot->link_map)
        {
            printk("--link : %s\r\n", link.first.c_str());
        }

        for (auto& joint : robot->joint_map)
        {
            printk("--joint : %s\r\n", joint.first.c_str());
        }

        while (1)
        {
            k_sleep(K_MSEC(1000));
        }
    }
    catch (urdf::URDFParseError& e)
    {
        printk("urdf error : %s", e.what());
    }
}

```
